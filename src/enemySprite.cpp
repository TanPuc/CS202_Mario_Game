#include "enemySprite.h"

#include "enemy.h"

SpriteEnemy::SpriteEnemy() = default;
SpriteEnemy::~SpriteEnemy() = default;


void SpriteEnemy::draw(Enemy& e)
{
    SpriteConfig sprite = m_Sprites[m_CurrentState];

    Rectangle src = sprite.m_FrameRect;
    src.x = sprite.m_offset + src.width * m_CurrentFrame;
    src.width *= e.getDirection() ;

    //DrawTextureRec(sprite.m_Texture, src, e.GetPosition(), WHITE);
    //Rectangle dest = { e.rect.x,e.rect.y, e.rect.width,e.rect.height };

    Rectangle dest = e.rect;

    DrawTexturePro(sprite.m_Texture, src, dest, { 0,0 }, 0, WHITE);
}

void SpriteEnemy::update(Enemy& e)
{
    m_AnimationTimer += GetFrameTime();
    if (m_AnimationTimer >= m_Sprites[m_CurrentState].m_FrameTime) {
        m_AnimationTimer = 0;
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