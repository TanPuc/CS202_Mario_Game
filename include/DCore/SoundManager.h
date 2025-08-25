#pragma once
#include <iostream>
#include "raylib.h"
#include <string>
#include <map>

enum class SoundEffect
{
    JUMP,
    COIN,
    FIRE_BALL,
    POWERUP,
    LEVEL_START,
    PLAYER_DOWN,
    GAME_OVER
};

enum class MusicTrack
{
    MAIN_THEME,
};

class SoundManager
{
private:
    std::map<SoundEffect, Sound> sfx;
    std::map<MusicTrack, Music> musicTracks;

    float musicVolume = 0.5f;
    float sfxVolume = 0.5f;

    Music currentMusic;
    bool isMusicPlaying = false;

    float musicVolumeBeforeMute;
    float sfxVolumeBeforeMute;

    SoundManager() = default;

public:
    SoundManager(const SoundManager &) = delete;
    SoundManager &operator=(const SoundManager &) = delete;

    static SoundManager &getInstance()
    {
        static SoundManager instance;
        return instance;
    }

    void load()
    {
        sfx[SoundEffect::JUMP] = LoadSound("assets/smb_jump-small.wav");
        sfx[SoundEffect::COIN] = LoadSound("assets/smb_coin.wav");
        sfx[SoundEffect::LEVEL_START] = LoadSound("assets/smb_stage_clear.wav");
        sfx[SoundEffect::PLAYER_DOWN] = LoadSound("assets/smb_mariodie.wav");
        sfx[SoundEffect::FIRE_BALL] = LoadSound("assets/smb_fireball.wav");
        sfx[SoundEffect::GAME_OVER] = LoadSound("assets/smb_game_over.wav");
        musicTracks[MusicTrack::MAIN_THEME] = LoadMusicStream("assets/Ground_Theme.mp3");

        setSFXVolume(sfxVolume);
        setMusicVolume(musicVolume);
    }

    void unload()
    {
        for (auto const &[key, val] : sfx)
        {
            UnloadSound(val);
        }

        sfx.clear();

        for (auto const &[key, val] : musicTracks)
        {
            UnloadMusicStream(val);
        }

        musicTracks.clear();
    }

    void playSound(SoundEffect effect)
    {
        if (sfx.count(effect))
        {
            PlaySound(sfx[effect]);
        }
    }

    void playMusic(MusicTrack track)
    {
        if (musicTracks.count(track))
        {
            currentMusic = musicTracks[track];
            PlayMusicStream(currentMusic);
            isMusicPlaying = true;
        }
    }

    void updateMusicStreams()
    {
        if (isMusicPlaying)
        {
            UpdateMusicStream(currentMusic);
        }
    }

    void setMusicVolume(float volume)
    {
        musicVolume = volume;
        if (musicVolume < 0.0f)
            musicVolume = 0.0f;
        if (musicVolume > 1.0f)
            musicVolume = 1.0f;

        ::SetMusicVolume(currentMusic, musicVolume);
    }

    void setSFXVolume(float volume)
    {
        sfxVolume = volume;
        if (sfxVolume < 0.0f)
            sfxVolume = 0.0f;
        if (sfxVolume > 1.0f)
            sfxVolume = 1.0f;

        for (auto &[key, val] : sfx)
        {
            SetSoundVolume(val, sfxVolume);
        }
    }

    float getMusicVolume() const
    {
        return musicVolume;
    }

    float getSFXVolume() const
    {
        return sfxVolume;
    }

    void stopMusic()
    {
        StopMusicStream(currentMusic);
        isMusicPlaying = false;
    }

    bool isMusicCurrentlyPlaying() const
    {
        return isMusicPlaying && IsMusicStreamPlaying(currentMusic);
    }

    void toggleMusicMute()
    {
        if (musicVolume > 0.0f)
        {
            musicVolumeBeforeMute = musicVolume;
            setMusicVolume(0.0f);
        }
        else
        {
            setMusicVolume(musicVolumeBeforeMute > 0.0f ? musicVolumeBeforeMute : 0.5f);
        }
    }

    void toggleSFXMute()
    {
        if (sfxVolume > 0.0f)
        {
            sfxVolumeBeforeMute = sfxVolume;
            setSFXVolume(0.0f);
        }
        else
        {
            setSFXVolume(sfxVolumeBeforeMute > 0.0f ? sfxVolumeBeforeMute : 0.8f);
        }
    }
};
