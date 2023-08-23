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
	//“G‚ğjsonƒtƒ@ƒCƒ‹‚©‚ç“Ç‚İ‚Ş
	Load(enemyData);

	for (std::unique_ptr<Enemy>& enemy : enemys_)
	{
		enemy->Initialize();
		ColliderManager::GetInstance()->AddCollision(enemy.get());
	}
}

void EnemyManager::Update(Camera* camera, Player* player, GameTimer* gameTimer, BulletManager* bulletManager)
{
	enemys_.remove_if([](std::unique_ptr<Enemy>& enemy) { return enemy->GetIsDead(); });
	for (const std::unique_ptr<Enemy>& enemy : enemys_)
	{
		enemy->SetCamera(camera);
		enemy->SetPlayer(player);
		enemy->SetGameTimer(gameTimer);
		enemy->SetBulletManager(bulletManager);
		enemy->Update();
	}
}

void EnemyManager::Draw()
{
	for (const std::unique_ptr<Enemy>& enemy : enemys_)
	{
		enemy->Draw();
	}
}

void EnemyManager::Load(EnemyData& enemyData)
{
	std::swap(enemys_, enemyData.enemys);
}

void EnemyManager::ReLoad(EnemyData& enemyData)
{
	Reset();
	Initialize(enemyData);
}

void EnemyManager::Reset()
{
	enemys_.clear();
}

const std::list<std::unique_ptr<Enemy>>& EnemyManager::GetEnemyList()
{
	return enemys_;
}