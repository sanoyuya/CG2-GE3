#include "NormalEnemy.h"
#include"ColliderManager.h"
#include"EasingFunction.h"
#include"PhysicsMath.h"
#include"GameHeader.h"

NormalEnemy::~NormalEnemy()
{
	ColliderManager::GetInstance()->SubCollision(this);
	if (lockOnFlag_ == true)
	{
		ColliderManager::GetInstance()->SubLockOnEnemy(this);
	}
}

void NormalEnemy::Initialize()
{
	enemy_ = std::make_unique<Model>();
	enemy_->SetModel(enemyTex0_);
	enemyTrans_.Initialize();
	enemyTrans_.TransUpdate(sCamera_);
	maxBulletTime = static_cast<float>(myMath::GetRand(GameHeader::sFps_ - delayBulletTime_, GameHeader::sFps_ + delayBulletTime_));

	//死亡アニメーションパーティクル初期化
	emitter_ = std::make_unique<EnemyDeathParticleEmitter>();
	emitter_->Initialize();
	//スポーンアニメーションパーティクル初期化
	spawnEmitter_ = std::make_unique<EnemySpawnParticleEmitter>();
	spawnEmitter_->Initialize();

	lockOnAnimation_ = std::make_unique<LockOnAnimation>();
	lockOnAnimation_->Initialize();

	hitEffect_ = std::make_unique<HitEffect>();
	hitEffect_->Initialize();
}

void NormalEnemy::Update()
{
	//死亡時間を過ぎたらスポーンフラグをfalseにして描画を消す
	if (sGameTimer_->GetFlameCount() > deathTime_ * GameHeader::sFps_)
	{
		spawnFlag_ = false;
	}

	//出現していたら
	if (spawnFlag_ == true)
	{
		actionTimer = static_cast<uint16_t>(sGameTimer_->GetFlameCount() - spawnTime_);
		//単振動
		enemyTrans_.translation.y = PhysicsMath::SimpleHarmonicMotion(actionTimer, amplitude_, GameHeader::sFps_ * 2) + iniPos_.y;

		//敵のモデルの更新処理
		enemyTrans_.TransUpdate(sCamera_);
		lockOnAnimation_->Update(enemyTrans_.parentToTranslation, sCamera_);
		if (attackProperty_.isAttack == true)
		{
			//弾の生成処理と更新処理
			BulletUpdate();
		}
		//死亡処理
		DeathUpdate();
	}
	else
	{
		if (sGameTimer_->GetFlameCount() <= deathTime_ * GameHeader::sFps_)
		{
			SpawnUpdate();
		}
	}

	collisionData_.center = enemyTrans_.translation;
}

void NormalEnemy::Draw()
{
	if (spawnTime_ * GameHeader::sFps_ <= sGameTimer_->GetFlameCount() && sGameTimer_->GetFlameCount() <= deathTime_ * GameHeader::sFps_)
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
				lockOnAnimation_->Draw(sCamera_);
			}
		}
		else
		{
			//死亡演出の描画処理
			emitter_->Draw();
			hitEffect_->Draw(sCamera_);
		}
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
	iniPos_ = position;
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

void NormalEnemy::SetAttackProperty(const AttackProperty property)
{
	attackProperty_ = property;
}

const bool NormalEnemy::GetIsDead()
{
	return isDead_;
}

const bool NormalEnemy::GetSpawnFlag()
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
		bulletTimer += sGameTimer_->GetTimeSpeed();
		if (bulletTimer > maxBulletTime)
		{
			if (distance_ >= length)
			{
				if (attackProperty_.type == "normal")
				{
					bulletManager_->CreateNormalBullet(enemyTrans_.translation, frontVec, BulletOwner::Enemy);
				}
				else
				{
					bulletManager_->Create3WayBullet(enemyTrans_.translation, frontVec, BulletOwner::Enemy);
				}
			}

			bulletTimer = 0.0f;
			maxBulletTime = static_cast<float>(myMath::GetRand(GameHeader::sFps_ - delayBulletTime_, GameHeader::sFps_ + delayBulletTime_));
		}
	}
}

void NormalEnemy::SpawnUpdate()
{
	if (spawnTime_ <= sGameTimer_->GetIntTime())
	{
		enemyTrans_.TransUpdate(sCamera_);

		if (spawnAnimationTimer_ < maxSpawnAnimationTime_ / 2)
		{
			spawnEmitter_->Create(enemyTrans_.parentToTranslation);
		}
		spawnAnimationTimer_++;
	}

	spawnEmitter_->Update(sCamera_);

	if (spawnAnimationTimer_ > maxSpawnAnimationTime_)
	{
		spawnFlag_ = true;
	}
}

void NormalEnemy::DeathUpdate()
{
	//死亡演出の更新処理
	if (deathAnimationFlag_ == true)
	{
		emitter_->Update(sCamera_);
		hitEffect_->Update(sCamera_);
		deathAnimationTimer_++;
	}

	if (deathAnimationTimer_ > maxDeathAnimationTime_)
	{
		if (lockOnFlag_ == false)
		{
			isDead_ = true;
		}
	}
}