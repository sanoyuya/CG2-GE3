#include "Enemy.h"
#include<cmath>

uint32_t Enemy::enemyTex;

const void Enemy::LoadTexture(uint32_t& texture)
{
	enemyTex = texture;
}

void Enemy::Initialize(const myMath::Vector3 position)
{
	enemy = std::make_unique<Sprite>();
	enemy->Sprite3DInitialize(enemyTex);
	enemyTrans.Initialize();
	enemyTrans.translation = position;
	enemyTrans.rotation.x = myMath::AX_PI / 2;
	enemyTrans.scale = { 1.0f / 24.0f,1.0f / 24.0f,1.0f };
	radius = 64.0f / 24.0f;
}

void Enemy::Update(Camera* camera, Player* player)
{
	Move(player);
	//死ぬ処理(適当)
	if (!player->GetJumpFlag())
	{
		if (((player->GetRadius() + radius) * (player->GetRadius() + radius)) >= ((enemyTrans.translation.x - player->GetTransform().translation.x) * (enemyTrans.translation.x - player->GetTransform().translation.x)) + ((enemyTrans.translation.z - player->GetTransform().translation.z) * (enemyTrans.translation.z - player->GetTransform().translation.z)))
		{
			if (!player->GetAttackFlag())
			{
				player->SetHp(player->GetHp() - 1);//プレイヤーダメージ処理
			}
			else
			{
				//スコア増加処理
			}
			isDead = true;//死ぬ処理
		}
	}
	enemyTrans.TransUpdate(camera);
}

void Enemy::Draw(Camera* camera)
{
	enemy->DrawSprite3D(camera, enemyTrans);
}

bool Enemy::GetIsDead()
{
	return isDead;
}

void Enemy::Move(Player* player)
{
	const float speed = 0.02f;

	//プレイヤーに向かう処理
	enemyVec.x = player->GetTransform().translation.x - enemyTrans.translation.x;
	enemyVec.z = player->GetTransform().translation.z - enemyTrans.translation.z;
	normEnemyVec = enemyVec.normalization();
	angle = -(atan2(enemyVec.z, enemyVec.x) + myMath::AX_PI / 2);
	enemyTrans.translation.x += normEnemyVec.x * speed;
	enemyTrans.translation.z += normEnemyVec.z * speed;
	enemyTrans.rotation.y = angle;//敵の進行方向に向きを合わせる
}