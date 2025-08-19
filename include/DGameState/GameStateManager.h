#pragma once
#include <vector>
#include <string>
#include <memory>
#include "DCore/GameContext.h"
#include "DCore/GameState.h"

class GameStateManager
{
    private:
        std::vector<std::unique_ptr<GameState>> states;
        GameContext context;
        bool exiting;
    public:
        GameStateManager();
        ~GameStateManager();

        GameContext& getContext() { return context; }
        void requestExit() {exiting = true;}
        bool isExiting() const { return exiting; } 

        void pushState(GameState* state);
        void popState();
        void changeState(GameState* newState);
        void update();
        void draw();   
    
    public:
    template<typename T>
    T* findState()
    {
        for (auto it = states.rbegin(); it != states.rend(); ++it) 
        {
            if (auto ptr = dynamic_cast<T*>(it->get())) 
            {
                return ptr;
            }
        }
        return nullptr;
    }
};