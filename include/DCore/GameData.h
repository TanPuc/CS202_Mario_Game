#pragma once
#include "raylib.h"
#include "GlobalVariables.h"

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

    CHARACTER_FORM playerForm;
    TileState tileStates[GRID_HEIGHT][GRID_WIDTH];

    // std::vector<EntityData> enemiesData;
    // std::vector<EntityData> itemsData;

    GameData()
    {
        lives = 3;
        coins = 0;
        score = 0;
        timeRemaining = 400;

        playerPosition = {0, 141}; // INITIALIZE POSITION
        // playerPosition = { 6000, 141 }; // INITIALIZE POSITION
        worldNum = 1;
        levelNum = 1;
        playerForm = SMALL;
        for (int i = 0; i < GRID_HEIGHT; i++)
        {
            for (int j = 0; j < GRID_WIDTH; j++)
            {
                tileStates[i][j] = STATE_NORMAL;
            }
        }
    }
};