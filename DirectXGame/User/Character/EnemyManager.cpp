#include "EnemyManager.h"
#include"ColliderManager.h"

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Initialize(EnemyData& enemyData)
{
	Load(enemyData);

	for (std::unique_ptr<Enemy>& enemy : normalEnemys_)
	{
		enemy->Initialize();
		ColliderManager::GetInstance()->AddEnemyCollider(enemy.get());
	}
}

void EnemyManager::Update(Camera* camera, Player* player, GameTimer* gameTimer)
{
	normalEnemys_.remove_if([](std::unique_ptr<Enemy>& enemy) { return enemy->GetIsDead(); });
	for (const std::unique_ptr<Enemy>& enemy : normalEnemys_)
	{
		enemy->Update(camera, player, gameTimer);
	}
}

void EnemyManager::Draw()
{
	for (const std::unique_ptr<Enemy>& enemy : normalEnemys_)
	{
		enemy->Draw();
	}
}

void EnemyManager::Load(EnemyData& enemyData)
{
	std::swap(normalEnemys_, enemyData.normalEnemys);
}

void EnemyManager::ReLoad(EnemyData& enemyData)
{
	Reset();
	Initialize(enemyData);
}

void EnemyManager::Reset()
{
	normalEnemys_.clear();
}

const std::list<std::unique_ptr<Enemy>>& EnemyManager::GetEnemyList()
{
	return normalEnemys_;
}