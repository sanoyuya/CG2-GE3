#include "Enemy.h"
#include"AudioManager.h"
uint32_t Enemy::sound_;

void Enemy::StaticInitialize()
{
	sound_ = AudioManager::GetInstance()->LoadAudio("Resources/Sound/enemyDeath.mp3", 0.1f);
}

void Enemy::SetCamera(Camera* camera)
{
	camera_ = camera;
}

void Enemy::SetPlayer(Player* player)
{
	player_ = player;
}

void Enemy::SetGameTimer(GameTimer* gameTimer)
{
	gameTimer_ = gameTimer;
}

void Enemy::SetBulletManager(BulletManager* bulletManager)
{
	bulletManager_ = bulletManager;
}