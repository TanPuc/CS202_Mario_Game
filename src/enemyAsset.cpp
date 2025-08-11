#include "enemyAsset.h"

unordered_map<EnemyType, Texture2D> enemyAsset::m_Textures;

void enemyAsset::Load()
{
	m_Textures[EnemyType::goopa] = LoadTexture("assets/Enemies/goopa.png");
	m_Textures[EnemyType::beezybettle] = LoadTexture("assets/Enemies/beezybeetle.png");
	m_Textures[EnemyType::blooper] = LoadTexture("assets/Enemies/blooper.png");
	m_Textures[EnemyType::koopa] = LoadTexture("assets/Enemies/koopa.png");
	m_Textures[EnemyType::lakitu] = LoadTexture("assets/Enemies/lakitu.png");
	m_Textures[EnemyType::paratroopa] = LoadTexture("assets/Enemies/paratroopa.png");
	m_Textures[EnemyType::spiny] = LoadTexture("assets/Enemies/spiny.png");
	m_Textures[EnemyType::hammerbro] = LoadTexture("assets/Enemies/hammerbro.png");
	m_Textures[EnemyType::cheepcheep] = LoadTexture("assets/Enemies/cheepcheep.png");
	m_Textures[EnemyType::piranhaplant] = LoadTexture("assets/Enemies/piranhaplant.png");
	m_Textures[EnemyType::bowser] = LoadTexture("assets/Enemies/bowser.png");
	m_Textures[EnemyType::lavabubble] = LoadTexture("assets/Enemies/lavabubble.png");
	m_Textures[EnemyType::bulletbill] = LoadTexture("assets/Enemies/bulletbill.png");
	m_Textures[EnemyType::hammer] = LoadTexture("assets/Enemies/hammer.png");
	m_Textures[EnemyType::fireball] = LoadTexture("assets/Enemies/fireball.png");

}

Texture2D enemyAsset::GetTexture(EnemyType type)
{
	return m_Textures[type];
}

void enemyAsset::Unload()
{
	for (auto& pair : m_Textures)
	{
		UnloadTexture(pair.second);
	}
}