#include "EngineOP.h"
#include"SceneManager.h"

void EngineOP::Initialize()
{
	engineLogo_ = std::make_unique<Sprite>();
	engineLogoTex_ = engineLogo_->LoadTexture("Resources/EngineLogo.png");
	engineLogo_->Sprite2DInitialize(engineLogoTex_);
	logoColor_ = { 1.0f,1.0f,1.0f,0.0f };

	back_ = std::make_unique<Sprite>();
	backTex_ = back_->LoadTexture("Resources/white1x1.png");
	back_->Sprite2DInitialize(backTex_);
}

void EngineOP::Destroy()
{
}

void EngineOP::Update()
{
	animationTimer_++;
	if (animationTimer_ <= 90)
	{
		logoColor_.w += 1.0f / 90;
	}
	else if (animationTimer_ > 90 && animationTimer_ <= animationEndTime_)
	{
		logoColor_.w -= 1.0f / 90;
	}

	if (animationTimer_ >= animationEndTime_)
	{
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}
}

void EngineOP::Draw()
{
	back_->DrawSprite2D(center_, { 0.0f,0.0f,0.0f,1.0f }, { 1280,720 });
	engineLogo_->DrawSprite2D(center_, logoColor_);
}