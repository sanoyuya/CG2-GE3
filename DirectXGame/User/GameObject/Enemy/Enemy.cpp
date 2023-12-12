#include "Enemy.h"
#include"AudioManager.h"
uint32_t Enemy::sound_;
uint32_t Enemy::enemyTex0_;
uint32_t Enemy::enemyTex1_;

void Enemy::LoadAsset()
{
	enemyTex0_ = Model::CreateObjModel("Resources/enemy");
	enemyTex1_ = Model::CreateObjModel("Resources/enemy2");
	sound_ = AudioManager::GetInstance()->LoadAudio("Resources/Sound/enemyDeath.mp3", 0.1f);
}

void Enemy::SetPlayer(Player* player)
{
	player_ = player;
}

void Enemy::SetBulletManager(BulletManager* bulletManager)
{
	bulletManager_ = bulletManager;
}