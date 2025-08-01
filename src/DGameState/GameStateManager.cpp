#pragma once
#include "DGameState/GameStateManager.h"
#include "DCore/GameState.h"

void GameStateManager::changeState(GameState* newState) 
{
    if (currentState) 
    {
        currentState->exit();
    }
    currentState.reset(newState);
    if (currentState) 
    {
        currentState->enter();
    }
}

void GameStateManager::update() 
{
    if (currentState) 
    {
        currentState->update();
    }
}

void GameStateManager::draw() 
{
    if (currentState) 
    {
        currentState->draw();
    }
}