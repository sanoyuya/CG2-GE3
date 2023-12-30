#include "NormalBullet.h"
#include"ColliderManager.h"

NormalBullet::~NormalBullet()
{
	ColliderManager::GetInstance()->SubCollision(this);
}

void NormalBullet::Initialize()
{
	bullet_ = std::make_unique<Model>();
	bulletTex_ = bullet_->CreateObjModel("Resources/sphere");
	bullet_->SetModel(bulletTex_);
	bulletTrans_.Initialize();

	smokeEmitter_->SetSize(2.0f);

	//死亡アニメーションパーティクル初期化
	deathParticleEmitter_ = std::make_unique<EnemyDeathParticleEmitter>();
	deathParticleEmitter_->Initialize();

	collisionData_.radius = 1.0f;
}

void NormalBullet::Update()
{
	deathTimer_++;
	if (deathAnimationFlag_ == false)
	{
		if (deathTimer_ > maxDeathTime_)
		{
			isDead_ = true;
		}
	}
	else
	{
		if (animationTimer_ > maxAnimationTime_)
		{
			isDead_ = true;
		}
		deathParticleEmitter_->Update(sCamera_);
		animationTimer_++;
	}
	bulletTrans_.translation += directionVector_ * speed_ * sGameTimer_->GetTimeSpeed();
	bulletTrans_.TransUpdate(sCamera_);

	collisionData_.center = bulletTrans_.translation;

	//パーティクルを毎フレーム作成
	smokeEmitter_->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	smokeEmitter_->Create(bulletTrans_.translation);
}

void NormalBullet::Draw()
{
	if (deathAnimationFlag_ == true)
	{
		deathParticleEmitter_->Draw();
	}
	else
	{
		//当たり判定描画用球
		//bullet_->DrawModel(&bulletTrans_);
	}
}

std::string NormalBullet::GetName()
{
	return name_;
}

const Transform& NormalBullet::GetTransform()
{
	return bulletTrans_;
}

const CollisionData& NormalBullet::GetCollisionData()
{
	return collisionData_;
}

void NormalBullet::OnCollision()
{
	isDead_ = true;
}

void NormalBullet::BulletDeathAnimation()
{
	deathAnimationFlag_ = true;
	deathFlag_ = true;
	deathParticleEmitter_->Create(bulletTrans_.translation);
}

const bool NormalBullet::GetDeathFlag()
{
	return deathFlag_;
}

const bool NormalBullet::GetIsDead()
{
	return isDead_;
}

const bool NormalBullet::GetDeathAnimationFlag()
{
	return false;
}

void NormalBullet::LockOn()
{
}

void NormalBullet::CancelLockOn()
{
}

const bool NormalBullet::GetLockOnFlag()
{
	return false;
}

void NormalBullet::SetPos(const myMath::Vector3& position)
{
	bulletTrans_.translation = position;
}

void NormalBullet::SetDirectionVector(const myMath::Vector3& directionVector)
{
	directionVector_ = directionVector;
}

void NormalBullet::SetOwner(BulletOwner owner)
{
	owner_ = owner;
}

void NormalBullet::SetName(const std::string& name)
{
	name_ = name;
}

void NormalBullet::SetTargetPos(GameObject* lockOnEnemy)
{
	lockOnEnemy;
}

void NormalBullet::SetControlPos(const myMath::Vector3& position)
{
	position;
}