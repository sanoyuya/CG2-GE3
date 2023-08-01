#include "HPBar.h"

void HPBar::Initialize(const int8_t maxHp, const myMath::Vector2 leftUpPoint)
{
	hpBar_ = std::make_unique<Sprite>();
	hpBarTex_ = hpBar_->LoadTexture("Resources/white1x1.png");
	hpBar_->Sprite2DInitialize(hpBarTex_);
	maxHp_ = maxHp;
	leftUpPoint_ = leftUpPoint;
}

void HPBar::Update(const int8_t hp)
{
	hp_ = hp;
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
	hpBar_->DrawSprite2D(leftUpPoint_, hpColor, { 20.0f * hp_,20.0f }, 0.0f, { 0.0f,0.0f });
}