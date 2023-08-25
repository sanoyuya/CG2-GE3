#include "LockOnAnimation.h"
#include "EasingFunction.h"

void LockOnAnimation::Initialize()
{
	lockOnSprite_ = std::make_unique<Sprite>();
	lockOnTex_ = lockOnSprite_->LoadTexture("Resources/reticle.png");
	lockOnSprite_->Sprite3DInitialize(lockOnTex_);
	lockOnTrans_.Initialize();
	lockOnTrans_.scale = { 1.0f / 5.0f,1.0f / 5.0f ,1.0f / 5.0f };
}

void LockOnAnimation::Create()
{
	lockOnAnimationFlag = true;
}

void LockOnAnimation::Cancel()
{
	lockOnAnimationFlag = false;
}

void LockOnAnimation::Update(const myMath::Vector3& position,Camera* camera)
{
	lockOnTrans_.translation = position;

	if (lockOnAnimationFlag == true)
	{
		lockOnAnimationTimer++;

		//ägèkââèo
		lockOnTrans_.scale = { static_cast<float>(Easing::EaseOutBack(lockOnAnimationTimer,0.0f,1.0f / 5.0f,15.0f,6.0f,4.0f)),
			static_cast<float>(Easing::EaseOutBack(lockOnAnimationTimer,0.0f,1.0f / 5.0f,15.0f,6.0f,4.0f)),
			1.0f };

		//âÒì]ââèo
		lockOnTrans_.rotation.z = static_cast<float>(Easing::EaseOutCirc(lockOnAnimationTimer, 0.0f, -myMath::AX_2PIF, 15.0f));

		if (lockOnAnimationTimer > 15.0f)
		{
			lockOnAnimationFlag = false;
		}
	}

	lockOnTrans_.TransUpdate(camera);
}

void LockOnAnimation::Draw(Camera* camera)
{
	lockOnSprite_->DrawSprite3D(camera, lockOnTrans_, BillboardFlag::AllBillboard);
}
