#include "Text.h"
#include"EasingFunction.h"
#include"GameHeader.h"

void Text::Initialize(const std::string& filePath)
{
	frameTex_ = TextureManager::GetInstance()->LoadTexture("Resources/white1x1.png");
	textTex_= TextureManager::GetInstance()->LoadTexture(filePath);

	for (uint8_t i = 0; i < frame_.size(); i++)
	{
		frame_[i] = std::make_unique<Sprite2D>();
		frame_[i]->Sprite2DInitialize(frameTex_);
	}

	center_ = { GameHeader::windowsCenter_.x,GameHeader::windowsCenter_.y * 3 / 2 };
	frameSize_ = { GameHeader::windowsCenter_.x / 2,50.0f };

	framePos_[0] = { center_.x - frameSize_.x,center_.y - frameSize_.y };//上
	framePos_[1] = { center_.x + frameSize_.x,center_.y - frameSize_.y };//右
	framePos_[2] = { center_.x + frameSize_.x,center_.y + frameSize_.y };//下
	framePos_[3] = { center_.x - frameSize_.x,center_.y + frameSize_.y };//左

	text_ = std::make_unique<Sprite2D>();
	text_->Sprite2DInitialize(textTex_);
}

void Text::Update(GameTimer* gameTimer, uint8_t startTime, uint8_t endTime)
{
	if (startTime*60 <= gameTimer->GetFlameCount() && gameTimer->GetFlameCount() <= endTime * 60)
	{
		drawFrag_ = true;

		if (startTime * 60 <= gameTimer->GetFlameCount() && gameTimer->GetFlameCount()<= startTime * 60 + time_)
		{
			Begin(gameTimer, startTime);
		}
		else if (endTime * 60 - time_ <= gameTimer->GetFlameCount() && gameTimer->GetFlameCount() <= endTime * 60)
		{
			End(gameTimer, endTime);
		}
	}
	else
	{
		drawFrag_ = false;
	}
}

void Text::Draw()
{
	if (drawFrag_ == true)
	{
		frame_[0]->DrawSprite2D(framePos_[0], { 1.0f,1.0f ,1.0f ,1.0f }, { frameScale_[0],3.0f }, 0.0f, { 0.0f,0.5f });//上
		frame_[1]->DrawSprite2D(framePos_[1], { 1.0f,1.0f ,1.0f ,1.0f }, { 3.0f,frameScale_[1] }, 0.0f, { 0.5f,0.0f });//右
		frame_[2]->DrawSprite2D(framePos_[2], { 1.0f,1.0f ,1.0f ,1.0f }, { frameScale_[2],3.0f }, 0.0f, { 1.0f,0.5f });//下
		frame_[3]->DrawSprite2D(framePos_[3], { 1.0f,1.0f ,1.0f ,1.0f }, { 3.0f,frameScale_[3] }, 0.0f, { 0.5f,1.0f });//左

		text_->DrawSprite2D(center_, { 1.0f,1.0f,1.0f,textAlpha_ });
	}
}

void Text::Begin(GameTimer* gameTimer, uint8_t startTime)
{
	frameScale_[0] = static_cast<float>(Easing::EaseOutCubic(gameTimer->GetFlameCount() - startTime * 60, 0.0f, frameSize_.x * 2, time_));
	frameScale_[1] = static_cast<float>(Easing::EaseOutCubic(gameTimer->GetFlameCount() - startTime * 60, 0.0f, frameSize_.y * 2, time_));
	frameScale_[2] = static_cast<float>(Easing::EaseOutCubic(gameTimer->GetFlameCount() - startTime * 60, 0.0f, frameSize_.x * 2, time_));
	frameScale_[3] = static_cast<float>(Easing::EaseOutCubic(gameTimer->GetFlameCount() - startTime * 60, 0.0f, frameSize_.y * 2, time_));

	textAlpha_ = static_cast<float>(Easing::EaseOutCubic(gameTimer->GetFlameCount() - startTime * 60, 0.0f, 1.0f, time_));
}

void Text::End(GameTimer* gameTimer, uint8_t endTime)
{
	frameScale_[0] = static_cast<float>(Easing::EaseInCubic(gameTimer->GetFlameCount() - (endTime - 1) * 60, frameSize_.x * 2, 0.0f, time_));
	frameScale_[1] = static_cast<float>(Easing::EaseInCubic(gameTimer->GetFlameCount() - (endTime - 1) * 60, frameSize_.y * 2, 0.0f, time_));
	frameScale_[2] = static_cast<float>(Easing::EaseInCubic(gameTimer->GetFlameCount() - (endTime - 1) * 60, frameSize_.x * 2, 0.0f, time_));
	frameScale_[3] = static_cast<float>(Easing::EaseInCubic(gameTimer->GetFlameCount() - (endTime - 1) * 60, frameSize_.y * 2, 0.0f, time_));

	textAlpha_ = static_cast<float>(Easing::EaseInCubic(gameTimer->GetFlameCount() - (endTime - 1) * 60, 1.0f, 0.0f, time_));
}