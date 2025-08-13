#include "Tile.h"

namespace aabb {
    bool CheckCollisionRecLine( Vector2& start, Vector2& direction, Rectangle* rect,
    Vector2& contact_point, Vector2& contact_normal, float& t_hit_near) {
        contact_normal = {0, 0};
        contact_point = {0, 0};

        Vector2 inverse_direction = Vector2{1.0f / direction.x, 1.0f / direction.y};

        Vector2 t_near = Vector2{(rect->x - start.x) * inverse_direction.x, (rect->y - start.y) * inverse_direction.y };
        Vector2 t_far = Vector2{(rect->x + rect->width - start.x) * inverse_direction.x, (rect->y + rect->height - start.y) * inverse_direction.y };   

        if ( std::isnan(t_far.y) || std::isnan(t_far.x) ) return false;
        if ( std::isnan(t_near.y) || std::isnan(t_near.x) ) return false;

        if ( t_near.x > t_far.x ) std::swap(t_near.x, t_far.x);
        if ( t_near.y > t_far.y ) std::swap(t_near.y, t_far.y);

        if ( t_near.x > t_far.y || t_near.y > t_far.x ) return false;

        t_hit_near = std::max(t_near.x, t_near.y);

        float t_hit_far = std::min(t_far.x, t_far.y);

        if ( t_hit_far < 0 ) return false;
        
        contact_point.x = start.x + t_hit_near * direction.x;
        contact_point.y = start.y + t_hit_near * direction.y;

        if ( t_near.x > t_near.y ) 
            if ( inverse_direction.x < 0 )
                contact_normal = { 1, 0 };
            else
                contact_normal = { -1, 0 };
        else if ( t_near.x < t_near.y ) 
            if ( inverse_direction.y < 0 )
                contact_normal = { 0, 1 };
            else
                contact_normal = { 0, -1 };
        return true;
    }

    bool CheckCollisionStaticRectDynamicRect(Rectangle* dynamic, Vector2& velocity, Rectangle& r_static, 
    Vector2& contact_point, Vector2& contact_normal, float& contact_time, float fElapsedTime ) {
        contact_time = 0.0f;

        if ( velocity.x == 0 && velocity.y == 0 ) return false;

        Rectangle expanded_target = Rectangle{ r_static.x - dynamic->width / 2.0f, r_static.y - dynamic->height / 2.0f, 
                                            r_static.width + dynamic->width, r_static.height + dynamic->height };

        Vector2 sourceCenPos = { dynamic->x + dynamic->width / 2.0f, dynamic->y + dynamic->height / 2.0f };
        Vector2 dir = { velocity.x * fElapsedTime, velocity.y * fElapsedTime };

        if ( CheckCollisionRecLine(sourceCenPos, dir, &expanded_target, contact_point, contact_normal, contact_time)) 
        {
            return ( contact_time >= 0.0f && contact_time < 1.0f );
        }
        else return false;
    }

    bool ResolveStaticRectDynamicRect ( Rectangle* dynamic, Vector2& velocity, float fElapsedTime, Rectangle* r_static ) {
        Vector2 cp, cn;
        float ct = 0.0f;
        if ( CheckCollisionStaticRectDynamicRect(dynamic, velocity, *r_static, cp, cn, ct, fElapsedTime)) {
            velocity.x += cn.x * std::abs(velocity.x) * ( 1 - ct );
            velocity.y += cn.y * std::abs(velocity.y) * ( 1 - ct );
            return true;
        }
        return false;
    }
}

float Q_rsqrt( float number ) {
    long i;
    float x2, y;
    const float threehalfs = 1.5f;

    x2 = number * 0.5f;
    y = number;
    i = * ( long * ) &y;
    i = 0x5f3759df - ( i >> 1 );
    y = * ( float * ) &i;
    y = y * ( threehalfs - ( x2 * y * y ) );
    return y;
}

bool compare(const std::pair<int, float>& a, const std::pair<int, float>& b) {
    return a.second < b.second;
}

TileInstance::TileInstance(Vector2 pos, std::shared_ptr<Tile> tile) 
    : pos(pos), tile(tile), bbox( Rectangle{pos.x, pos.y, 16 * SCALE, 16 * SCALE} ) {}

GroundInstance::GroundInstance(Vector2 pos, std::shared_ptr<Tile> ground) 
    : TileInstance(pos, ground) {}

void GroundInstance::update(Mario& player) {
    // handleCollision(player);
}

void GroundInstance::render() {
    DrawTextureEx(tile->getTexture(), pos, 0.0f, SCALE, WHITE);
}

