#pragma once
#include "raylib.h"
#include <iostream>

class ResourceManager 
{
    private:
        Font gameFont;
        ResourceManager() = default;
        Texture2D backgroundTexture;
    
    public:
        //Delete copy constructor to ensure singleton
        ResourceManager(const ResourceManager&) = delete;
        ResourceManager& operator=(const ResourceManager&) = delete;

        static ResourceManager& GetInstance()
        {
            static ResourceManager instance;
            return instance;
        }

        void LoadGameFont(const char* filePath)
        {
            gameFont = LoadFont(filePath);
            if (!IsFontValid(gameFont))
            {
                std::cerr << "Failed to load font: " << filePath << std::endl;
            }
            else
            {
                std::cout << "Successfully loaded font\n";
            }
        }

        Font& GetGameFont()
        {
            return gameFont;
        }

        void LoadBackgroundTexture(const char* filePath)
        {
            backgroundTexture = LoadTexture(filePath);
            if (backgroundTexture.id == 0)
            {
                std::cerr << "Failed to load background texture: " << filePath << std::endl;
            }
            else
            {
                std::cout << "Successfully loaded background texture\n";
            }
        }

        Texture2D& GetBackgroundTexture()
        {
            return backgroundTexture;
        }

        void UnloadResources()
        {
            if (IsFontValid(gameFont))
            {
                UnloadFont(gameFont);
            }
            if (backgroundTexture.id > 0)
            {
                UnloadTexture(backgroundTexture);
            }
        }
};