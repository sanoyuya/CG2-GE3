#include "MoveEnemy.h"
#include"PhysicsMath.h"
#include"ColliderManager.h"
#include"EasingFunction.h"
#include"AudioManager.h"

MoveEnemy::~MoveEnemy()
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

void MoveEnemy::Initialize()
{
	enemy_ = std::make_unique<Model>();
	enemyTex_ = enemy_->CreateObjModel("Resources/enemy2");
	enemy_->SetModel(enemyTex_);
	enemyTrans_.Initialize();
	enemyTrans_.translation = moveEnemyProperty_.spawnPos;
	enemyTrans_.rotation = { myMath::ChangeRadians(moveEnemyProperty_.movePosRotation.x), myMath::ChangeRadians(moveEnemyProperty_.movePosRotation.y), myMath::ChangeRadians(moveEnemyProperty_.movePosRotation.z) - myMath::AX_PIF / 2 };
	collisionData_.center = enemyTrans_.translation;

	//死亡アニメーションパーティクル初期化
	emitter_ = std::make_unique<EnemyDeathParticleEmitter>();
	emitter_->Initialize();
	//スポーンアニメーションパーティクル初期化
	spawnEmitter_= std::make_unique<EnemySpawnParticleEmitter>();
	spawnEmitter_->Initialize();

	lockOnAnimation_ = std::make_unique<LockOnAnimation>();
	lockOnAnimation_->Initialize();

	hitEffect_ = std::make_unique<HitEffect>();
	hitEffect_->Initialize();
}

void MoveEnemy::Update()
{
	//出現していたら
	if (spawnFlag_ == true)
	{
		PhaseUpdate();
		//敵のモデルの更新処理
		enemyTrans_.TransUpdate(camera_);
		collisionData_.center = enemyTrans_.translation;
		lockOnAnimation_->Update(enemyTrans_.parentToTranslation, camera_);
		if (isAttack == true)
		{
			//弾の生成処理と更新処理
			BulletUpdate();
		}
		//死亡処理
		DeathUpdate();
	}
	else
	{
		SpawnUpdate();
	}
}

void MoveEnemy::PhaseUpdate()
{
	switch (phase)
	{
	case ActionPhase::MOVE:

		PhaseMove(moveEnemyProperty_.spawnPos, moveEnemyProperty_.movePos, moveEnemyProperty_.spawnPosRotation, moveEnemyProperty_.movePosRotation, moveEnemyProperty_.toMovePosTime * 60);

		actionTimer++;

		if (moveEnemyProperty_.toMovePosTime * 60 <= actionTimer)
		{
			actionTimer = 0;
			phase = ActionPhase::WAIT;
		}

		break;
	case ActionPhase::WAIT:

		if (moveEnemyProperty_.waitTime * 60 <= actionTimer)
		{
			actionTimer = 0;
			waitFinishPos = enemyTrans_.translation;
			waitFinishRot = enemyTrans_.rotation;
			phase = ActionPhase::ESCAPE;
		}

		addY = PhysicsMath::SimpleHarmonicMotion(actionTimer, 0.02f, 120.0f);
		enemyTrans_.translation.y = enemyTrans_.translation.y + addY;

		actionTimer++;

		break;
	case ActionPhase::ESCAPE:

		PhaseMove(waitFinishPos, moveEnemyProperty_.escapePos, waitFinishRot, moveEnemyProperty_.escapePosRotation, moveEnemyProperty_.toEscapePosTime * 60);

		actionTimer++;

		if (moveEnemyProperty_.toEscapePosTime * 60 <= actionTimer)
		{
			isDead_ = true;
		}

		break;
	}
}

void MoveEnemy::PhaseMove(const myMath::Vector3& startPosition, const myMath::Vector3& endPosition, const myMath::Vector3& startRotation, const myMath::Vector3& endRotation, const float maxTime)
{
	enemyTrans_.translation = { static_cast<float>(Easing::EaseInOutCubic(actionTimer, startPosition.x, endPosition.x, maxTime)),
	static_cast<float>(Easing::EaseInOutCubic(actionTimer, startPosition.y, endPosition.y, maxTime)),
	static_cast<float>(Easing::EaseInOutCubic(actionTimer, startPosition.z, endPosition.z, maxTime)) };

	enemyTrans_.rotation = { static_cast<float>(Easing::EaseInOutCubic(actionTimer, startRotation.x, endRotation.x, maxTime)),
	static_cast<float>(Easing::EaseInOutCubic(actionTimer, startRotation.y, endRotation.y, maxTime)),
	static_cast<float>(Easing::EaseInOutCubic(actionTimer, startRotation.z, endRotation.z, maxTime)) };
}

void MoveEnemy::Draw()
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

void MoveEnemy::SetIsAttack(const bool flag)
{
	isAttack = flag;
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
		hitEffect_->Update(camera_);
		deathAnimationTimer_++;
	}

	if (deathAnimationTimer_ > maxDeathAnimationTime_)
	{
		isDead_ = true;
	}
}