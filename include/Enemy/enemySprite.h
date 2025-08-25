#pragma once

#include <unordered_map>

#include "raylib.h"

#include "enemyEnum.h"

using namespace std;

class Enemy;
class Character;


struct SpriteConfig
{
	Texture2D	m_Texture;
	Rectangle	m_FrameRect;
	int			m_offset;
	int			m_FrameCount;
	float		m_FrameTime;
};

class SpriteEnemy
{
public:
	SpriteEnemy();
	SpriteEnemy(Character*);
	~SpriteEnemy();

	void draw(Enemy& e);
	void update(Enemy& e);
	void addSpriteConfig(StateType state, const SpriteConfig& config);
	void setCurrentState(StateType state);
	void setOffSetPosition(Rectangle offset);

private:
	unordered_map<StateType, SpriteConfig>		m_Sprites;
	StateType									m_CurrentState		= StateType::Nothing;
	float										m_AnimationTimer	= 0;
	int											m_CurrentFrame		= 0;
	Rectangle									m_OffSet			= { 0,0,1,1 };
	Character*										m_mario				= nullptr;
};
