#include "Tile.h"

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

// void Background::render(Vector2 pos) {
//     DrawTextureEx(texture, pos, 0.0f, scale, WHITE);
// }

// Handle collision and return collision type: L: 1, R: 2, A: 3, B: 4
int sHandleCollision( Mario& player, Rectangle& tileBBox ) {
    int collisionType = 0;
    Rectangle playerBBox = player.rect;
    float pHW = playerBBox.width / 2, 
          pHH = playerBBox.height / 2,
          tHW = tileBBox.width / 2,
          tHH = tileBBox.height / 2;

    float deltaX = (playerBBox.x + pHW) - (tileBBox.x + tHW);
    float deltaY = (playerBBox.y + pHH) - (tileBBox.y + tHH);

    float overlapX = ((pHW + tHW) - std::abs(deltaX));
    float overlapY = ((pHH + tHH) - std::abs(deltaY));

    if (overlapX < overlapY) { // Movement come from 2 sides
        if (playerBBox.x < tileBBox.x) { // Left
            player.position.x -= overlapX;
            collisionType = 1; 
        } else { // Right 
            player.position.x += overlapX;
            collisionType = 2;
        }
        player.velocity.x = 0; 
    } else { // Movement come from above or below 
        if (playerBBox.y < tileBBox.y) { // Above
            player.position.y -= overlapY;
            collisionType = 3;
        } else { // Below 
            player.position.y += overlapY;
            collisionType = 4;
        }
        player.velocity.y = 0;
        player.position.y = (int)(player.position.y / 64.0f ) * 64.0f; // Align to grid 
    }
    // Update Mario's bounding box after position change
    player.rect.x = player.position.x;
    player.rect.y = player.position.y;
    return collisionType;
}

TileInstance::TileInstance(Vector2 pos, std::shared_ptr<Tile> tile) 
    : pos(pos), tile(tile), bbox( Rectangle{pos.x, pos.y, 16 * scale, 16 * scale} ) {}

GroundInstance::GroundInstance(Vector2 pos, std::shared_ptr<Tile> ground) 
    : TileInstance(pos, ground) {}

void GroundInstance::handleCollision(Mario& player) {
    Rectangle playerBBox = player.rect;
    Rectangle tileBBox = bbox;
    if (CheckCollisionRecs(playerBBox, tileBBox)) {
        sHandleCollision(player, tileBBox);
    }
}

void GroundInstance::render() {
    DrawTextureEx(tile->getTexture(), pos, 0.0f, scale, WHITE);
}

BrickInstance::BrickInstance(Vector2 pos, std::shared_ptr<Tile> brick) 
    : TileInstance(pos, brick) {}

void BrickInstance::handleCollision(Mario& player) {
    Rectangle playerBBox = player.rect;
    Rectangle tileBBox = bbox;
    if (CheckCollisionRecs(playerBBox, tileBBox)) {
        sHandleCollision(player, tileBBox);   
    }
}

void BrickInstance::render() {
    dest.x = pos.x; dest.y = pos.y;
    DrawTexturePro(tile->getTexture(), normal, dest, Vector2{0, 0}, 0.0f, WHITE);
}

QuestionInstance::QuestionInstance(Vector2 pos, std::shared_ptr<Tile> question) 
    : TileInstance(pos, question) {}

void QuestionInstance::handleCollision(Mario& player) {
    Rectangle playerBBox = player.rect;
    Rectangle tileBBox = bbox;
    if (CheckCollisionRecs(playerBBox, tileBBox)) {
        // Mario can only activate the question block from below
        if ( sHandleCollision(player, tileBBox) == 4 ) {
            switch ( state ) {
                case STATE_NORMAL: {
                    state = STATE_ACTIVATED;
                } break;
                default: break;
            }
        }
    }
}

void QuestionInstance::render() {
    dest.x = pos.x; dest.y = pos.y;
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
    DrawTexturePro(tile->getTexture(), normal, dest, Vector2{0, 0}, 0.0f, WHITE);
}

BackgroundInstance::BackgroundInstance(Vector2 pos, std::shared_ptr<Tile> background) 
    : TileInstance(pos, background) {}

void BackgroundInstance::render() {
    DrawTextureEx(tile->getTexture(), pos, 0.0f, scale, WHITE);
}

PipeInstance1::PipeInstance1(Vector2 pos, std::shared_ptr<Tile> pipe) : TileInstance(pos, pipe) {
    bbox = Rectangle{pos.x, pos.y, 16 * scale * 2, 16 * scale * 2}; }
PipeInstance2::PipeInstance2(Vector2 pos, std::shared_ptr<Tile> pipe) : TileInstance(pos, pipe) {
    bbox = Rectangle{pos.x, pos.y, 16 * scale * 2, 16 * scale * 3}; }
PipeInstance3::PipeInstance3(Vector2 pos, std::shared_ptr<Tile> pipe) : TileInstance(pos, pipe) {
    bbox = Rectangle{pos.x, pos.y, 16 * scale * 2, 16 * scale * 4};
}

