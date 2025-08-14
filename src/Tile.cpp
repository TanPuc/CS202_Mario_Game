#include "Tile.h"
#include "Mario.h"
#include "BrickPieces.h"

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

bool compare(const std::pair<std::array<int, 2>, float>& a, const std::pair<std::array<int, 2>, float>& b) {
    return a.second < b.second;
}

TileInstance::TileInstance(Vector2 pos, std::shared_ptr<Tile> tile) 
    : pos(pos), tile(tile), bbox( Rectangle{pos.x, pos.y, TILE_SIZE * SCALE, TILE_SIZE * SCALE} ) {}

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
    : TileInstance(pos, brick), hbox(Rectangle{pos.x + 24, pos.y + 60, 16, 6}), dest{pos.x, pos.y, TILE_SIZE * SCALE, TILE_SIZE * SCALE} {}

void BrickInstance::update(Mario& player) {
    dest.x = pos.x; dest.y = pos.y;
    handleBreaking(player);

}

void BrickInstance::render() {
    DrawTexturePro(tile->getTexture(), normal, dest, Vector2{0, 0}, 0.0f, WHITE);
    DrawRectangleLinesEx(hbox, 1.0f, RED); // Draw hitbox 
}

QuestionInstance::QuestionInstance(Vector2 pos, std::shared_ptr<Tile> question) 
    : TileInstance(pos, question), hbox(Rectangle{pos.x + 24, pos.y + 60, 16, 6}), dest{pos.x, pos.y, TILE_SIZE * SCALE, TILE_SIZE * SCALE} {}

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
    handleActivation(player);
    handleAnimation();
}

void QuestionInstance::render() {
    DrawTexturePro(tile->getTexture(), normal, dest, Vector2{0, 0}, 0.0f, WHITE);
    DrawRectangleLinesEx(hbox, 1.0f, RED); // Draw hitbox 
}

BackgroundInstance::BackgroundInstance(Vector2 pos, std::shared_ptr<Tile> background) : TileInstance(pos, background) {
    bbox = Rectangle{0, 0, 0, 0};
}

void BackgroundInstance::render() {
    DrawTextureEx(tile->getTexture(), pos, 0.0f, SCALE, WHITE);
}

PipeInstance1::PipeInstance1(Vector2 pos, std::shared_ptr<Tile> pipe) : TileInstance(pos, pipe) {}
PipeInstance2::PipeInstance2(Vector2 pos, std::shared_ptr<Tile> pipe) : TileInstance(pos, pipe) {}
PipeInstance3::PipeInstance3(Vector2 pos, std::shared_ptr<Tile> pipe) : TileInstance(pos, pipe) {}

void PipeInstance1::update(Mario& player){} 
void PipeInstance2::update(Mario& player){} 
void PipeInstance3::update(Mario& player){} 

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

void TileManager::addTileInstance(Vector2 pos, int tileID, int x, int y) {
    float t = TILE_SIZE * SCALE;
    std::shared_ptr<TileInstance> tileInstance = nullptr;
    switch ( tileID ) {
        case 1: {
            tileInstance = std::make_shared<PipeInstance2>(pos, tileMap[tileID]);
            tileInstancesGrid[x][y+1] = std::make_shared<DummyInstance>(Vector2{ pos.x + t, pos.y});
            tileInstancesGrid[x+1][y] = std::make_shared<DummyInstance>(Vector2{ pos.x, pos.y + t});
            tileInstancesGrid[x+1][y+1] = std::make_shared<DummyInstance>(Vector2{ pos.x + t, pos.y + t});
            tileInstancesGrid[x+2][y] = std::make_shared<DummyInstance>(Vector2{pos.x, pos.y + 2 * t});
            tileInstancesGrid[x+2][y+1] = std::make_shared<DummyInstance>(Vector2{pos.x + t, pos.y + 2 * t});
        } break;
        case 2: tileInstance = std::make_shared<BackgroundInstance>(pos, tileMap[tileID]); break;
        case 4: tileInstance = std::make_shared<FortressInstance>(pos, tileMap[tileID]); break;
        case 7: tileInstance = std::make_shared<GoalpoleInstance>(pos, tileMap[tileID]); break;
        case 8: tileInstance = std::make_shared<GroundInstance>(pos, tileMap[tileID]); break;
        case 9: tileInstance = std::make_shared<HardblockInstance>(pos, tileMap[tileID]); break;
        case 10: {
            tileInstance = std::make_shared<PipeInstance1>(pos, tileMap[tileID]);
            tileInstancesGrid[x][y+1] = std::make_shared<DummyInstance>(Vector2{pos.x + t, pos.y});
            tileInstancesGrid[x+1][y] = std::make_shared<DummyInstance>(Vector2{pos.x, pos.y + t});
            tileInstancesGrid[x+1][y+1] = std::make_shared<DummyInstance>(Vector2{pos.x + t, pos.y + t});
        } break;
        case 12: {
            tileInstance = std::make_shared<PipeInstance3>(pos, tileMap[tileID]);
            tileInstancesGrid[x][y+1] = std::make_shared<DummyInstance>(Vector2{pos.x + t, pos.y});
            tileInstancesGrid[x+1][y] = std::make_shared<DummyInstance>(Vector2{pos.x, pos.y + t});
            tileInstancesGrid[x+1][y+1] = std::make_shared<DummyInstance>(Vector2{pos.x + t, pos.y + t});
            tileInstancesGrid[x+2][y] = std::make_shared<DummyInstance>(Vector2{pos.x, pos.y + 2 * t});
            tileInstancesGrid[x+2][y+1] = std::make_shared<DummyInstance>(Vector2{pos.x + t, pos.y + 2 * t});
            tileInstancesGrid[x+3][y] = std::make_shared<DummyInstance>(Vector2{pos.x, pos.y + 3 * t});
            tileInstancesGrid[x+3][y+1] = std::make_shared<DummyInstance>(Vector2{pos.x + t, pos.y + 3 * t});
        } break;
        case 13: tileInstance = std::make_shared<QuestionInstance>(pos, tileMap[tileID]); break;
        case 17: tileInstance = std::make_shared<BrickInstance>(pos, tileMap[tileID]); break;
        default: break;
    }
    if ( tileInstance ) {
        tileInstances.push_back(tileInstance);
        tileInstancesGrid[x][y] = tileInstance; 
    }
}

