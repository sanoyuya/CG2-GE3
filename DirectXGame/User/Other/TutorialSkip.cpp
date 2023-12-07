#include "TutorialSkip.h"
#include"EasingFunction.h"
#include"GameHeader.h"

void TutorialSkip::Initialize(GameTimer* gameTimer)
{
	input_ = InputManager::GetInstance();

	text_ = std::make_unique<Sprite2D>();
	textTex_ = TextureManager::GetInstance()->LoadTexture("Resources/skip.png");
	text_->Sprite2DInitialize(textTex_);

	back_ = std::make_unique<Sprite2D>();
	backTex_ = TextureManager::GetInstance()->LoadTexture("Resources/white1x1.png");
	back_->Sprite2DInitialize(backTex_);

	gameTimer_ = gameTimer;
}

void TutorialSkip::Update()
{
	if (animationFlag_ == true)
	{
		animationTimer_++;

		if (animationTimer_ <= (maxAnimationTime_ - isSkipAnimationTime_) / 2)
		{
			alpha_ = static_cast<float>(Easing::EaseInQuint(static_cast<double>(animationTimer_), 0.0f, 1.0f, (maxAnimationTime_ - isSkipAnimationTime_) / 2));
		}
		else if (animationTimer_ == (maxAnimationTime_ - isSkipAnimationTime_) / 2 + 1)
		{
			gameTimer_->SetFlameTime(startTime_ * 60.0f);
		}
		else if (animationTimer_ > (maxAnimationTime_ - isSkipAnimationTime_) / 2 && animationTimer_ <= (maxAnimationTime_ - isSkipAnimationTime_) / 2 + isSkipAnimationTime_)
		{
			alpha_ = 1.0f;
		}
		else if(animationTimer_<= maxAnimationTime_)
		{
			alpha_ = static_cast<float>(Easing::EaseInOutQuint(static_cast<double>(animationTimer_-((maxAnimationTime_ - isSkipAnimationTime_) / 2 + isSkipAnimationTime_)), 1.0f, 0.0f, (maxAnimationTime_ - isSkipAnimationTime_) / 2));
		}
		else
		{
			animationFlag_ = false;
		}
	}

	if (input_->ControllerButtonTriggerPush(Y)||input_->KeyboardTriggerPush(DIK_RETURN))
	{
		animationFlag_ = true;
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
	back_->DrawSprite2D(GameHeader::windowsCenter_, { 0.0f,0.0f,0.0f ,alpha_ }, GameHeader::windowsSize_);
}

void TutorialSkip::SetGameStartTime(uint16_t startTime)
{
	startTime_ = startTime;
}

void TutorialSkip::Reset()
{
	animationFlag_ = false;
	animationTimer_ = 0;
	alpha_ = 0.0f;
}