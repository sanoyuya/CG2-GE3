#include "NormalEnemy.h"
#include"ColliderManager.h"

NormalEnemy::~NormalEnemy()
{
	if (deathAnimationFlag_ == false)
	{
		ColliderManager::GetInstance()->SubCollision(this);
	}
}

void NormalEnemy::Initialize()
{
	enemy_ = std::make_unique<Model>();
	enemyTex_ = enemy_->CreateObjModel("Resources/enemy");
	enemy_->SetModel(enemyTex_);
	enemyTrans_.Initialize();
	enemyTrans_.scale = { 10.0f,10.0f,10.0f };

	// �p�[�e�B�N������
	emitter_ = std::make_unique<EnemyDeathParticleEmitter>();
	emitter_->Initialize();
}

void NormalEnemy::Update()
{
	//�o�����Ă�����
	if (spawnFlag_ == true)
	{
		//�G�̃��f���̍X�V����
		enemyTrans_.TransUpdate(camera_);
		//�e�̐��������ƍX�V����
		BulletUpdate();
		//���S����
		DeathUpdate();
	}
	else
	{
		SpawnUpdate();
	}

	collisionData_.center = enemyTrans_.translation;
}

void NormalEnemy::Draw()
{
	//����ł��Ȃ��Ƃ��̂ݕ`��
	if (spawnFlag_ == true && deathAnimationFlag_ == false)
	{
		enemy_->DrawModel(&enemyTrans_);
	}
	else
	{
		//���S���o�̕`�揈��
		emitter_->Draw();
	}
}

std::string NormalEnemy::GetName()
{
	return name_;
}

const CollisionData& NormalEnemy::GetCollisionData()
{
	return collisionData_;
}

void NormalEnemy::SetPosition(const myMath::Vector3& position)
{
	enemyTrans_.translation = position;
}

void NormalEnemy::SetRotation(const myMath::Vector3& rotation)
{
	enemyTrans_.rotation = rotation;
}

void NormalEnemy::SetColliderSize(const float size)
{
	collisionData_.radius = size;
}

void NormalEnemy::SetSpawnTimer(const float timer)
{
	spawnTime_ = timer;
}

void NormalEnemy::SetDeathTimer(const float timer)
{
	deathTime_ = timer;
}

const bool NormalEnemy::GetIsDead()
{
	return isDead_;
}

bool NormalEnemy::GetSpawnFlag()
{
	return spawnFlag_;
}

const bool NormalEnemy::GetDeathAnimationFlag()
{
	return deathAnimationFlag_;
}

void NormalEnemy::OnCollision()
{
	emitter_->Create(enemyTrans_.parentToTranslation);
	deathAnimationFlag_ = true;
}

bool NormalEnemy::GetLockOnFlag()
{
	return lockOnFlag;
}

const Transform& NormalEnemy::GetTrans()
{
	return enemyTrans_;
}

void NormalEnemy::BulletUpdate()
{
	myMath::Vector3 frontVec = player_->GetTransform().parentToTranslation - enemyTrans_.translation;
	frontVec = frontVec.normalization();

	if (deathAnimationFlag_ == false)
	{
		float length = sqrt((player_->GetTransform().parentToTranslation.x - enemyTrans_.parentToTranslation.x) * (player_->GetTransform().parentToTranslation.x - enemyTrans_.parentToTranslation.x)) +
			sqrt((player_->GetTransform().parentToTranslation.z - enemyTrans_.parentToTranslation.z) * (player_->GetTransform().parentToTranslation.z - enemyTrans_.parentToTranslation.z));
		bulletTimer++;
		if (bulletTimer > maxBulletTime)
		{
			if (75.0f >= length)
			{
				bulletManager_->CreateNormalBullet(enemyTrans_.translation, frontVec, BulletOwner::Enemy);
			}

			bulletTimer = 0.0f;
		}
	}
}

void NormalEnemy::SpawnUpdate()
{
	if (spawnTime_ <= gameTimer_->GetIntTime())
	{
		enemyTrans_.TransUpdate(camera_);
		if (spawnAnimationFlag_ == false)
		{
			emitter_->Create(enemyTrans_.parentToTranslation);
		}
		spawnAnimationFlag_ = true;
	}

	if (spawnAnimationFlag_ == true)
	{
		emitter_->Update(camera_);
		spawnAnimationTimer_++;
	}

	if (spawnAnimationTimer_ > maxSpawnAnimationTime_)
	{
		spawnFlag_ = true;
	}
}

void NormalEnemy::DeathUpdate()
{
	//���S���ԂɂȂ����玀��
	if (deathTime_ <= gameTimer_->GetIntTime())
	{
		isDead_ = true;
	}

	//���S���o�̍X�V����
	if (deathAnimationFlag_ == true)
	{
		emitter_->Update(camera_);
		deathAnimationTimer_++;
	}

	if (deathAnimationTimer_ > maxDeathAnimationTime_)
	{
		isDead_ = true;
	}
}