void TileManager::update(Mario& player){
    // for ( int i = 0; i < tileInstances.size(); i++ ) {
    //     tileInstances[i]->update(player);

    //     // Check for broken brick to remove
    //     switch( tileInstances[i]->getState() ) {
    //         case STATE_BROKEN: {
    //             toRemove.push_back(i);
    //             entityManager.addBrickPieces( tileInstances[i]->getPos() );
    //         } break;
    //         default: break;
    //     }
    // }
    // std::sort(toRemove.rbegin(), toRemove.rend());
    // for ( const auto& idx : toRemove ) 
    //     tileInstances.erase(tileInstances.begin() + idx);
    // toRemove.clear();

    for ( int i = 0; i < GRID_HEIGHT; i++ ) {
        for ( int j = 0; j < GRID_WIDTH; j++ ) {
            if ( tileInstancesGrid[i][j] ) {
                tileInstancesGrid[i][j]->update(player);
                if ( tileInstancesGrid[i][j]->getState() == STATE_BROKEN ) {
                    entityManager.addBrickPieces( tileInstancesGrid[i][j]->getPos() );
                    tileInstancesGrid[i][j] = nullptr; 
                }
            }
        }
    }

    entityManager.update();

}

void TileManager::render() {
    // for (const auto& tileInstance : tileInstances) {
    //     tileInstance->render();
    //     DrawRectangleLinesEx(tileInstance->getBBox(), 2.0f, RED); // Debug: Draw bounding box
    // }
    
    for ( int i = 0; i < GRID_HEIGHT; i++ ) {
        for ( int j = 0; j < GRID_WIDTH; j++ ) {
            if ( tileInstancesGrid[i][j]) {
                tileInstancesGrid[i][j]->render();
                DrawRectangleLinesEx(tileInstancesGrid[i][j]->getBBox(), 2.0f, RED); // Debug: Draw bounding box
            }
        }
    }
    entityManager.render();
}

void EntityManager::addBrickPieces(Vector2 position) {
    std::shared_ptr<BrickPiece> brickPiece1 = std::make_shared<BrickPiece>("./assets/tiles/brick.png", Vector2{position.x, position.y}, Vector2{32, 32}, Rectangle{16, 0, 8, 8}, Vector2{-200, -500});
    std::shared_ptr<BrickPiece> brickPiece2 = std::make_shared<BrickPiece>("./assets/tiles/brick.png", Vector2{position.x + 32, position.y}, Vector2{32, 32}, Rectangle{24, 0, 8, 8}, Vector2{200, -500});
    std::shared_ptr<BrickPiece> brickPiece3 = std::make_shared<BrickPiece>("./assets/tiles/brick.png", Vector2{position.x, position.y + 32}, Vector2{32, 32}, Rectangle{16, 8, 8, 8}, Vector2{-200, -250});
    std::shared_ptr<BrickPiece> brickPiece4 = std::make_shared<BrickPiece>("./assets/tiles/brick.png", Vector2{position.x + 32, position.y + 32}, Vector2{32, 32}, Rectangle{24, 8, 8, 8}, Vector2{200, -250});
    brickPieces.push_back(brickPiece1);
    brickPieces.push_back(brickPiece2);
    brickPieces.push_back(brickPiece3);
    brickPieces.push_back(brickPiece4);
}

void EntityManager::update() {
    for ( int i = 0; i < brickPieces.size(); i++ ) {
        brickPieces[i]->Update();
        // Check for out-of-screen brick pieces to remove
        if ( brickPieces[i]->isOutOfScreen )
            toRemove.push_back(i);
    }
    std::sort(toRemove.rbegin(), toRemove.rend());
    for ( const auto& idx : toRemove ) 
        brickPieces.erase(brickPieces.begin() + idx);
    toRemove.clear();
}

void EntityManager::render() {
    for ( const auto& brickPiece : brickPieces ) {
        brickPiece->Draw();
    }
}

Level::Level(const std::string& fileName) {
    int temp = 0;
    std::ifstream fin(fileName);
    if ( fin.is_open() ){
        for (int i = 0; i < GRID_HEIGHT; ++i)
            for (int j = 0; j < GRID_WIDTH; ++j) {
                fin >> temp;
                Vector2 pos = Vector2{ j * TILE_SIZE * SCALE, i * TILE_SIZE * SCALE };
                tileManager.addTileInstance(pos, temp, i, j);
            }
        fin.close();
    }
}

void Level::run(Mario& player) {
    tileManager.update(player);
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
