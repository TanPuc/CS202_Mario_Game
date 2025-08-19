#include "Enemy/enemySprite.h"

#include "Enemy/enemy.h"
#include "Mario.h"

#include <iostream>
using namespace std;

SpriteEnemy::SpriteEnemy() = default;
SpriteEnemy::SpriteEnemy(Mario* mario) :
    m_mario(mario) {}
SpriteEnemy::~SpriteEnemy() = default;


void SpriteEnemy::draw(Enemy& e)
{
    SpriteConfig sprite = m_Sprites[m_CurrentState];

    Rectangle src = sprite.m_FrameRect;
    src.x = sprite.m_offset + src.width * m_CurrentFrame;

    if (!m_mario) src.width *= e.getDirectionSelf() ;
    else
    {
        if (e.GetPosition().x + e.getHurtBox().width / 2 <= m_mario->position.x + m_mario->rect.width / 2)
        {
            src.width *= -1;
        }
    }

    Rectangle dest = e.getHurtBox();
    dest.width *= m_OffSet.width;
    dest.height *= m_OffSet.height;
    dest.y += m_OffSet.y * TILEFACTOR;
    dest.x += m_OffSet.x * TILEFACTOR;
    dest.width -= m_OffSet.x * TILEFACTOR;
    dest.height -= m_OffSet.y * TILEFACTOR;

    DrawTexturePro(sprite.m_Texture, src, dest, { 0,0 }, 0, WHITE);
}

void SpriteEnemy::update(Enemy& e)
{
    m_AnimationTimer += GetFrameTime();
    if (m_AnimationTimer >= m_Sprites[m_CurrentState].m_FrameTime) {
        m_AnimationTimer = 0;
        cout << m_Sprites[m_CurrentState].m_FrameCount;
        m_CurrentFrame = (m_CurrentFrame + 1) % m_Sprites[m_CurrentState].m_FrameCount;
    }
}

void SpriteEnemy::addSpriteConfig(StateType state, const SpriteConfig& config)
{
    m_Sprites[state] = config;
}

void SpriteEnemy::setCurrentState(StateType state)
{
    m_CurrentState = state;
    m_CurrentFrame = 0;
}

void SpriteEnemy::setOffSetPosition(Rectangle offset)
{
    m_OffSet = offset;
}