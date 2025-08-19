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

    if(!states.empty())
    {
        states.back()->resume();
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
    if (states.empty()) return;

    size_t first_state_to_draw = 0;
    for (int i = states.size() - 1; i >= 0; --i)
    {
        if (states[i]->isOpaque())
        {
            first_state_to_draw = i;
            break;
        }
    }

    for (size_t i = first_state_to_draw; i < states.size(); ++i)
    {
        states[i]->draw();
    }

}