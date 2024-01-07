#include "LockOnAnimation.h"
#include "EasingFunction.h"
uint32_t LockOnAnimation::sLockOnTex_;

void LockOnAnimation::Initialize()
{
	lockOnSprite_ = std::make_unique<Sprite>();
	lockOnSprite_->Sprite3DInitialize(sLockOnTex_);
	lockOnTrans_.Initialize();
	lockOnTrans_.scale = { 1.0f / 5.0f,1.0f / 5.0f ,1.0f / 5.0f };
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
		lockOnTrans_.scale = { static_cast<float>(Easing::EaseOutBack(lockOnAnimationTimer_,0.0f,1.0f / 5.0f,15.0f,6.0f,4.0f)),
			static_cast<float>(Easing::EaseOutBack(lockOnAnimationTimer_,0.0f,1.0f / 5.0f,15.0f,6.0f,4.0f)),
			1.0f };

		//回転演出
		lockOnTrans_.rotation.z = static_cast<float>(Easing::EaseOutCirc(lockOnAnimationTimer_, 0.0f, -myMath::AX_2PIF, 15.0f));

		if (lockOnAnimationTimer_ > 15.0f)
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