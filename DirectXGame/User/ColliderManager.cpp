#include "ColliderManager.h"

void ColliderManager::Update(Player* player)
{
}

void ColliderManager::PlayerBulletToEnemy()
{
}

void ColliderManager::EnemyBulletToPlayer(Player* player)
{
}

void ColliderManager::SetPlayerBulletList(std::list<std::unique_ptr<Bullet>>& playerBullets)
{
	playerBullets_ = playerBullets;
}

void ColliderManager::SetEnemyList(std::list<std::unique_ptr<Enemy>>& enemys)
{
	enemys_ = enemys;
}

void ColliderManager::SetEnemyBulletList(std::list<std::unique_ptr<Bullet>>& enemyBullets)
{
	enemyBullets_ = enemyBullets;
}

ColliderManager* ColliderManager::GetInstance()
{
	static ColliderManager instance;
	return &instance;
}