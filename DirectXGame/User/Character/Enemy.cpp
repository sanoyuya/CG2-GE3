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

	// パーティクル生成
	emitter_ = std::make_unique<EnemyDeathParticleEmitter>();
	emitter_->Initialize();
}

void Enemy::Update(Camera* camera, Player* player, GameTimer* gameTimer)
{
	//出現していたら
	if (spawnFlag_ == true)
	{
		//敵のモデルの更新処理
		enemyTrans_.TransUpdate(camera);
		//弾の生成処理と更新処理
		BulletUpdate(camera, player);
		//死亡処理
		DeathUpdate(camera, gameTimer);
	}
	else
	{
		SpawnUpdate(camera, gameTimer);
	}
}

void Enemy::Draw()
{
	//死んでいないときのみ描画
	if (spawnFlag_ == true && deathAnimationFlag_ == false)
	{
		enemy_->DrawModel(&enemyTrans_);
	}
	else
	{
		//死亡演出の描画処理
		emitter_->Draw();
	}

	//弾の描画処理
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
	//デバッグ用
	spawnTime_ = 5.0f;
}

void Enemy::SetDeathTimer(const float timer)
{
	deathTime_ = timer;
	//デバッグ用
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

bool Enemy::GetSpawnFlag()
{
	return spawnFlag_;
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

	//弾の更新処理
	Character::BulletUpdate(camera);
}

void Enemy::BulletDraw()
{
	for (const std::unique_ptr<Bullet>& bullet : bullets_)
	{
		bullet->Draw();//弾の描画
	}
}

void Enemy::SpawnUpdate(Camera* camera, GameTimer* gameTimer)
{
	if (spawnTime_ <= gameTimer->GetIntTime())
	{
		enemyTrans_.TransUpdate(camera);
		if (spawnAnimationFlag_ == false)
		{
			emitter_->Create(enemyTrans_.parentToTranslation);
		}
		spawnAnimationFlag_ = true;
	}

	if (spawnAnimationFlag_ == true)
	{
		emitter_->Update(camera);
		spawnAnimationTimer_++;
	}

	if (spawnAnimationTimer_ > maxSpawnAnimationTime_)
	{
		spawnFlag_ = true;
	}
}

void Enemy::DeathUpdate(Camera* camera, GameTimer* gameTimer)
{
	//死亡時間になったら死ぬ
	if (deathTime_ <= gameTimer->GetIntTime())
	{
		if (deathAnimationFlag_ == false)
		{
			emitter_->Create(enemyTrans_.parentToTranslation);
		}
		deathAnimationFlag_ = true;
	}

	//死亡演出の更新処理
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