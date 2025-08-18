#include "DGameState/SettingState.h"
#include "DGUI/Button.h"
#include "DGUI/ImageButton.h"
#include "DCore/SoundManager.h"
#include "DCore/ResourceManager.h"
#include "DGameState/MenuState.h"
#include <iostream>

SettingState::SettingState(GameStateManager *manager)
    : gsm(manager), guiManager(GUIManager::getInstance()) {}

void SettingState::buildGUI()
{
    guiManager.clearElements();

    // float barWidth = 300;
    // float barHeight = 20;
    // float screenCenterX = GetScreenWidth() / 2.0f;

    // musicSliderBar = {screenCenterX - barWidth / 2, 150, barWidth, barHeight};
    // sfxSliderBar = {screenCenterX - barWidth / 2, 250, barWidth, barHeight};

    // musicSliderHandle = {0, musicSliderBar.y - 5, 10, barHeight + 10};
    // sfxSliderHandle = {0, sfxSliderBar.y - 5, 10, barHeight + 10};

    // float musicVolume = SoundManager::getInstance().getMusicVolume();
    // musicSliderHandle.x = musicSliderBar.x + musicVolume * musicSliderBar.width - musicSliderHandle.width/2;

    // float sfxVolume = SoundManager::getInstance().getSFXVolume();
    // sfxSliderHandle.x = sfxSliderBar.x + sfxVolume * sfxSliderBar.width - sfxSliderHandle.width/2;

    //Music Mute button
    musicMuteButton = std::make_unique<ImageButton>(
        Vector2{musicBarRect.x - 45, musicBarRect.y - 5},
        Vector2{40, 40},
        SoundManager::getInstance().getMusicVolume() > 0.0f ? soundOnIcon : soundOffIcon,
        "",
        []() {SoundManager::getInstance().toggleMusicMute();}
    );

    //SFX Mute button
    sfxMuteButton = std::make_unique<ImageButton>(
        Vector2{sfxBarRect.x - 45, sfxBarRect.y - 5},
        Vector2{40, 40},
        SoundManager::getInstance().getSFXVolume() > 0.0f ? soundOnIcon : soundOffIcon,
        "",
        []() {SoundManager::getInstance().toggleSFXMute();}
    );

    //Back
    float aspectRatio = (float)buttonTexture.width / (float)buttonTexture.height;
    float buttonWidth = 170.0f;
    float buttonHeight = buttonWidth / aspectRatio;
    Vector2 buttonSize = { buttonWidth, buttonHeight };
    guiManager.addElement(new ImageButton({150, 328}, buttonSize, buttonTexture, "BACK",
        [this]()
        {
            this->gsm->popState();
        }
    ));
}
void SettingState::enter()
{
    std::cout << "Entering Settings State" << std::endl;
    buttonTexture = LoadTexture("assets/button.png");
    soundOnIcon = LoadTexture("assets/sound_on.png");
    soundOffIcon = LoadTexture("assets/sound_off.png");
    settingTexture = LoadTexture("assets/settingBoard.png");
    volumeBarTextures.clear();
    for (int i=0; i<=5; ++i)
    {
        std::string filePath = "assets/volume_bar_" + std::to_string(i) + ".png";
        volumeBarTextures.push_back(LoadTexture(filePath.c_str()));
    }

    float barWidth = 300.0f;
    float barAspectRatio = (float)volumeBarTextures[0].width / (float)volumeBarTextures[0].height;
    float barHeight = barWidth / barAspectRatio;
    float screenCenterX = GetScreenWidth() / 2.0f;
    Vector2 barSize = { barWidth, barHeight };
    Rectangle sourceRec = { 0.0f, 0.0f, (float)volumeBarTextures[0].width, (float)volumeBarTextures[0].height };
    Rectangle destRec = { 70, 120, barSize.x, barSize.y };
    Vector2 origin = { 0, 0 };
    DrawTexturePro(settingTexture, sourceRec, destRec, origin, 0.0f, WHITE);

    musicBarRect = { 110, 202, barWidth, barHeight };
    sfxBarRect = { 110, 282, barWidth, barHeight };
    buildGUI();
}

void SettingState::exit()
{
    std::cout << "Exiting Settings State" << std::endl;
    guiManager.clearElements();
    UnloadTexture(soundOnIcon);
    UnloadTexture(soundOffIcon);
    UnloadTexture(settingTexture);
    UnloadTexture(buttonTexture);
    for (const auto& texture : volumeBarTextures)
    {
        UnloadTexture(texture);
    }
    volumeBarTextures.clear();
}

