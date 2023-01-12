#include "EnemyBullet.h"

void EnemyBullet::Initialize(const myMath::Vector3 position)
{
	enemyBullet = std::make_unique<Sprite>();
	enemyBulletTex = enemyBullet->LoadTexture("Resources/enemyBullet.png");
	enemyBullet->Sprite3DInitialize(enemyBulletTex);

	enemyBulletTrans.Initialize();
	enemyBulletTrans.translation = position;
	enemyBulletTrans.rotation.x = myMath::AX_PI / 2;
	enemyBulletTrans.scale = { 1.0f / 64.0f,1.0f / 64.0f,1.0f };
	radius = 64.0f / 64.0f;
}

void EnemyBullet::Update(Player* player, Camera* camera, const myMath::Vector3 normVec)
{
	Move(normVec);

	//死ぬ処理(適当)
	if (!player->GetJumpFlag())
	{
		if (((player->GetRadius() + radius) * (player->GetRadius() + radius)) >= ((enemyBulletTrans.translation.x - player->GetTransform().translation.x) * (enemyBulletTrans.translation.x - player->GetTransform().translation.x)) + ((enemyBulletTrans.translation.z - player->GetTransform().translation.z) * (enemyBulletTrans.translation.z - player->GetTransform().translation.z)))
		{
			if (!player->GetAttackFlag())
			{
				if (!player->GetDamageFlag())
				{
					player->SetHp(player->GetHp() - 1);//プレイヤーダメージ処理
					player->SetDamageFlag(true);
					isDead = true;
				}
			}
		}
	}

	if (enemyBulletTrans.translation.x <= -30.0f || enemyBulletTrans.translation.x >= 30.0f || enemyBulletTrans.translation.z <= -30.0f || enemyBulletTrans.translation.z >= 30.0f)
	{
		isDead = true;
	}
	enemyBulletTrans.TransUpdate(camera);
}

void EnemyBullet::Draw(Camera* camera, myMath::Vector4 color)
{
	enemyBullet->DrawSprite3D(camera, enemyBulletTrans, BillboardFlag::NonBillboard, { 1.0f - color.x * 3,1.0f - color.y * 3,1.0f - color.z * 3,color.w });
}

void EnemyBullet::Move(const myMath::Vector3 normVec)
{
	const float speed = 0.15f;

	enemyBulletTrans.translation.x += normVec.x * speed;
	enemyBulletTrans.translation.z += normVec.z * speed;
}

const bool& EnemyBullet::GetIsDead()
{
	return isDead;
}
