#pragma once

#include <unordered_map>

#include "raylib.h"
#include "enemyEnum.h"

using namespace std;

class enemyAsset
{
public:
	static void Load();
	static Texture2D GetTexture(EnemyType type);
	static void Unload();
private:
	static unordered_map<EnemyType, Texture2D> m_Textures;
};