void SettingState::update()
{
    Vector2 mousePos = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        //music track
        if (CheckCollisionPointRec(mousePos, musicBarRect))
        {
            float clickPositionX = (mousePos.x - musicBarRect.x) / musicBarRect.width;
            int segment = (int)ceil(clickPositionX * 5.0f);
            if (segment == 0 && clickPositionX > 0.01f) segment = 1;
            if (segment > 5) segment = 5;
            float newVolume = segment / 5.0f;
            SoundManager::getInstance().setMusicVolume(newVolume);
            SoundManager::getInstance().playSound(SoundEffect::COIN); // Phản hồi âm thanh
        }

        //SFX
        if (CheckCollisionPointRec(mousePos, sfxBarRect))
        {
            float clickPositionX = (mousePos.x - sfxBarRect.x) / sfxBarRect.width;
            int segment = (int)ceil(clickPositionX * 5.0f);
            if (segment == 0 && clickPositionX > 0.01f) segment = 1;
            if (segment > 5) segment = 5;
            float newVolume = segment / 5.0f;
            SoundManager::getInstance().setSFXVolume(newVolume);
            SoundManager::getInstance().playSound(SoundEffect::COIN);
        }

        ///mute
        if (musicMuteButton->contains(mousePos)) musicMuteButton->onClick();
        if (sfxMuteButton->contains(mousePos)) sfxMuteButton->onClick();
    }

    musicMuteButton->texture = SoundManager::getInstance().getMusicVolume() > 0 ? soundOnIcon : soundOffIcon;
    sfxMuteButton->texture = SoundManager::getInstance().getSFXVolume() > 0 ? soundOnIcon : soundOffIcon;
    musicMuteButton->update();
    sfxMuteButton->update();

    guiManager.handleInput();
}

void SettingState::draw()
{
    Font font = ResourceManager::GetInstance().GetGameFont();
    
    //Setting board bg
    float aspectRatio = (float)settingTexture.width / (float)settingTexture.height;
    float backgroundWidth = 400.0f;
    float backgroundHeight = backgroundWidth / aspectRatio;
    Vector2 backgroundSize = { backgroundWidth, backgroundHeight };
    Rectangle sourceRec = { 0.0f, 0.0f, (float)settingTexture.width, (float)settingTexture.height };
    Rectangle destRec = { 40, 120, backgroundSize.x, backgroundSize.y };
    Vector2 origin = { 0, 0 };
    DrawTexturePro(settingTexture, sourceRec, destRec, origin, 0.0f, WHITE);

    const char* title = "SETTINGS";
    Vector2 titleSize = MeasureTextEx(font, title, 35, 3.0f);
    DrawTextEx(font, title, {50 + (backgroundSize.x - titleSize.x) / 2 + 3, 133}, 35, 3.0f, Fade(BLACK, 0.5f));
    DrawTextEx(font, title, {50 + (backgroundSize.x - titleSize.x) / 2, 130}, 35, 3.0f, WHITE);

    DrawTextEx(font, "MUSIC VOLUME", {musicBarRect.x, musicBarRect.y - 20}, 15, 1.0f, WHITE);
    DrawTextEx(font, "SFX VOLUME", {sfxBarRect.x, sfxBarRect.y - 20}, 15, 1.0f, WHITE);

    //Draw music bar
    {
        float musicVolume = SoundManager::getInstance().getMusicVolume();
        int textureIndex = (int)(musicVolume * 5.0f + 0.5f);
        if (textureIndex > 5) textureIndex = 5;
        DrawTexturePro(volumeBarTextures[textureIndex], {0,0, (float)volumeBarTextures[textureIndex].width, (float)volumeBarTextures[textureIndex].height}, musicBarRect, {0,0}, 0.0f, WHITE);
    }

    //Draw sfx bar
    {
        float sfxVolume = SoundManager::getInstance().getSFXVolume();
        int textureIndex = (int)(sfxVolume * 5.0f + 0.5f);
        if (textureIndex > 5) textureIndex = 5;
        DrawTexturePro(volumeBarTextures[textureIndex], {0,0, (float)volumeBarTextures[textureIndex].width, (float)volumeBarTextures[textureIndex].height}, sfxBarRect, {0,0}, 0.0f, WHITE);
    }

    // DrawRectangleRec(musicBarRect, DARKGRAY);
    // DrawRectangleRec(sfxBarRect, DARKGRAY);

    musicMuteButton->draw();
    sfxMuteButton->draw();

    guiManager.draw();
}

void SettingState::resume()
{
    std::cout << "Resuming Settings State" << std::endl;
    buildGUI();
}