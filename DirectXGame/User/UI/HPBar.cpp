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
		hpColor = greenColor_;
	}
	//HPが半分以下になったら黄色に
	else if (hp_ > maxHp_ / 4 && hp_ <= maxHp_ / 2)
	{
		hpColor = yellowColor_;
	}
	//HPが1/4以下になったら赤色に
	else
	{
		hpColor = redColor_;
	}
}

void HPBar::Draw()
{
	hpBar_->DrawSprite2D(leftUpPoint_, hpColor, { hpScale_.x * hpBarScale_,hpScale_.y }, 0.0f, { 0.0f,0.0f });
	hpBarFlame_->DrawSprite2D({ leftUpPoint_.x + hpScale_.x * maxHp_ / 2 ,leftUpPoint_.y + hpScale_.y / 2 });
}

void HPBar::LoadAsset()
{
	sHpBarTex_ = TextureManager::GetInstance()->LoadTexture("Resources/Texture/white1x1.png");
	sHpBarFlameTex_ = TextureManager::GetInstance()->LoadTexture("Resources/Texture/hpFlame.png");
}