void PipeInstance1::handleCollision(Mario& player) {
    Rectangle playerBBox = player.rect;
    Rectangle tileBBox = bbox;
    if (CheckCollisionRecs(playerBBox, tileBBox)) {
        sHandleCollision(player, tileBBox);
    }
}
void PipeInstance2::handleCollision(Mario& player) {
    Rectangle playerBBox = player.rect;
    Rectangle tileBBox = bbox;
    if (CheckCollisionRecs(playerBBox, tileBBox)) {
        sHandleCollision(player, tileBBox);
    }
}
void PipeInstance3::handleCollision(Mario& player) {
    Rectangle playerBBox = player.rect;
    Rectangle tileBBox = bbox;
    if (CheckCollisionRecs(playerBBox, tileBBox)) {
        sHandleCollision(player, tileBBox);
    }
}

void PipeInstance1::render() { DrawTextureEx(tile->getTexture(), pos, 0.0f, scale, WHITE); }
void PipeInstance2::render() { DrawTextureEx(tile->getTexture(), pos, 0.0f, scale, WHITE); }
void PipeInstance3::render() { DrawTextureEx(tile->getTexture(), pos, 0.0f, scale, WHITE); }

HardblockInstance::HardblockInstance(Vector2 pos, std::shared_ptr<Tile> hardblock) 
    : TileInstance(pos, hardblock) {}

void HardblockInstance::handleCollision(Mario& player) {
    Rectangle playerBBox = player.rect;
    Rectangle tileBBox = bbox;
    if (CheckCollisionRecs(playerBBox, tileBBox)) {
        sHandleCollision(player, tileBBox);
    }
}

void HardblockInstance::render() { 
    DrawTextureEx(tile->getTexture(), pos, 0.0f, scale, WHITE); 
}

GoalpoleInstance::GoalpoleInstance(Vector2 pos, std::shared_ptr<Tile> goalpole) 
    : TileInstance(pos, goalpole) {}

void GoalpoleInstance::render() {
    DrawTextureEx(tile->getTexture(), pos, 0.0f, scale, WHITE);
}

FortressInstance::FortressInstance(Vector2 pos, std::shared_ptr<Tile> fortress) 
    : TileInstance(pos, fortress) {}

void FortressInstance::render() {
    DrawTextureEx(tile->getTexture(), pos, 0.0f, scale, WHITE);
}

std::shared_ptr<TileInstance> TileManager::addTileInstance(Vector2 pos, int tileID) {
    std::shared_ptr<TileInstance> tileInstance = nullptr;
    switch ( tileID ) {
        case 1: tileInstance = std::make_shared<PipeInstance2>(pos, pipe2); break;
        case 2: tileInstance = std::make_shared<BackgroundInstance>(pos, background); break;
        case 4: tileInstance = std::make_shared<FortressInstance>(pos, fortress); break;
        case 7: tileInstance = std::make_shared<GoalpoleInstance>(pos, goalpole); break;
        case 8: tileInstance = std::make_shared<GroundInstance>(pos, ground); break;
        case 9: tileInstance = std::make_shared<HardblockInstance>(pos, hardblock); break;
        case 10: tileInstance = std::make_shared<PipeInstance1>(pos, pipe1); break;
        case 12: tileInstance = std::make_shared<PipeInstance3>(pos, pipe3 ); break;
        case 13: tileInstance = std::make_shared<QuestionInstance>(pos, question); break;
        case 17: tileInstance = std::make_shared<BrickInstance>(pos, brick); break;
        default: break;
    }
    if ( tileInstance ) tileInstances.push_back(tileInstance);
    return tileInstance;
}

void TileManager::handleCollision(Mario& player, int** grid) {
    // Sau này chỉ cần kiểm tra block gần player 
    for ( const auto& tileInstance : tileInstances ) {
        tileInstance->handleCollision(player);   
    }
    int minX = player.position.x / TILE_SIZE * SCALE;
    int maxX = (player.position.x + player.rect.width) / TILE_SIZE * SCALE;
    int minY = player.position.y / TILE_SIZE * SCALE;
    int maxY = (player.position.y + player.rect.height) / TILE_SIZE * SCALE
    for ( int y = minY; y <= maxY; ++y ) {
        for ( int x = minX; x <= maxX; ++x ) {
            if ( x > 0 && x < gridWidth && y > 0 && y < gridHeight ) {
                
            }
        }
    }

}

void TileManager::render() {
    for (const auto& tileInstance : tileInstances) {
        tileInstance->render();
        DrawRectangleLinesEx(tileInstance->getBBox(), 2.0f, RED); // Debug: Draw bounding box
    }
}

World1_1::World1_1(const std::string& fileName) {
    std::ifstream fin(fileName);
    if ( fin.is_open() ){
        for (int i = 0; i < gridHeight; ++i)
            for (int j = 0; j < gridWidth; ++j) {
                fin >> grid[i][j];
                Vector2 pos = Vector2{ j * 16.0f * scale, i * 16.0f * scale };
                tileManager.addTileInstance(pos, grid[i][j]);
            }
        fin.close();
    }
}

void World1_1::update( Mario& player ){
    tileManager.handleCollision( player, grid );
}

void World1_1::render() {
    tileManager.render();
}