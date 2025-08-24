#ifndef MARIOSTATE_H
#define MARIOSTATE_H

#include <memory>
#include "Character.h"
#include "GameSprite/Sprite.h"

class Character;
class Sprite;

class CharacterState
{
public:
    virtual ~CharacterState() = default;
    virtual std::unique_ptr<CharacterState> HandleInput(Character &entity, Sprite &sprite) = 0;
    virtual std::unique_ptr<CharacterState> Update(Character &entity, Sprite &sprite) = 0;
    virtual void Draw(Character &entity, Sprite &sprite) = 0;
    virtual STATE GetType() const = 0;
};

#endif
