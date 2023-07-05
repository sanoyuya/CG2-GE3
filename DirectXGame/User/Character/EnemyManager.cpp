#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Initialize(EnemyData& enemyData)
{
	Load(enemyData);

	for (const std::unique_ptr<Enemy>& enemy : normalEnemys_)
	{
		enemy->Initialize();
	}
}

void EnemyManager::Update(Camera* camera)
{
	normalEnemys_.remove_if([](std::unique_ptr<Enemy>& enemy) { return enemy->GetIsDead(); });
	for (const std::unique_ptr<Enemy>& enemy : normalEnemys_)
	{
		enemy->Update(camera);
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