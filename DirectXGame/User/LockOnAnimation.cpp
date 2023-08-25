#include "LockOnAnimation.h"

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
}

void LockOnAnimation::Update()
{
}

void LockOnAnimation::Draw()
{
}
