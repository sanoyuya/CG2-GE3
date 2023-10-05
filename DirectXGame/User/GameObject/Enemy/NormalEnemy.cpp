#include "NormalEnemy.h"
#include"ColliderManager.h"
#include"EasingFunction.h"

NormalEnemy::~NormalEnemy()
{
	if (deathAnimationFlag_ == false)
	{
		ColliderManager::GetInstance()->SubCollision(this);
	}
	if (lockOnFlag_ == true)
	{
		ColliderManager::GetInstance()->SubLockOnEnemy(this);
	}
}

void NormalEnemy::Initialize()
{
	enemy_ = std::make_unique<Model>();
	enemyTex_ = enemy_->CreateObjModel("Resources/enemy");
	enemy_->SetModel(enemyTex_);
	enemyTrans_.Initialize();

	//死亡アニメーションパーティクル初期化
	emitter_ = std::make_unique<EnemyDeathParticleEmitter>();
	emitter_->Initialize();
	//スポーンアニメーションパーティクル初期化
	spawnEmitter_ = std::make_unique<EnemySpawnParticleEmitter>();
	spawnEmitter_->Initialize();

	lockOnAnimation_= std::make_unique<LockOnAnimation>();
	lockOnAnimation_->Initialize();

	hitEffect_ = std::make_unique<HitEffect>();
	hitEffect_->Initialize();
}

void NormalEnemy::Update()
{
	//出現していたら
	if (spawnFlag_ == true)
	{
		//敵のモデルの更新処理
		enemyTrans_.TransUpdate(camera_);
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

	collisionData_.center = enemyTrans_.translation;
}

void NormalEnemy::Draw()
{
	if (spawnFlag_ == false)
	{
		spawnEmitter_->Draw();
	}
	//死んでいないときのみ描画
	if (spawnFlag_ == true && deathAnimationFlag_ == false)
	{
		enemy_->DrawModel(&enemyTrans_);
		if (lockOnFlag_ == true)
		{
			lockOnAnimation_->Draw(camera_);
		}
	}
	else
	{
		//死亡演出の描画処理
		emitter_->Draw();
		hitEffect_->Draw(camera_);
	}
}

std::string NormalEnemy::GetName()
{
	return name_;
}

const Transform& NormalEnemy::GetTransform()
{
	return enemyTrans_;
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

void NormalEnemy::SetMoveEnemyProperty(const MoveEnemyProperty& moveEnemyProperty)
{
	moveEnemyProperty;
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

void NormalEnemy::LockOn()
{
	lockOnFlag_ = true;
	lockOnAnimation_->Create();
}

void NormalEnemy::CancelLockOn()
{
	lockOnFlag_ = false;
	lockOnAnimation_->Cancel();
}

void NormalEnemy::OnCollision()
{
	//爆発演出
	emitter_->Create(enemyTrans_.parentToTranslation);
	//Hit演出
	hitEffect_->Create(enemyTrans_.parentToTranslation);
	//爆発音
	AudioManager::GetInstance()->PlayWave(sound_, false);

	deathAnimationFlag_ = true;
}

const bool NormalEnemy::GetLockOnFlag()
{
	return lockOnFlag_;
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

		if (spawnAnimationTimer_ < maxSpawnAnimationTime_ / 2)
		{
			spawnEmitter_->Create(enemyTrans_.parentToTranslation);
		}
		spawnAnimationTimer_++;
	}

	spawnEmitter_->Update(camera_);

	if (spawnAnimationTimer_ > maxSpawnAnimationTime_)
	{
		spawnFlag_ = true;
	}
}

void NormalEnemy::DeathUpdate()
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
		hitEffect_->Update(camera_);
		deathAnimationTimer_++;
	}

	if (deathAnimationTimer_ > maxDeathAnimationTime_)
	{
		isDead_ = true;
	}
}