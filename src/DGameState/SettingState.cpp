#include "DGameState/SettingState.h"
#include "DGUI/Button.h"
#include "DCore/SoundManager.h"
#include "DCore/ResourceManager.h"
#include "DGameState/MenuState.h"
#include <iostream>

SettingState::SettingState(GameStateManager *manager)
    : gsm(manager), guiManager(GUIManager::getInstance()) {}

void SettingState::enter()
{
    std::cout << "Entering Settings State" << std::endl;
    guiManager.clearElements();

    float barWidth = 300;
    float barHeight = 20;
    float screenCenterX = GetScreenWidth() / 2.0f;

    musicSliderBar = {screenCenterX - barWidth / 2, 150, barWidth, barHeight};
    sfxSliderBar = {screenCenterX - barWidth / 2, 250, barWidth, barHeight};

    musicSliderHandle = {0, musicSliderBar.y - 5, 10, barHeight + 10};
    sfxSliderHandle = {0, sfxSliderBar.y - 5, 10, barHeight + 10};

    float musicVolume = SoundManager::getInstance().getMusicVolume();
    musicSliderHandle.x = musicSliderBar.x + musicVolume * musicSliderBar.width - musicSliderHandle.width/2;

    float sfxVolume = SoundManager::getInstance().getSFXVolume();
    sfxSliderHandle.x = sfxSliderBar.x + sfxVolume * sfxSliderBar.width - sfxSliderHandle.width/2;

    //Back
    guiManager.addElement(new Button({screenCenterX - 100, 350}, {200, 50}, "BACK", 
        [this]() 
        {
            this->gsm->changeState(new MenuState(this->gsm));
        }
    ));
}

void SettingState::exit()
{
    std::cout << "Exiting Settings State" << std::endl;
    guiManager.clearElements();
}

void SettingState::update()
{
    Vector2 mousePos = GetMousePosition();
    //Check dragging for music slider
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, musicSliderBar))
    {
        isDraggingMusic = true;
    }

    if (isDraggingMusic)
    {
        float newX = mousePos.x;
        if (newX < musicSliderBar.x) newX = musicSliderBar.x;
        if (newX > musicSliderBar.x + musicSliderBar.width) newX = musicSliderBar.x + musicSliderBar.width;

        musicSliderHandle.x = newX - musicSliderHandle.width / 2;
        float volume = (newX - musicSliderBar.x) / musicSliderBar.width;
        SoundManager::getInstance().setMusicVolume(volume);
    }

    //Check dragging for SFX slider
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, sfxSliderBar))
    {
        isDraggingSFX = true;
    }

    if (isDraggingSFX)
    {
        float newX = mousePos.x;
        if (newX < sfxSliderBar.x) newX = sfxSliderBar.x;
        if (newX > sfxSliderBar.x + sfxSliderBar.width) newX = sfxSliderBar.x + sfxSliderBar.width;

        sfxSliderHandle.x = newX - sfxSliderHandle.width / 2;
        float volume = (newX - sfxSliderBar.x) / sfxSliderBar.width;
        SoundManager::getInstance().setSFXVolume(volume);
    }

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        isDraggingMusic = false;
        isDraggingSFX = false;
    }

    guiManager.handleInput();
}

void SettingState::draw()
{
    ClearBackground(BLACK);
    Font font = ResourceManager::GetInstance().GetGameFont();

    const char* title = "SETTINGS";
    Vector2 titleSize = MeasureTextEx(font, title, 50, 3.0f);
    DrawTextEx(font, title, {GetScreenWidth() / 2 - titleSize.x / 2, 50}, 50, 3.0f, WHITE);

    DrawTextEx(font, "MUSIC VOLUME", {musicSliderBar.x, musicSliderBar.y - 30}, 20, 1.0f, WHITE);
    DrawTextEx(font, "SFX VOLUME", {sfxSliderBar.x, sfxSliderBar.y - 30}, 20, 1.0f, WHITE);

    DrawRectangleRec(musicSliderBar, DARKGRAY);
    DrawRectangleRec(musicSliderHandle, SKYBLUE);
    DrawRectangleRec(sfxSliderBar, DARKGRAY);
    DrawRectangleRec(sfxSliderHandle, SKYBLUE);

    guiManager.draw();
}