void BrickInstance::handleBreaking(Mario& player){
    Rectangle playerBBox = player.rect;
    if(CheckCollisionRecs(playerBBox, hbox)){
        switch(state) {
            case STATE_NORMAL: state = STATE_BROKEN; break;
            default: break;
        }
    }
}

BrickInstance::BrickInstance(Vector2 pos, std::shared_ptr<Tile> brick) 
    : TileInstance(pos, brick), hbox(Rectangle{pos.x + 24, pos.y + 60, 16, 6}) {}

void BrickInstance::update(Mario& player) {
    dest.x = pos.x; dest.y = pos.y;
    // handleCollision(player);
    handleBreaking(player);

}

void BrickInstance::render() {
    DrawTexturePro(tile->getTexture(), normal, dest, Vector2{0, 0}, 0.0f, WHITE);
    DrawRectangleLinesEx(hbox, 1.0f, RED); // Draw hitbox 
}

QuestionInstance::QuestionInstance(Vector2 pos, std::shared_ptr<Tile> question) 
    : TileInstance(pos, question), hbox(Rectangle{pos.x + 24, pos.y + 60, 16, 6}) {}

void QuestionInstance::handleAnimation(){
    switch ( state ) {
        case STATE_NORMAL:{
            frameCounter++;
            if ( normal.x == 0 ) {
                if ( frameCounter >= frameSpeed2 ) {
                    frameCounter = 0;
                    normal.x += 16;
                }
            } else {
                if ( frameCounter >= frameSpeed ) {
                    frameCounter = 0;
                    normal.x += 16;
                    if ( normal.x >= 48 ) normal.x = 0;
                }
            }
        } break;
        case STATE_ACTIVATED: {
            normal.x = 48; 
        } break;
        default: break;
    }
}

void QuestionInstance::handleActivation(Mario& player){
    Rectangle playerBBox = player.rect;
    if ( CheckCollisionRecs(playerBBox, hbox) ) {
        switch(state) {
            case STATE_NORMAL: state = STATE_ACTIVATED; break;
        }
    }
}

void QuestionInstance::update(Mario& player) {
    dest.x = pos.x; dest.y = pos.y;
    // handleCollision(player);
    handleActivation(player);
    handleAnimation();
}

void QuestionInstance::render() {
    DrawTexturePro(tile->getTexture(), normal, dest, Vector2{0, 0}, 0.0f, WHITE);
    DrawRectangleLinesEx(hbox, 1.0f, RED); // Draw hitbox 
}

BackgroundInstance::BackgroundInstance(Vector2 pos, std::shared_ptr<Tile> background) 
    : TileInstance(pos, background) {}

void BackgroundInstance::update(Mario& player) {
    // handleCollision(player);
}

void BackgroundInstance::render() {
    DrawTextureEx(tile->getTexture(), pos, 0.0f, SCALE, WHITE);
}

PipeInstance1::PipeInstance1(Vector2 pos, std::shared_ptr<Tile> pipe) : TileInstance(pos, pipe) {
    bbox = Rectangle{pos.x, pos.y, 16 * SCALE * 2, 16 * SCALE * 2}; }
PipeInstance2::PipeInstance2(Vector2 pos, std::shared_ptr<Tile> pipe) : TileInstance(pos, pipe) {
    bbox = Rectangle{pos.x, pos.y, 16 * SCALE * 2, 16 * SCALE * 3}; }
PipeInstance3::PipeInstance3(Vector2 pos, std::shared_ptr<Tile> pipe) : TileInstance(pos, pipe) {
    bbox = Rectangle{pos.x, pos.y, 16 * SCALE * 2, 16 * SCALE * 4};
}

void PipeInstance1::update(Mario& player){} // handleCollision(player); }
void PipeInstance2::update(Mario& player){} // handleCollision(player); }
void PipeInstance3::update(Mario& player){} // handleCollision(player); }

void PipeInstance1::render() { DrawTextureEx(tile->getTexture(), pos, 0.0f, SCALE, WHITE); }
void PipeInstance2::render() { DrawTextureEx(tile->getTexture(), pos, 0.0f, SCALE, WHITE); }
void PipeInstance3::render() { DrawTextureEx(tile->getTexture(), pos, 0.0f, SCALE, WHITE); }

HardblockInstance::HardblockInstance(Vector2 pos, std::shared_ptr<Tile> hardblock) 
    : TileInstance(pos, hardblock) {}

void HardblockInstance::update(Mario& player){
    // handleCollision(player);
}

void HardblockInstance::render() { 
    DrawTextureEx(tile->getTexture(), pos, 0.0f, SCALE, WHITE); 
}

