#pragma once
#include "GameData.h"
#include <string>
#include <fstream>
#include <iostream>

class SaveManager
{
public:
    static bool saveGame(const GameData& data, const std::string& filePath)
    {
        std::ofstream outFile(filePath, std::ios::binary);
        if (!outFile)
        {
            std::cerr << "Error: Could not open file for writing: " << filePath << std::endl;
            return false;
        }

        // Write game data to file
        outFile.write(reinterpret_cast<const char*>(&data), sizeof(GameData));
        outFile.close();

        std::cout << "Game saved successfully to: " << filePath << std::endl;
        return true;
    }

    static bool loadGame(GameData& data, const std::string& filePath)
    {
        std::ifstream inFile(filePath, std::ios::binary);
        if (!inFile)
        {
            std::cerr << "Error: Could not open file for reading: " << filePath << std::endl;
            return false;
        }

        // Read game data from file
        inFile.read(reinterpret_cast<char*>(&data), sizeof(GameData));
        inFile.close();

        if (inFile.gcount() != sizeof(GameData)) 
        {
            std::cerr << "Error: Save file is corrupted or has wrong size." << std::endl;
            return false;
        }

        std::cout << "Game loaded successfully from: " << filePath << std::endl;
        return true;
    }

    static bool saveFileExists(const std::string& filePath)
    {
        std::ifstream inFile(filePath, std::ios::binary);
        return inFile.good();
    }
};
