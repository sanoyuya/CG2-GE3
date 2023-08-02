#include "Enemy.h"
#include"ColliderManager.h"

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

	// �p�[�e�B�N������
	emitter_ = std::make_unique<EnemyDeathParticleEmitter>();
	emitter_->Initialize();
}

void Enemy::Update(Camera* camera, Player* player, GameTimer* gameTimer)
{
	//�G�̃��f���̍X�V����
	enemyTrans_.TransUpdate(camera);
	//�e�̐��������ƍX�V����
	BulletUpdate(camera, player);
	//���S����
	DeathUpdate(camera, gameTimer);
}

void Enemy::Draw()
{
	//����ł��Ȃ��Ƃ��̂ݕ`��
	if (deathAnimationFlag_ == false)
	{
		enemy_->DrawModel(&enemyTrans_);
	}
	else
	{
		//���S���o�̕`�揈��
		emitter_->Draw();
	}

	//�e�̕`�揈��
	BulletDraw();
}

void Enemy::SetPosition(const myMath::Vector3& position)
{
	enemyTrans_.translation = position;
}

void Enemy::SetRotation(const myMath::Vector3& rotation)
{
	enemyTrans_.rotation = rotation;
}

void Enemy::SetColliderSize(const float size)
{
	colliderSize_ = size;
}

void Enemy::SetSpawnTimer(const float timer)
{
	spawnTime_ = timer;
}

void Enemy::SetDeathTimer(const float timer)
{
	deathTime_ = timer;
	//�f�o�b�O�p
	deathTime_ = 10.0f;
}

const Transform& Enemy::GetTrans()
{
	return enemyTrans_;
}

const float& Enemy::GetColliderSize()
{
	return colliderSize_;
}

bool Enemy::GetIsDead()
{
	return isDead_;
}

bool Enemy::GetDeathAnimationFlag()
{
	return deathAnimationFlag_;
}

void Enemy::OnCollision()
{
	deathAnimationFlag_ = true;
	emitter_->Create(enemyTrans_.parentToTranslation);
}

void Enemy::BulletUpdate(Camera* camera, Player* player)
{
	myMath::Vector3 frontVec = player->GetTransform().parentToTranslation - enemyTrans_.translation;
	frontVec = frontVec.normalization();

	if (deathAnimationFlag_ == false)
	{
		float length = sqrt((player->GetTransform().parentToTranslation.x - enemyTrans_.parentToTranslation.x) * (player->GetTransform().parentToTranslation.x - enemyTrans_.parentToTranslation.x)) +
			sqrt((player->GetTransform().parentToTranslation.z - enemyTrans_.parentToTranslation.z) * (player->GetTransform().parentToTranslation.z - enemyTrans_.parentToTranslation.z));
		bulletTimer++;
		if (bulletTimer > maxBulletTime)
		{
			if (75.0f >= length)
			{
				CreateBullet(enemyTrans_.translation, frontVec, BulletOwner::Enemy);
			}

			bulletTimer = 0.0f;
		}
	}

	//�e�̍X�V����
	Character::BulletUpdate(camera);
}

void Enemy::BulletDraw()
{
	for (const std::unique_ptr<Bullet>& bullet : bullets_)
	{
		bullet->Draw();//�e�̕`��
	}
}

void Enemy::DeathUpdate(Camera* camera, GameTimer* gameTimer)
{
	if (deathTime_ <= gameTimer->GetIntTime())
	{
		deathAnimationFlag_ = true;
	}

	//���S���o�̍X�V����
	if (deathAnimationFlag_ == true)
	{
		emitter_->Update(camera);
		deathAnimationTimer_++;
	}

	if (deathAnimationTimer_ > maxDeathAnimationTime_)
	{
		isDead_ = true;
	}
}