GoalpoleInstance::GoalpoleInstance(Vector2 pos, std::shared_ptr<Tile> goalpole) 
    : TileInstance(pos, goalpole) {}

void GoalpoleInstance::update(Mario& player){

}

void GoalpoleInstance::render() {
    DrawTextureEx(tile->getTexture(), pos, 0.0f, SCALE, WHITE);
}

FortressInstance::FortressInstance(Vector2 pos, std::shared_ptr<Tile> fortress) 
    : TileInstance(pos, fortress) {}

void FortressInstance::render() {
    DrawTextureEx(tile->getTexture(), pos, 0.0f, SCALE, WHITE);
}

TileManager::TileManager(){
    tileMap = { 
        {1, std::make_shared<Pipe2>()},
        {2, std::make_shared<Background>()},
        {4, std::make_shared<Fortress>()},
        {7, std::make_shared<Goalpole>()},
        {8, std::make_shared<Ground>()},
        {9, std::make_shared<Hardblock>()},
        {10, std::make_shared<Pipe1>()},
        {12, std::make_shared<Pipe3>()},
        {13, std::make_shared<Question>()},
        {17, std::make_shared<Brick>()}
    };
}

void TileManager::handleBrickPieces(Vector2 position){
    std::shared_ptr<Entity> brickPiece1 = std::make_shared<BrickPiece>("./assets/tiles/brick.png", Vector2{position.x, position.y}, Vector2{32, 32}, Rectangle{16, 0, 8, 8}, Vector2{-200, -500});
    std::shared_ptr<Entity> brickPiece2 = std::make_shared<BrickPiece>("./assets/tiles/brick.png", Vector2{position.x + 32, position.y}, Vector2{32, 32}, Rectangle{24, 0, 8, 8}, Vector2{200, -500});
    std::shared_ptr<Entity> brickPiece3 = std::make_shared<BrickPiece>("./assets/tiles/brick.png", Vector2{position.x, position.y + 32}, Vector2{32, 32}, Rectangle{16, 8, 8, 8}, Vector2{-200, -250});
    std::shared_ptr<Entity> brickPiece4 = std::make_shared<BrickPiece>("./assets/tiles/brick.png", Vector2{position.x + 32, position.y + 32}, Vector2{32, 32}, Rectangle{24, 8, 8, 8}, Vector2{200, -250});
    brickPieces.push_back(brickPiece1);
    brickPieces.push_back(brickPiece2);
    brickPieces.push_back(brickPiece3);
    brickPieces.push_back(brickPiece4);
}

std::shared_ptr<TileInstance> TileManager::addTileInstance(Vector2 pos, int tileID) {
    std::shared_ptr<TileInstance> tileInstance = nullptr;
    switch ( tileID ) {
        case 1: tileInstance = std::make_shared<PipeInstance2>(pos, tileMap[tileID]); break;
        case 2: tileInstance = std::make_shared<BackgroundInstance>(pos, tileMap[tileID]); break;
        case 4: tileInstance = std::make_shared<FortressInstance>(pos, tileMap[tileID]); break;
        case 7: tileInstance = std::make_shared<GoalpoleInstance>(pos, tileMap[tileID]); break;
        case 8: tileInstance = std::make_shared<GroundInstance>(pos, tileMap[tileID]); break;
        case 9: tileInstance = std::make_shared<HardblockInstance>(pos, tileMap[tileID]); break;
        case 10: tileInstance = std::make_shared<PipeInstance1>(pos, tileMap[tileID]); break;
        case 12: tileInstance = std::make_shared<PipeInstance3>(pos, tileMap[tileID]); break;
        case 13: tileInstance = std::make_shared<QuestionInstance>(pos, tileMap[tileID]); break;
        case 17: tileInstance = std::make_shared<BrickInstance>(pos, tileMap[tileID]); break;
        default: break;
    }
    if ( tileInstance ) tileInstances.push_back(tileInstance);
    return tileInstance;
}

