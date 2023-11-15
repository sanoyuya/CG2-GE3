#include "LockOnBullet.h"
#include"ColliderManager.h"
#include"EasingFunction.h"
#include"PhysicsMath.h"

LockOnBullet::~LockOnBullet()
{
	ColliderManager::GetInstance()->SubCollision(this);
}

void LockOnBullet::Initialize()
{
	bullet_ = std::make_unique<Model>();
	bulletTex_ = bullet_->CreateObjModel("Resources/sphere");
	bullet_->SetModel(bulletTex_);
	bulletTrans_.Initialize();

	//パーティクルの初期化
	smokeEmitter_ = std::make_unique<PlayerEngineSmokeParticleEmitter>();
	smokeEmitter_->Initialize();
	smokeTrans_.Initialize();
	smokeEmitter_->SetSize(2.0f);
	smokeEmitter_->SetColor({ 0.0f / 255.0f,183.0f / 255.0f,206.0f / 255.0f,1.0f });

	actualTrans_.Initialize();
	isPlus_ = myMath::GetRandPlusOrMinus();

	collisionData_.radius = 0.1f;
}

void LockOnBullet::Update()
{
	deathTimer_++;
	if (deathTimer_ > maxDeathTime_)
	{
		isDead_ = true;
		ColliderManager::GetInstance()->CancelLockOn();
	}
	
	BulletMove();

	collisionData_.center = bulletTrans_.translation;

	//パーティクルを毎フレーム作成
	smokeEmitter_->Create(actualTrans_.parentToTranslation);
	
	//パーティクルの更新
	smokeEmitter_->Update(camera_);
}

void LockOnBullet::Draw()
{
	//当たり判定用描画
	//bullet_->DrawModel(&bulletTrans_, { 0.0f / 255.0f,183.0f / 255.0f,206.0f / 255.0f,1.0f });
	smokeEmitter_->Draw();
}

std::string LockOnBullet::GetName()
{
	return name_;
}

const Transform& LockOnBullet::GetTransform()
{
	return bulletTrans_;
}

const CollisionData& LockOnBullet::GetCollisionData()
{
	return collisionData_;
}

void LockOnBullet::OnCollision()
{
	isDead_ = true;
}

const bool LockOnBullet::GetIsDead()
{
	return isDead_;
}

const bool LockOnBullet::GetDeathAnimationFlag()
{
	return false;
}

void LockOnBullet::LockOn()
{
}

void LockOnBullet::CancelLockOn()
{
}

const bool LockOnBullet::GetLockOnFlag()
{
	return false;
}

void LockOnBullet::SetCamera(Camera* camera)
{
	camera_ = camera;
}

void LockOnBullet::SetPos(const myMath::Vector3& position)
{
	bulletTrans_.translation = position;//念のため
	startPos_ = position;
}

void LockOnBullet::SetDirectionVector(const myMath::Vector3& directionVector)
{
	directionVector;
}

void LockOnBullet::SetOwner(BulletOwner owner)
{
	owner_ = owner;
}

void LockOnBullet::SetName(const std::string& name)
{
	name_ = name;
}

void LockOnBullet::SetTargetPos(GameObject* lockOnEnemy)
{
	lockOnEnemy_ = lockOnEnemy;
}

void LockOnBullet::SetControlPos(const myMath::Vector3& position)
{
	controlPos_ = position;
}

void LockOnBullet::BulletMove()
{
	//弾の移動にベジエ補間をかける
	bulletTrans_.translation = myMath::Beziers(startPos_, lockOnEnemy_->GetTransform().translation, controlPos_, beziersTime_ / static_cast<float>(maxDeathTime_));

	//ベジエ補間にイージング補間をかける
	beziersTime_ = static_cast<float>(Easing::EaseInOutCubic(deathTimer_, 0.0f, static_cast<float>(maxDeathTime_), static_cast<float>(maxDeathTime_)));

	bulletTrans_.TransUpdate(camera_);

	angle_ += 0.25f * myMath::GetRandPlusOrMinus();
	actualTrans_.parent = &bulletTrans_;
	actualTrans_.translation = { PhysicsMath::CircularMotion({},(1 - beziersTime_ * 1 / maxDeathTime_),angle_).x,PhysicsMath::CircularMotion({},(1 - beziersTime_ * 1 / maxDeathTime_),angle_).y,0.0f };
	actualTrans_.TransUpdate(camera_);
}