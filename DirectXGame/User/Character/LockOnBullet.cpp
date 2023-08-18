#include "LockOnBullet.h"
#include"ColliderManager.h"
#include"EasingFunction.h"

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

	collisionData_.radius = 1.0f;
}

void LockOnBullet::Update()
{
	deathTimer_++;
	if (deathTimer_ > maxDeathTime_)
	{
		isDead_ = true;
	}
	
	BulletMove();

	collisionData_.center = bulletTrans_.translation;

	SmokeUpdate();
}

void LockOnBullet::Draw()
{
	bullet_->DrawModel(&bulletTrans_);
	smokeEmitter_->Draw();
}

std::string LockOnBullet::GetName()
{
	return name_;
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

void LockOnBullet::SetTargetPos(const myMath::Vector3& position)
{
	targetPos_ = position;
}

void LockOnBullet::SetControlPos(const myMath::Vector3& position)
{
	controlPos_ = position;
}

void LockOnBullet::SmokeUpdate()
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

void LockOnBullet::BulletMove()
{
	//弾の移動にベジエ補間をかける
	bulletTrans_.translation = myMath::Beziers(startPos_, targetPos_, controlPos_, beziersTime_);

	//ベジエ補間にイージング補間をかける
	beziersTime_ = static_cast<float>(Easing::EaseInCirc(deathTimer_, 0.0f, 60.0f, 60.0f));

	bulletTrans_.TransUpdate(camera_);
}