void TileManager::update(Mario& player){
    float et = GetFrameTime();
    

    for ( int i = 0; i < tileInstances.size(); i++ ) {
        tileInstances[i]->update(player);

        // Check for broken brick to remove
        switch( tileInstances[i]->getState() ) {
            case STATE_BROKEN: {
                toRemoveTiles.push_back(i);
                handleBrickPieces( tileInstances[i]->getPos() );
            } break;
            default: break;
        }

        // Check for collision
        if ( aabb::CheckCollisionStaticRectDynamicRect(&player.rect, player.velocity, tileInstances[i]->getBBox(), cp, cn, t, et) ) 
            z.push_back({i, t});

    }
    
    // Resolve collision
    std::sort(z.begin(), z.end(), compare);
    for ( auto j : z ) 
        aabb::ResolveStaticRectDynamicRect(&player.rect, player.velocity, et, &tileInstances[j.first]->getBBox());

    std::sort(toRemoveTiles.rbegin(), toRemoveTiles.rend());
    for ( const auto& idx : toRemoveTiles ) 
        tileInstances.erase(tileInstances.begin() + idx);
    toRemoveTiles.clear();


    for ( int i = 0; i < brickPieces.size(); i++ ) {
        brickPieces[i]->Update();
        // Check for out-of-screen brick pieces to remove
        if ( brickPieces[i]->isOutOfScreen )
            toRemoveEntities.push_back(i);
    }
    std::sort(toRemoveEntities.rbegin(), toRemoveEntities.rend());
    for ( const auto& idx : toRemoveEntities ) 
        brickPieces.erase(brickPieces.begin() + idx);
    toRemoveEntities.clear();

}

void TileManager::render() {
    for (const auto& tileInstance : tileInstances) {
        tileInstance->render();
        DrawRectangleLinesEx(tileInstance->getBBox(), 2.0f, RED); // Debug: Draw bounding box
    }
    for ( const auto& brickPiece : brickPieces ) {
        brickPiece->Draw();
    }
}

World1_1::World1_1(const std::string& fileName) {
    std::ifstream fin(fileName);
    if ( fin.is_open() ){
        for (int i = 0; i < GRID_HEIGHT; ++i)
            for (int j = 0; j < GRID_WIDTH; ++j) {
                fin >> grid[i][j];
                Vector2 pos = Vector2{ j * TILE_SIZE * SCALE, i * TILE_SIZE * SCALE };
                tileManager.addTileInstance(pos, grid[i][j]);
            }
        fin.close();
    }
}

void World1_1::update(Mario& player){
    tileManager.update(player);
}

void World1_1::render() {
    tileManager.render();
}


// void sHandleCollision( Mario& player, Rectangle& tileBBox ) {
// THEORY 
// Point VS Rectangle
// Detection
// px > x && px < x + w
// py > y && py < y + h

// Rectangle VS Rectangle
// Note: x and y are the top-left corner of the rectangle
// Horizontal Overlap
    // Detection
    // y_1 < y_2 + h_2 && y_2 < y_1 + h_1
// Vertical Overlap 
    // Detection
    // x_1 < x_2 + w_2 && x_2 < x_1 + w_1
// Overlap if both Hor and Vert are true

// Note: x and y are center of the rectangle
// ox = ( w_1 + w_2 ) / 2 - dx > 0 if overlap x
// oy = ( h_1 + h_2 ) / 2 - dy > 0 if overlap y

// Resolution
// Determine direction of movement
    // Previous frame
    // oy > 0 -> Movement came from the side -> Pushing in x direction
    // ox > 0 -> Movement came from the top or bottom -> Pushing in y direction
        // Top detection
        // ox > 0 && its y is lower ( player is higher than tile )
        // Bottom detection
        // ox > 0 && its y is higher ( player is lower than tile )

// IMPLEMENTATION
//     Rectangle playerBBox = player.rect;
//     float pHW = playerBBox.width / 2, 
//           pHH = playerBBox.height / 2,
//           tHW = tileBBox.width / 2,
//           tHH = tileBBox.height / 2;

//     float deltaX = (playerBBox.x + pHW) - (tileBBox.x + tHW);
//     float deltaY = (playerBBox.y + pHH) - (tileBBox.y + tHH);

//     float overlapX = ((pHW + tHW) - std::abs(deltaX));
//     float overlapY = ((pHH + tHH) - std::abs(deltaY));

//     if (overlapX < overlapY) { // Movement come from 2 sides
//         if (playerBBox.x < tileBBox.x) { // Left
//             player.position.x -= overlapX;
//         } else { // Right 
//             player.position.x += overlapX;
//         }
//         player.velocity.x = 0; 
//     } else { // Movement come from above or below 
//         if (playerBBox.y < tileBBox.y) { // Above
//             player.position.y -= overlapY;
//         } else { // Below 
//             player.position.y += overlapY;
//         }
//         player.velocity.y = 0;
//         player.position.y = (int)(player.position.y / 64.0f ) * 64.0f; // Align to grid 
//     }
//     // Update Mario's bounding box after position change
//     player.rect.x = player.position.x;
//     player.rect.y = player.position.y;
// }

// void TileInstance::handleCollision( Mario& player ) {
//     Rectangle playerBBox = player.rect;
//     if ( CheckCollisionRecs(playerBBox, bbox) ) {
//         sHandleCollision(player, bbox );
//     }
// }
