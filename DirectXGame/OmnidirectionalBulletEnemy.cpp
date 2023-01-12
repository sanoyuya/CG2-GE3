#include "OmnidirectionalBulletEnemy.h"
#include"Score.h"
#include"PhysicsMath.h"

void OmnidirectionalBulletEnemy::Initialize(const myMath::Vector3 position)
{
	enemy = std::make_unique<Sprite>();
	enemyTex = enemy->LoadTexture("Resources/enemy2.png");
	enemy->Sprite3DInitialize(enemyTex);
	exclamation = std::make_unique<Sprite>();
	exclamationTex = exclamation->LoadTexture("Resources/exclamation.png");
	exclamation->Sprite3DInitialize(exclamationTex);
	enemyTrans.Initialize();
	enemyTrans.translation = position;
	enemyTrans.rotation.x = myMath::AX_PI / 2;
	enemyTrans.scale = { 1.0f / 24.0f,1.0f / 24.0f,1.0f };
	radius = 64.0f / 24.0f;

	animationFlag = true;

	alpha = 1.0f;
}

void OmnidirectionalBulletEnemy::Update(Camera* camera, Player* player)
{
	for (int i = 0; i < 8; i++)
	{
		enemyBullets[i].remove_if([](std::unique_ptr<EnemyBullet>& enemyBullet) { return enemyBullet->GetIsDead(); });
	}

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
		if (deathFlag == false && deleteFlag == false)
		{
			Attack(player, camera);
			//���ʏ���(�K��)
			if (!player->GetJumpFlag())
			{
				if (((player->GetRadius() + radius) * (player->GetRadius() + radius)) >= ((enemyTrans.translation.x - player->GetTransform().translation.x) * (enemyTrans.translation.x - player->GetTransform().translation.x)) + ((enemyTrans.translation.z - player->GetTransform().translation.z) * (enemyTrans.translation.z - player->GetTransform().translation.z)))
				{
					if (!player->GetAttackFlag())
					{
						if (!player->GetDamageFlag())
						{
							player->SetHp(player->GetHp() - 1);//�v���C���[�_���[�W����
							player->SetDamageFlag(true);
							deleteFlag = true;
						}
					}
					else
					{
						//�X�R�A��������
						Score::GetInstance()->EnemyKillAdd();
						deathFlag = true;//���ʉ��o�J�n
					}
				}
			}
			enemyTrans.TransUpdate(camera);
		}

		//�e�̍X�V����
		for (int i = 0; i < 8; i++)
		{
			for (const std::unique_ptr<EnemyBullet>& enemyBullet : enemyBullets[i])
			{
				enemyBullet->Update(player, camera, { PhysicsMath::CircularMotion({0.0f,0.0f},1.0f,i * myMath::AX_PIF / 4).x,0.0f,PhysicsMath::CircularMotion({0.0f,0.0f},1.0f,i * myMath::AX_PIF / 4).y });
			}
		}
	}
}

void OmnidirectionalBulletEnemy::Draw(Camera* camera, myMath::Vector4 color)
{
	for (int i = 0; i < 8; i++)
	{
		for (const std::unique_ptr<EnemyBullet>& enemyBullet : enemyBullets[i])
		{
			enemyBullet->Draw(camera, color);//�v���C���[�Ɍ������Ă���G
		}
	}

	if (deathFlag == false && deleteFlag == false)
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

	if (deathFlag == true)
	{
		DeathAnimation(camera, color);
	}

	if (deathFlag == true || deleteFlag == true)
	{
		deathTimer++;
		if (deathTimer > 300)
		{
			deathCubes.clear();
			isDead = true;//���ʏ���
		}
	}
}

bool OmnidirectionalBulletEnemy::GetIsDead()
{
	return isDead;
}

void OmnidirectionalBulletEnemy::Attack(Player* player, Camera* camera)
{
	//�e�̐�������
	coolTime++;
	if (coolTime > 120)
	{
		for (int i = 0; i < 8; i++)
		{
			//�e�𐶐����A������
			std::unique_ptr<EnemyBullet> newEnemyBullet = std::make_unique<EnemyBullet>();
			newEnemyBullet->Initialize(enemyTrans.translation);
			//�e��o�^����
			enemyBullets[i].push_back(std::move(newEnemyBullet));

			coolTime = 0.0f;
		}
	}
}

void OmnidirectionalBulletEnemy::DeathAnimation(Camera* camera, myMath::Vector4 color)
{
	deathCubes.remove_if([](std::unique_ptr<DeathCube>& deathCube) { return deathCube->GetIsDead(); });

	if (generationFlag == false)
	{
		for (int i = 0; i < 20; i++)
		{
			//�w�i�T�C�R���𐶐����A������
			std::unique_ptr<DeathCube> newdeathCube = std::make_unique<DeathCube>();
			newdeathCube->Initialize(enemyTrans.translation);
			//�w�i�T�C�R����o�^����
			deathCubes.push_back(std::move(newdeathCube));
		}
		generationFlag = true;
	}

	//�w�i�T�C�R���̍X�V����
	for (const std::unique_ptr<DeathCube>& deathCube : deathCubes)
	{
		deathCube->Update(camera, { 1.0f ,1.0f ,1.0f });
	}

	alpha -= 1.0f / 50;

	for (const std::unique_ptr<DeathCube>& deathCube : deathCubes)
	{
		deathCube->Draw({ 1.0f - color.x * 3,1.0f - color.y * 3,1.0f - color.z * 3 ,alpha });//�w�i�̃T�C�R��
	}
}
