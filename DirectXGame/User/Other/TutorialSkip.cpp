#include "TutorialSkip.h"

void TutorialSkip::Initialize(GameTimer* gameTimer)
{
	input_ = InputManager::GetInstance();

	text_ = std::make_unique<Sprite2D>();
	textTex_ = TextureManager::GetInstance()->LoadTexture("Resources/skip.png");
	text_->Sprite2DInitialize(textTex_);

	gameTimer_ = gameTimer;
}

void TutorialSkip::Update()
{
	if (input_->ControllerButtonTriggerPush(Y)||input_->KeyboardTriggerPush(DIK_RETURN))
	{
		gameTimer_->SetFlameTime(startTime_ * 60.0f);
	}
	if (gameTimer_->GetIntTime() >= startTime_)
	{
		drawFlag_ = false;
	}
	else
	{
		if (gameTimer_->GetIntTime() % 2 == 0)
		{
			drawFlag_ = true;
		}
		else
		{
			drawFlag_ = false;
		}
	}
}

void TutorialSkip::Draw()
{
	if (drawFlag_ == true)
	{
		text_->DrawSprite2D({ 1075.0f,75.0f });
	}
}

void TutorialSkip::SetGameStartTime(uint16_t startTime)
{
	startTime_ = startTime;
}