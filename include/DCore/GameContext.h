#pragma once
#include <string>
#include "DCore/GameData.h"

class GameContext
{
    public:
        std::string selectedCharacter = "mario";
        int lives = 3;

        bool checkpointIsSet = false;
        GameData checkpointData;

        long long scoreBeforeRespawn = 0;

        //checkpoint
        // int checkpointWorld = 1;
        // int checkpointLevel = 1;

        // long long currentScore = 0;
        // int currentCoins = 0;

        void resetForNewGame()
        {
            lives = 3;
            checkpointIsSet = false;
            checkpointData = GameData();
            scoreBeforeRespawn = 0;
        }
};
