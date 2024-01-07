#include "HitEffect.h"
#include"EasingFunction.h"
uint32_t HitEffect::hitTex_ = 0;

void HitEffect::LoadAsset()
{
	hitTex_ = TextureManager::GetInstance()->LoadTexture("Resources/Texture/Hit.png");
}

void HitEffect::Initialize()
{
	hit_ = std::make_unique<Sprite>();
	hit_->Sprite3DInitialize(hitTex_);
	hitTrans_.Initialize();
	hitTrans_.scale = { 1.0f / 25.0f,1.0f / 25.0f ,1.0f / 25.0f };
}

void HitEffect::Create(const myMath::Vector3& pos)
{
	animationFlag_ = true;
	animationTimer_ = 0;
	hitTrans_.translation = pos;
	pos_ = pos;
}

void HitEffect::Update(Camera* camera)
{
	if (animationFlag_ == true)
	{
		animationTimer_++;

		hitTrans_.translation.y = static_cast<float>(Easing::EaseOutQuint(animationTimer_, pos_.y, pos_.y + 4.0f, maxAnimationTime_));
		alpha_= static_cast<float>(Easing::EaseInCirc(animationTimer_, 1.0f, 0.0f, maxAnimationTime_));
	}

	if (animationTimer_ > maxAnimationTime_)
	{
		animationTimer_ = 0.0f;
		animationFlag_ = false;
	}

	hitTrans_.TransUpdate(camera);
}

void HitEffect::Draw(Camera* camera)
{
	if (animationFlag_ == true)
	{
		hit_->DrawSprite3D(camera, hitTrans_, BillboardFlag::AllBillboard,{1.0f,1.0f ,1.0f ,alpha_});
	}
}
