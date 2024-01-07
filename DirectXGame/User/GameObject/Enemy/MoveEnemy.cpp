#include "MoveEnemy.h"
#include"PhysicsMath.h"
#include"ColliderManager.h"
#include"EasingFunction.h"
#include"AudioManager.h"
#include"GameHeader.h"

MoveEnemy::~MoveEnemy()
{
	ColliderManager::GetInstance()->SubCollision(this);
	if (lockOnFlag_ == true)
	{
		ColliderManager::GetInstance()->SubLockOnEnemy(this);
	}
}

void MoveEnemy::Initialize()
{
	enemy_ = std::make_unique<Model>();
	enemy_->SetModel(enemyTex1_);
	enemyTrans_.Initialize();
	enemyTrans_.translation = moveEnemyProperty_.spawnPos;
	enemyTrans_.rotation = moveEnemyProperty_.movePosRotation;
	collisionData_.center = enemyTrans_.translation;
	maxBulletTime_ = static_cast<float>(myMath::GetRand(GameHeader::sFps_ - delayBulletTime_, GameHeader::sFps_ + delayBulletTime_));

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

void MoveEnemy::Update()
{
	if (spawnTime_ * GameHeader::sFps_ <= sGameTimer_->GetFlameCount() && sGameTimer_->GetFlameCount() <= deathTime_ * GameHeader::sFps_)
	{
		//出現していたら
		if (spawnFlag_ == true)
		{
			PhaseUpdate();
			//敵のモデルの更新処理
			enemyTrans_.TransUpdate(sCamera_);
			collisionData_.center = enemyTrans_.translation;
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
	}
	else
	{
		spawnFlag_ = false;
	}
}

void MoveEnemy::PhaseUpdate()
{
	if (spawnTime_ * GameHeader::sFps_ <= sGameTimer_->GetFlameCount() && sGameTimer_->GetFlameCount() <= deathTime_ * GameHeader::sFps_)
	{
		if (spawnTime_ * GameHeader::sFps_ <= sGameTimer_->GetFlameCount() && sGameTimer_->GetFlameCount() <= (spawnTime_ + moveEnemyProperty_.toMovePosTime) * GameHeader::sFps_)
		{
			phase = ActionPhase::MOVE;
		}
		else if ((spawnTime_ + moveEnemyProperty_.toMovePosTime) * GameHeader::sFps_ <= sGameTimer_->GetFlameCount() && sGameTimer_->GetFlameCount() <= (spawnTime_ + moveEnemyProperty_.toMovePosTime + moveEnemyProperty_.waitTime) * GameHeader::sFps_ + 1)
		{
			phase = ActionPhase::WAIT;
		}
		else
		{
			phase = ActionPhase::ESCAPE;
		}

		switch (phase)
		{
		case ActionPhase::MOVE:

			actionTimer = static_cast<uint16_t>(sGameTimer_->GetFlameCount() - spawnTime_ * GameHeader::sFps_ - maxSpawnAnimationTime_);

			PhaseMove(moveEnemyProperty_.spawnPos, moveEnemyProperty_.movePos, moveEnemyProperty_.spawnPosRotation, moveEnemyProperty_.movePosRotation, moveEnemyProperty_.toMovePosTime * GameHeader::sFps_);

			if (moveEnemyProperty_.toMovePosTime * GameHeader::sFps_ <= actionTimer)
			{
				actionTimer = static_cast<uint16_t>(sGameTimer_->GetFlameCount() - spawnTime_ * GameHeader::sFps_ - moveEnemyProperty_.toMovePosTime * GameHeader::sFps_- maxSpawnAnimationTime_);
			}

			break;
		case ActionPhase::WAIT:

			actionTimer = static_cast<uint16_t>(sGameTimer_->GetFlameCount() - spawnTime_ * GameHeader::sFps_ - moveEnemyProperty_.toMovePosTime * GameHeader::sFps_);

			enemyTrans_.translation.y = PhysicsMath::SimpleHarmonicMotion(actionTimer, amplitude_, GameHeader::sFps_ * 2) + moveEnemyProperty_.movePos.y;

			if (moveEnemyProperty_.waitTime * GameHeader::sFps_ <= actionTimer)
			{
				actionTimer = static_cast<uint16_t>(sGameTimer_->GetFlameCount() - spawnTime_ * GameHeader::sFps_ - moveEnemyProperty_.toMovePosTime * GameHeader::sFps_ - moveEnemyProperty_.waitTime * GameHeader::sFps_);
				waitFinishPos = enemyTrans_.translation;
				waitFinishRot = enemyTrans_.rotation;
			}

			break;
		case ActionPhase::ESCAPE:

			actionTimer = static_cast<uint16_t>(sGameTimer_->GetFlameCount() - spawnTime_ * GameHeader::sFps_ - moveEnemyProperty_.toMovePosTime * GameHeader::sFps_ - moveEnemyProperty_.waitTime * GameHeader::sFps_);

			PhaseMove(waitFinishPos, moveEnemyProperty_.escapePos, waitFinishRot, moveEnemyProperty_.escapePosRotation, moveEnemyProperty_.toEscapePosTime * GameHeader::sFps_);

			break;
		}
	}
}

void MoveEnemy::PhaseMove(const myMath::Vector3& startPosition, const myMath::Vector3& endPosition, const myMath::Vector3& startRotation, const myMath::Vector3& endRotation, const float maxTime)
{
	enemyTrans_.translation = { static_cast<float>(Easing::EaseInOutQuad(actionTimer, startPosition.x, endPosition.x, maxTime)),
	static_cast<float>(Easing::EaseInOutQuad(actionTimer, startPosition.y, endPosition.y, maxTime)),
	static_cast<float>(Easing::EaseInOutQuad(actionTimer, startPosition.z, endPosition.z, maxTime)) };

	enemyTrans_.rotation = { static_cast<float>(Easing::EaseOutCubic(actionTimer, startRotation.x, endRotation.x, maxTime)),
	static_cast<float>(Easing::EaseOutCubic(actionTimer, startRotation.y, endRotation.y, maxTime)),
	static_cast<float>(Easing::EaseOutCubic(actionTimer, startRotation.z, endRotation.z, maxTime)) };
}

void MoveEnemy::Draw()
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

std::string MoveEnemy::GetName()
{
	return name_;
}

const Transform& MoveEnemy::GetTransform()
{
	return enemyTrans_;
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

void MoveEnemy::SetMoveEnemyProperty(const MoveEnemyProperty& moveEnemyProperty)
{
	moveEnemyProperty_ = moveEnemyProperty;
	moveEnemyProperty_.spawnPosRotation = { myMath::ChangeRadians(moveEnemyProperty_.spawnPosRotation.x), myMath::ChangeRadians(moveEnemyProperty_.spawnPosRotation.y) - myMath::AX_PIF / 2, myMath::ChangeRadians(moveEnemyProperty_.spawnPosRotation.z) - myMath::AX_PIF / 2 };
	moveEnemyProperty_.movePosRotation = { myMath::ChangeRadians(moveEnemyProperty_.movePosRotation.x), myMath::ChangeRadians(moveEnemyProperty_.movePosRotation.y) - myMath::AX_PIF / 2, myMath::ChangeRadians(moveEnemyProperty_.movePosRotation.z) - myMath::AX_PIF / 2 };
	moveEnemyProperty_.escapePosRotation = { myMath::ChangeRadians(moveEnemyProperty_.escapePosRotation.x), myMath::ChangeRadians(moveEnemyProperty_.escapePosRotation.y) - myMath::AX_PIF / 2, myMath::ChangeRadians(moveEnemyProperty_.escapePosRotation.z) - myMath::AX_PIF / 2 };
}

void MoveEnemy::SetAttackProperty(const AttackProperty property)
{
	attackProperty_ = property;
}

const bool MoveEnemy::GetIsDead()
{
	return isDead_;
}

const bool MoveEnemy::GetSpawnFlag()
{
	return spawnFlag_;
}

const bool MoveEnemy::GetDeathAnimationFlag()
{
	return deathAnimationFlag_;
}

void MoveEnemy::LockOn()
{
	lockOnFlag_ = true;
	lockOnAnimation_->Create();
}

void MoveEnemy::CancelLockOn()
{
	lockOnFlag_ = false;
	lockOnAnimation_->Cancel();
}

void MoveEnemy::OnCollision()
{
	//爆発演出
	emitter_->Create(enemyTrans_.parentToTranslation);
	//Hit演出
	hitEffect_->Create(enemyTrans_.parentToTranslation);
	//爆発音
	AudioManager::GetInstance()->PlayWave(sound_, false);

	deathAnimationFlag_ = true;
}

const bool MoveEnemy::GetLockOnFlag()
{
	return lockOnFlag_;
}

const Transform& MoveEnemy::GetTrans()
{
	return enemyTrans_;
}

void MoveEnemy::BulletUpdate()
{
	myMath::Vector3 frontVec = player_->GetPredictionPoint() + player_->GetTransform().translation - enemyTrans_.translation;
	frontVec = frontVec.normalization();

	if (deathAnimationFlag_ == false)
	{
		float length = sqrt((player_->GetTransform().parentToTranslation.x - enemyTrans_.parentToTranslation.x) * (player_->GetTransform().parentToTranslation.x - enemyTrans_.parentToTranslation.x)) +
			sqrt((player_->GetTransform().parentToTranslation.z - enemyTrans_.parentToTranslation.z) * (player_->GetTransform().parentToTranslation.z - enemyTrans_.parentToTranslation.z));
		bulletTimer_ += sGameTimer_->GetTimeSpeed();
		if (bulletTimer_ > maxBulletTime_)
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

			bulletTimer_ = 0.0f;
			maxBulletTime_ = static_cast<float>(myMath::GetRand(GameHeader::sFps_ - delayBulletTime_, GameHeader::sFps_ + delayBulletTime_));
		}
	}
}

void MoveEnemy::SpawnUpdate()
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

	if (spawnAnimationTimer_ >= maxSpawnAnimationTime_)
	{
		spawnFlag_ = true;
	}
}

void MoveEnemy::DeathUpdate()
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