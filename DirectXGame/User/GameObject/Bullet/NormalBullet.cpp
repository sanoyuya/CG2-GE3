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

	//パーティクルの初期化
	smokeEmitter_ = std::make_unique<PlayerEngineSmokeParticleEmitter>();
	smokeEmitter_->Initialize();
	smokeTrans_.Initialize();

	collisionData_.radius = 1.0f;
}

void NormalBullet::Update()
{
	deathTimer_++;
	if (deathTimer_ > maxDeathTime_)
	{
		isDead_ = true;
	}
	bulletTrans_.translation += directionVector_ * speed_;
	bulletTrans_.TransUpdate(camera_);

	collisionData_.center = bulletTrans_.translation;

	SmokeUpdate();
}

void NormalBullet::Draw()
{
	bullet_->DrawModel(&bulletTrans_);
	smokeEmitter_->Draw();
}

std::string NormalBullet::GetName()
{
	return name_;
}

const CollisionData& NormalBullet::GetCollisionData()
{
	return collisionData_;
}

void NormalBullet::OnCollision()
{
	isDead_ = true;
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

void NormalBullet::SetCamera(Camera* camera)
{
	camera_ = camera;
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

void NormalBullet::SetTargetPos(const myMath::Vector3& position)
{
	position;
}

void NormalBullet::SetControlPos(const myMath::Vector3& position)
{
	position;
}

void NormalBullet::SmokeUpdate()
{
	//エンジンの座標に合わせるため、モデルの中心座標から位置をずらせるように子を作成
	smokeTrans_.parent = &bulletTrans_;
	//モデルの中心座標から位置をずらす
	smokeTrans_.translation = { 0.0f,0.0f,-1.0f };
	//子の更新処理
	smokeTrans_.TransUpdate(camera_);
	//パーティクルを毎フレーム作成
	smokeEmitter_->Create(smokeTrans_.parentToTranslation);
	//パーティクルの更新
	smokeEmitter_->Update(camera_);
}