#ifndef MARIOSTATE_H
#define MARIOSTATE_H

#include <memory>
#include "Mario.h"
#include "GameSprite/Sprite.h"

class Mario;
class Sprite;

class MarioState
{
public:
    virtual ~MarioState() = default;
    virtual std::unique_ptr<MarioState> HandleInput(Mario &entity, Sprite &sprite) = 0;
    virtual std::unique_ptr<MarioState> Update(Mario &entity, Sprite &sprite) = 0;
    virtual void Draw(Mario &entity, Sprite &sprite) = 0;
    virtual STATE GetType() const = 0;
};

#endif
