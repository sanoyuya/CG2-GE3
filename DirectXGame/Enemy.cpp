#include "Enemy.h"
#include<cmath>

void Enemy::Initialize(const myMath::Vector3 position)
{
	enemy = std::make_unique<Sprite>();
	enemyTex = enemy->LoadTexture("Resources/enemy.png");
	enemy->Sprite3DInitialize(enemyTex);
	exclamation = std::make_unique<Sprite>();
	exclamationTex = exclamation->LoadTexture("Resources/exclamation.png");
	exclamation->Sprite3DInitialize(exclamationTex);
	enemyTrans.Initialize();
	enemyTrans.translation = position;
	enemyTrans.rotation.x = myMath::AX_PI / 2;
	enemyTrans.rotation.y = myMath::AX_PI;
	enemyTrans.scale = { 1.0f / 24.0f,1.0f / 24.0f,1.0f };
	radius = 64.0f / 24.0f;

	animationFlag = true;

	alpha = 1.0f;
}

void Enemy::Update(Camera* camera, Player* player)
{
	if (animationFlag == true)
	{
		animationCoolTime++;
		if (animationCoolTime > 100)
		{
			animationFlag = false;
		}
	}
	else
	{
		if (deathFlag == false)
		{
			Move(player);
			//死ぬ処理(適当)
			if (!player->GetJumpFlag())
			{
				if (((player->GetRadius() + radius) * (player->GetRadius() + radius)) >= ((enemyTrans.translation.x - player->GetTransform().translation.x) * (enemyTrans.translation.x - player->GetTransform().translation.x)) + ((enemyTrans.translation.z - player->GetTransform().translation.z) * (enemyTrans.translation.z - player->GetTransform().translation.z)))
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
					else
					{
						//スコア増加処理
						deathFlag = true;//死ぬ演出開始
					}
				}
			}
			enemyTrans.TransUpdate(camera);
		}
	}
}

void Enemy::Draw(Camera* camera, myMath::Vector4 color)
{
	if (deathFlag == false)
	{
		if (animationFlag == true)
		{
			exclamation->DrawSprite3D(camera, enemyTrans, BillboardFlag::NonBillboard, { 1.0f - color.x * 3,1.0f - color.y * 3,1.0f - color.z * 3,color.w });
		}
		else
		{
			enemy->DrawSprite3D(camera, enemyTrans, BillboardFlag::NonBillboard, { 1.0f - color.x * 3,1.0f - color.y * 3,1.0f - color.z * 3,color.w });
		}
	}
	else
	{
		DeathAnimation(camera, color);
	}
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

void Enemy::DeathAnimation(Camera* camera, myMath::Vector4 color)
{
	deathTimer++;
	if (deathTimer > 180)
	{
		deathCubes.clear();
		isDead = true;//死ぬ処理
	}

	deathCubes.remove_if([](std::unique_ptr<DeathCube>& deathCube) { return deathCube->GetIsDead(); });

	if (generationFlag == false)
	{
		for (int i = 0; i < 10; i++)
		{
			//背景サイコロを生成し、初期化
			std::unique_ptr<DeathCube> newdeathCube = std::make_unique<DeathCube>();
			newdeathCube->Initialize(enemyTrans.translation);
			//背景サイコロを登録する
			deathCubes.push_back(std::move(newdeathCube));
		}
		generationFlag = true;
	}

	//背景サイコロの更新処理
	for (const std::unique_ptr<DeathCube>& deathCube : deathCubes)
	{
		deathCube->Update(camera, { 1.0f ,1.0f ,1.0f });
	}

	alpha -= 1.0f / 50;

	for (const std::unique_ptr<DeathCube>& deathCube : deathCubes)
	{
		deathCube->Draw({ 1.0f - color.x * 3,1.0f - color.y * 3,1.0f - color.z * 3 ,alpha });//背景のサイコロ
	}
}