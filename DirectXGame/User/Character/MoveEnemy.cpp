#include "MoveEnemy.h"
#include"PhysicsMath.h"
#include"ColliderManager.h"
#include"EasingFunction.h"

MoveEnemy::~MoveEnemy()
{
	if (deathAnimationFlag_ == false)
	{
		ColliderManager::GetInstance()->SubCollision(this);
	}
	if (lockOnFlag == true)
	{
		ColliderManager::GetInstance()->SubLockOnEnemy(this);
	}
}

void MoveEnemy::Initialize()
{
	enemy_ = std::make_unique<Model>();
	enemyTex_ = enemy_->CreateObjModel("Resources/enemy");
	enemy_->SetModel(enemyTex_);
	enemyTrans_.Initialize();
	enemyTrans_.scale = { 10.0f,10.0f,10.0f };

	// パーティクル生成
	emitter_ = std::make_unique<EnemyDeathParticleEmitter>();
	emitter_->Initialize();

	lockOnAnimation_ = std::make_unique<LockOnAnimation>();
	lockOnAnimation_->Initialize();
}

void MoveEnemy::Update()
{
	time_++;
	addY = PhysicsMath::SimpleHarmonicMotion(time_,0.5f,120.0f);
	enemyTrans_.translation.y = enemyTrans_.translation.y + addY;

	//出現していたら
	if (spawnFlag_ == true)
	{
		//敵のモデルの更新処理
		enemyTrans_.TransUpdate(camera_);
		collisionData_.center = enemyTrans_.translation;
		lockOnAnimation_->Update(enemyTrans_.parentToTranslation, camera_);
		//弾の生成処理と更新処理
		BulletUpdate();
		//死亡処理
		DeathUpdate();
	}
	else
	{
		SpawnUpdate();
	}
}

void MoveEnemy::Draw()
{
	//死んでいないときのみ描画
	if (spawnFlag_ == true && deathAnimationFlag_ == false)
	{
		enemy_->DrawModel(&enemyTrans_);
		if (lockOnFlag == true)
		{
			lockOnAnimation_->Draw(camera_);
		}
	}
	else
	{
		//死亡演出の描画処理
		emitter_->Draw();
	}
}

std::string MoveEnemy::GetName()
{
	return name_;
}

const CollisionData& MoveEnemy::GetCollisionData()
{
	return collisionData_;
}

void MoveEnemy::SetPosition(const myMath::Vector3& position)
{
	enemyTrans_.translation = position;
}

void MoveEnemy::SetRotation(const myMath::Vector3& rotation)
{
	enemyTrans_.rotation = rotation;
}

void MoveEnemy::SetColliderSize(const float size)
{
	collisionData_.radius = size;
}

void MoveEnemy::SetSpawnTimer(const float timer)
{
	spawnTime_ = timer;
}

void MoveEnemy::SetDeathTimer(const float timer)
{
	deathTime_ = timer;
}

const bool MoveEnemy::GetIsDead()
{
	return isDead_;
}

bool MoveEnemy::GetSpawnFlag()
{
	return spawnFlag_;
}

const bool MoveEnemy::GetDeathAnimationFlag()
{
	return deathAnimationFlag_;
}

void MoveEnemy::LockOn()
{
	lockOnFlag = true;
	lockOnAnimation_->Create();
}

void MoveEnemy::CancelLockOn()
{
	lockOnFlag = false;
	lockOnAnimation_->Cancel();
}

void MoveEnemy::OnCollision()
{
	emitter_->Create(enemyTrans_.parentToTranslation);
	deathAnimationFlag_ = true;
}

const bool MoveEnemy::GetLockOnFlag()
{
	return lockOnFlag;
}

const Transform& MoveEnemy::GetTrans()
{
	return enemyTrans_;
}

void MoveEnemy::BulletUpdate()
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

void MoveEnemy::SpawnUpdate()
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

void MoveEnemy::DeathUpdate()
{
	//死亡時間になったら死ぬ
	if (deathTime_ <= gameTimer_->GetIntTime())
	{
		isDead_ = true;
	}

	//死亡演出の更新処理
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