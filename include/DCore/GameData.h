#pragma once
#include "raylib.h"

struct EnityData
{
    Vector2 position;
};

struct GameData
{
    int lives;
    int coins;
    long long score;
    int timeRemaining;
    Vector2 playerPosition;

    int worldNum;
    int levelNum;

    // std::vector<EntityData> enemiesData;
    // std::vector<EntityData> itemsData;

    GameData()
    {
        lives = 3;
        coins = 0;
        score = 0;
        timeRemaining = 400;
        playerPosition = { 0, 0 }; // INITIALIZE POSITION 
        worldNum = 1;
        levelNum = 1;
    }
};