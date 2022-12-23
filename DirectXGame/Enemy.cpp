#include "Enemy.h"

uint32_t Enemy::enemyTex;

const void Enemy::LoadTexture(uint32_t& texture)
{
	enemyTex = texture;
}

void Enemy::Initialize(const myMath::Vector3 position)
{
	enemy = std::make_unique<DrawOversight>();
	enemy->SetModel(enemyTex);
	enemyTrans.Initialize();
	enemyTrans.translation = position;
}

void Enemy::Update(Camera* camera)
{
	Move();
	enemyTrans.TransUpdate(camera);
}

void Enemy::Draw()
{
	enemy->DrawModel(&enemyTrans,{0.25f,1.0f,0.25f,1.0f});
}

bool Enemy::GetIsDead()
{
	return isDead;
}

void Enemy::Move()
{
	enemyTrans.translation.z -= 0.5f;
}

void Enemy::Attack()
{
}