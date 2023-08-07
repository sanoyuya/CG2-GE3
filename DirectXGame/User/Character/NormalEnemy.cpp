#include "NormalEnemy.h"
#include"ColliderManager.h"

void NormalEnemy::Initialize()
{
	enemy_ = std::make_unique<Model>();
	enemyTex_ = enemy_->CreateObjModel("Resources/enemy");
	enemy_->SetModel(enemyTex_);
	enemyTrans_.Initialize();
	enemyTrans_.rotation.y = myMath::AX_PIF / 2;
	enemyTrans_.scale = { 15.0f,15.0f,15.0f };

	// ƒp[ƒeƒBƒNƒ‹¶¬
	emitter_ = std::make_unique<EnemyDeathParticleEmitter>();
	emitter_->Initialize();
}

void NormalEnemy::Update()
{
	//oŒ»‚µ‚Ä‚¢‚½‚ç
	if (spawnFlag_ == true)
	{
		//“G‚Ìƒ‚ƒfƒ‹‚ÌXVˆ—
		enemyTrans_.TransUpdate(camera_);
		//’e‚Ì¶¬ˆ—‚ÆXVˆ—
		BulletUpdate(camera_, player_);
		//€–Sˆ—
		DeathUpdate(camera_, gameTimer_);
	}
	else
	{
		SpawnUpdate(camera_, gameTimer_);
	}
}

void NormalEnemy::Draw()
{
	//€‚ñ‚Å‚¢‚È‚¢‚Æ‚«‚Ì‚İ•`‰æ
	if (spawnFlag_ == true && deathAnimationFlag_ == false)
	{
		enemy_->DrawModel(&enemyTrans_);
	}
	else
	{
		//€–S‰‰o‚Ì•`‰æˆ—
		emitter_->Draw();
	}

	//’e‚Ì•`‰æˆ—
	BulletDraw();
}

std::string NormalEnemy::GetName()
{
	return name_;
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
	colliderSize_ = size;
}

void NormalEnemy::SetSpawnTimer(const float timer)
{
	spawnTime_ = timer;
}

void NormalEnemy::SetDeathTimer(const float timer)
{
	deathTime_ = timer;
}

const Transform& NormalEnemy::GetTrans()
{
	return enemyTrans_;
}

const float& NormalEnemy::GetColliderSize()
{
	return colliderSize_;
}

bool NormalEnemy::GetIsDead()
{
	return isDead_;
}

bool NormalEnemy::GetSpawnFlag()
{
	return spawnFlag_;
}

bool NormalEnemy::GetDeathAnimationFlag()
{
	return deathAnimationFlag_;
}

void NormalEnemy::OnCollision()
{
	deathAnimationFlag_ = true;
	emitter_->Create(enemyTrans_.parentToTranslation);
}

void NormalEnemy::BulletUpdate(Camera* camera, Player* player)
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

	//’e‚ÌXVˆ—
	GameObject::BulletUpdate(camera);
}

void NormalEnemy::BulletDraw()
{
	for (const std::unique_ptr<Bullet>& bullet : bullets_)
	{
		bullet->Draw();//’e‚Ì•`‰æ
	}
}

void NormalEnemy::SpawnUpdate(Camera* camera, GameTimer* gameTimer)
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

void NormalEnemy::DeathUpdate(Camera* camera, GameTimer* gameTimer)
{
	//€–SŠÔ‚É‚È‚Á‚½‚ç€‚Ê
	if (deathTime_ <= gameTimer->GetIntTime())
	{
		if (deathAnimationFlag_ == false)
		{
			emitter_->Create(enemyTrans_.parentToTranslation);
		}
		deathAnimationFlag_ = true;
	}

	//€–S‰‰o‚ÌXVˆ—
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