#pragma once
#include <iostream>
#include "raylib.h"
#include <string>
#include <map>

class SoundManager 
{
    private:
        std::map<std::string, Sound> soundEffects;
        std::map<std::string, Music> backgroundMusic;
        SoundManager() = default;
    public:
        SoundManager(const SoundManager&);

};






































// class SoundManager {
// private:
//     std::map<std::string, Sound> soundEffects;
//     std::map<std::string, Music> backgroundMusic;
//     SoundManager() = default;

// public:
//     SoundManager(const SoundManager&) = delete;
//     SoundManager& operator=(const SoundManager&) = delete;

//     static SoundManager& getInstance() {
//         static SoundManager instance;
//         return instance;
//     }

//     ~SoundManager(); // Destructor để giải phóng tài nguyên

//     void loadSoundEffect(const std::string& name, const std::string& filePath);
//     void loadMusic(const std::string& name, const std::string& filePath);
//     void unloadAll();

//     void playSoundEffect(const std::string& name);
//     void playMusic(const std::string& name);
//     void stopMusic(const std::string& name);
//     void updateMusicStreams();
//     void setGlobalVolume(float volume);
// };
