#include "HPBar.h"
#include"EasingFunction.h"
uint32_t HPBar::sHpBarTex_;
uint32_t HPBar::sHpBarFlameTex_;

void HPBar::Initialize(const int8_t maxHp, const myMath::Vector2 leftUpPoint)
{
	hpBar_ = std::make_unique<Sprite>();
	hpBar_->Sprite2DInitialize(sHpBarTex_);
	hpBarFlame_ = std::make_unique<Sprite>();
	hpBarFlame_->Sprite2DInitialize(sHpBarFlameTex_);

	maxHp_ = maxHp;
	hp_ = maxHp;
	leftUpPoint_ = leftUpPoint;
	hpBarScale_ = maxHp;
}

void HPBar::Update(const int8_t hp)
{
	if (hp_ != hp)
	{
		hp_ = hp;
		animationTimer_ = 0;
		animationFlag_ = true;
	}

	if (animationFlag_ == true)
	{
		hpBarScale_ = static_cast<float>(Easing::EaseOutCirc(animationTimer_, hpBarScale_, hp_, maxAnimationTimer_));
		animationTimer_++;
		if (animationTimer_ >= maxAnimationTimer_)
		{
			animationTimer_ = 0;
			animationFlag_ = false;
		}
	}

	if (hp_ > maxHp_ / 2)
	{
		hpColor = { 130.0f / 255.0f,174.0f / 255.0f,70.0f / 255.0f,1.0f };
	}
	else if (hp_ > maxHp_ / 4 && hp_ <= maxHp_ / 2)
	{
		hpColor = { 255.0f / 255.0f,217.0f / 255.0f,0.0f / 255.0f,1.0f };
	}
	else
	{
		hpColor = { 255.0f / 255.0f,0.0f / 255.0f,0.0f / 255.0f,1.0f };
	}
}

void HPBar::Draw()
{
	hpBar_->DrawSprite2D(leftUpPoint_, hpColor, { 25.0f * hpBarScale_,14.0f }, 0.0f, { 0.0f,0.0f });
	hpBarFlame_->DrawSprite2D({ leftUpPoint_.x + 25.0f * 5.0f ,leftUpPoint_.y + 7.0f });
}

void HPBar::LoadAsset()
{
	sHpBarTex_ = TextureManager::GetInstance()->LoadTexture("Resources/Texture/white1x1.png");
	sHpBarFlameTex_ = TextureManager::GetInstance()->LoadTexture("Resources/Texture/hpFlame.png");
}