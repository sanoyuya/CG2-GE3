#include "LockOnAnimation.h"
#include "EasingFunction.h"
uint32_t LockOnAnimation::sLockOnTex_;

void LockOnAnimation::Initialize()
{
	lockOnSprite_ = std::make_unique<Sprite>();
	lockOnSprite_->Sprite3DInitialize(sLockOnTex_);
	lockOnTrans_.Initialize();
	lockOnTrans_.scale = { 1.0f / scale_,1.0f / scale_ ,1.0f / scale_ };
}

void LockOnAnimation::Create()
{
	lockOnAnimationFlag_ = true;
}

void LockOnAnimation::Cancel()
{
	lockOnAnimationFlag_ = false;
	lockOnAnimationTimer_ = 0;
}

void LockOnAnimation::Update(const myMath::Vector3& position,Camera* camera)
{
	lockOnTrans_.translation = position;

	if (lockOnAnimationFlag_ == true)
	{
		lockOnAnimationTimer_++;

		//拡縮演出
		lockOnTrans_.scale = { static_cast<float>(Easing::EaseOutBack(lockOnAnimationTimer_,0.0f,1.0f / scale_,maxLockOnAnimationTimer_,scaleUpPower_,scaleDownPower_)),
			static_cast<float>(Easing::EaseOutBack(lockOnAnimationTimer_,0.0f,1.0f / scale_,maxLockOnAnimationTimer_,scaleUpPower_,scaleDownPower_)),
			1.0f };

		//回転演出
		lockOnTrans_.rotation.z = static_cast<float>(Easing::EaseOutCirc(lockOnAnimationTimer_, 0.0f, -myMath::AX_2PIF, maxLockOnAnimationTimer_));

		if (lockOnAnimationTimer_ > maxLockOnAnimationTimer_)
		{
			lockOnAnimationFlag_ = false;
		}
	}

	lockOnTrans_.TransUpdate(camera);
}

void LockOnAnimation::Draw(Camera* camera)
{
	lockOnSprite_->DrawSprite3D(camera, lockOnTrans_, BillboardFlag::AllBillboard);
}

void LockOnAnimation::LoadAsset()
{
	sLockOnTex_ = TextureManager::GetInstance()->LoadTexture("Resources/Texture/reticle.png");
}