#include "NormalBullet.h"
#include"ColliderManager.h"

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

void NormalBullet::SetPos(const myMath::Vector3& position)
{
	bulletTrans_.translation = position;
}

void NormalBullet::SetOwner(BulletOwner owner)
{
	owner = owner_;
}

void NormalBullet::SetDirectionVector(const myMath::Vector3& directionVector)
{
	directionVector_ = directionVector;
}

BulletOwner NormalBullet::GetOwner()
{
	return owner_;
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

bool NormalBullet::GetIsDead()
{
	return isDead_;
}

void NormalBullet::OnCollision()
{
	isDead_ = true;
}

const myMath::Vector3& NormalBullet::GetPosition()
{
	return bulletTrans_.translation;
}
