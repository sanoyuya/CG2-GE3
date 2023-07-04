#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	enemy_ = std::make_unique<Model>();
	enemyTex_ = enemy_->CreateObjModel("Resources/F-35E");
	enemy_->SetModel(enemyTex_);
	enemyTrans_.Initialize();
}

void Enemy::Update(Camera* camera)
{
	enemyTrans_.TransUpdate(camera);
}

void Enemy::Draw()
{
	enemy_->DrawModel(&enemyTrans_);
}

void Enemy::SetPosition(const myMath::Vector3& position)
{
	enemyTrans_.translation = position;
}

bool Enemy::GetIsDead()
{
	return isDead_;
}