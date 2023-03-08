#include "EngineOP.h"
#include"SceneManager.h"

void EngineOP::Initialize()
{
	engineLogo = std::make_unique<Sprite>();
	engineLogoTex = engineLogo->LoadTexture("Resources/EngineLogo.png");
	engineLogo->Sprite2DInitialize(engineLogoTex);
	logoColor = { 1.0f,1.0f,1.0f,0.0f };

	back = std::make_unique<Sprite>();
	backTex = back->LoadTexture("Resources/white1x1.png");
	back->Sprite2DInitialize(backTex);
}

void EngineOP::Destroy()
{
}

void EngineOP::Update()
{
	animationTimer++;
	if (animationTimer <= 90)
	{
		logoColor.w += 1.0f / 90;
	}
	else if (animationTimer > 90 && animationTimer <= animationEndTime)
	{
		logoColor.w -= 1.0f / 90;
	}

	if (animationTimer >= animationEndTime)
	{
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}
}

void EngineOP::Draw()
{
	back->DrawSprite2D(center, { 0.0f,0.0f,0.0f,1.0f }, { 1280,720 });
	engineLogo->DrawSprite2D(center, logoColor);
}