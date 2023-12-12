#include "Reticle.h"
#include <algorithm>
#include "ColliderManager.h"
#include"EasingFunction.h"
myMath::Vector2 Reticle::addTargetAngle_;
uint32_t Reticle::sReticleTex_;
uint32_t Reticle::sReticleTex2_;

void Reticle::Initialize()
{
	input_ = InputManager::GetInstance();

	//スプライトの初期化
	reticle_ = std::make_unique<Sprite>();
	reticle_->Sprite3DInitialize(sReticleTex_);
	reticleTrans_.Initialize();
	reticleTrans_.translation = { 0.0f,-reticleLimit_,200.0f };
	reticleTrans_.scale = { 0.5f,0.5f,1.0f };

	ColliderManager::GetInstance()->AddCollision(this);
}

std::string Reticle::GetName()
{
	return name_;
}

const CollisionData& Reticle::GetCollisionData()
{
	return collisionData;
}

void Reticle::OnCollision()
{
}

const bool Reticle::GetIsDead()
{
	return false;
}

void Reticle::Update()
{
	//カメラを親にする為に行列をTransformのmatWorldに登録
	cameraTrans_.matWorld = sCamera_->GetMatView();
	//レティクルの親にカメラを設定
	reticleTrans_.parent = &cameraTrans_;

	//移動処理
	Move();
	//移動制限処理
	ReticleLimit();
	//ロックオン攻撃に切り替わった時の動き
	ChangeReticleUpdate();

	//スプライトの更新処理
	reticleTrans_.TransUpdate(sCamera_);

	collisionData.rayStartPos = sCamera_->GetEye();
	collisionData.rayEndPos = reticleTrans_.parentToTranslation;
}

void Reticle::Draw()
{
	if (lockOnAttackFlag_ == false)
	{
		if (lockOnFlag_ == false)
		{
			reticle_->SetTexture3D(sReticleTex_);
		}
		else
		{
			reticle_->SetTexture3D(sReticleTex2_);
		}
		reticle_->DrawSprite3D(sCamera_, reticleTrans_);
	}
}

const bool Reticle::GetDeathAnimationFlag()
{
	return false;
}

const bool Reticle::GetLockOnFlag()
{
	return false;
}

void Reticle::LockOn()
{
}

void Reticle::CancelLockOn()
{
}

void Reticle::Reset()
{
	reticleTrans_.translation = { 0.0f,-reticleLimit_,200.0f };

	lockOnFlag_ = false;
	changeReticleFlag_ = false;
	animationTimer_ = 0;

	ColliderManager::GetInstance()->AddCollision(this);
}

const float Reticle::GetReticleLimit()
{
	return reticleLimit_;
}

const Transform& Reticle::GetTransform()
{
	return reticleTrans_;
}

const myMath::Vector2 Reticle::GetAddTargetAngle()
{
	return addTargetAngle_;
}

void Reticle::ChangeReticle()
{
	changeReticleFlag_ = true;
}

void Reticle::GetLockOnFlag(const bool flag)
{
	lockOnFlag_ = flag;
}

void Reticle::GetLockOnAttackFlag(const bool flag)
{
	lockOnAttackFlag_ = flag;
}

void Reticle::GetCameraFlag(const int8_t flag)
{
	cameraFlag_ = flag;
}

void Reticle::LoadAsset()
{
	sReticleTex_ = TextureManager::GetInstance()->LoadTexture("Resources/reticle.png");
	sReticleTex2_ = TextureManager::GetInstance()->LoadTexture("Resources/reticle2.png");
}

void Reticle::Move()
{
#pragma region キーボード
	if (input_->KeyboardKeepPush(DIK_UP))
	{
		reticleTrans_.translation += {0.0f, reticleSpeed_* sGameTimer_->GetTimeSpeed(), 0.0f};
	}
	if (input_->KeyboardKeepPush(DIK_LEFT))
	{
		reticleTrans_.translation += {-reticleSpeed_ * sGameTimer_->GetTimeSpeed(), 0.0f, 0.0f};
	}
	if (input_->KeyboardKeepPush(DIK_DOWN))
	{
		reticleTrans_.translation += {0.0f, -reticleSpeed_ * sGameTimer_->GetTimeSpeed(), 0.0f};
	}
	if (input_->KeyboardKeepPush(DIK_RIGHT))
	{
		reticleTrans_.translation += {reticleSpeed_* sGameTimer_->GetTimeSpeed(), 0.0f, 0.0f};
	}
#pragma endregion キーボード

#pragma region コントローラー

	//Lスティックを傾けることで移動できるようにする
	reticleTrans_.translation += {reticleSpeed_* sGameTimer_->GetTimeSpeed()* input_->GetLeftStickVec().x, -reticleSpeed_ * sGameTimer_->GetTimeSpeed() * input_->GetLeftStickVec().y, 0.0f};

#pragma endregion コントローラー

	addTargetAngle_.x = myMath::ChangeRadians(reticleTrans_.translation.x / 45.0f * 20.0f / sGameTimer_->GetTimeSpeed());
	if (cameraFlag_ == 2)
	{
		addTargetAngle_.y = myMath::ChangeRadians(reticleTrans_.translation.y / 45.0f * 20.0f / sGameTimer_->GetTimeSpeed());
	}
	else
	{
		addTargetAngle_.y = -myMath::ChangeRadians(reticleTrans_.translation.y / 45.0f * 20.0f / sGameTimer_->GetTimeSpeed());
	}
}

void Reticle::ReticleLimit()
{
	reticleTrans_.translation.x = std::clamp(reticleTrans_.translation.x, -reticleLimit_, reticleLimit_);
	//画面比率に合わせた制限処理(x:y,16:9)
	reticleTrans_.translation.y = std::clamp(reticleTrans_.translation.y, -reticleLimit_ / 16 * 9, reticleLimit_ / 16 * 9);
}

void Reticle::ChangeReticleUpdate()
{
	if (changeReticleFlag_ == true)
	{
		animationTimer_++;

		//拡縮演出
		if (animationTimer_ <= maxAnimationTime_ / 2)
		{
			reticleTrans_.scale = { static_cast<float>(Easing::EaseOutCubic(animationTimer_,0.5f,0.25f,maxAnimationTime_ / 2)),//まずは小さくなる
			static_cast<float>(Easing::EaseOutCubic(animationTimer_,0.5f,0.25f,maxAnimationTime_ / 2)),
			1.0f };
		}
		else
		{
			reticleTrans_.scale = { static_cast<float>(Easing::EaseOutBack(animationTimer_ - maxAnimationTime_ / 2,0.25f,0.5f,maxAnimationTime_ / 2)),//まずは小さくなる
			static_cast<float>(Easing::EaseOutBack(animationTimer_ - maxAnimationTime_ / 2,0.25f,0.5f,maxAnimationTime_ / 2)),
			1.0f };
		}

		//回転演出
		reticleTrans_.rotation.z = static_cast<float>(Easing::EaseOutCirc(animationTimer_, 0.0f, -myMath::AX_2PIF, maxAnimationTime_));

		if (animationTimer_ >= maxAnimationTime_)
		{
			animationTimer_ = 0;
			changeReticleFlag_ = false;
		}
	}
}