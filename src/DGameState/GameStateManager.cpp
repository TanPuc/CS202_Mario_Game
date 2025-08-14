#pragma once
#include "DGameState/GameStateManager.h"
#include "DCore/GameState.h"
#include <iostream> 

GameStateManager::GameStateManager() : exiting(false) {}
GameStateManager::~GameStateManager() 
{
    while (!states.empty()) {
        states.back()->exit();
        states.pop_back();
    }
}

void GameStateManager::pushState(GameState* state) 
{
    if (state) 
    {
        states.emplace_back(state);
        states.back()->enter();
    }
}

void GameStateManager::popState() 
{
    if (!states.empty()) 
    {
        states.back()->exit();
        states.pop_back();
    }
}

void GameStateManager::changeState(GameState* state) 
{
    while (!states.empty()) {
        states.back()->exit();
        states.pop_back();
    }
    pushState(state);
}

void GameStateManager::update()
{
    if (!states.empty()) {
        states.back()->update();
    }
}

void GameStateManager::draw() 
{
    for (const auto& state : states) 
    {
        state->draw();
    }
}