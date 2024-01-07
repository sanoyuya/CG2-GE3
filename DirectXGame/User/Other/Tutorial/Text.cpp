#include "Text.h"
#include"EasingFunction.h"
#include"GameHeader.h"
std::array<uint32_t, 6> Text::sTextTex_;
uint32_t Text::sFrameTex_;

void Text::Initialize(const TextName& textFlag)
{
	textTex_ = sTextTex_[static_cast<uint8_t>(textFlag)];

	for (uint8_t i = 0; i < frame_.size(); i++)
	{
		frame_[i] = std::make_unique<Sprite2D>();
		frame_[i]->Sprite2DInitialize(sFrameTex_);
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
	if (startTime * GameHeader::sFps_ <= gameTimer->GetFlameCount() && gameTimer->GetFlameCount() <= endTime * GameHeader::sFps_)
	{
		drawFrag_ = true;

		if (startTime * GameHeader::sFps_ <= gameTimer->GetFlameCount() && gameTimer->GetFlameCount() <= startTime * GameHeader::sFps_ + time_)
		{
			Begin(gameTimer, startTime);
		}
		else if (endTime * GameHeader::sFps_ - time_ <= gameTimer->GetFlameCount() && gameTimer->GetFlameCount() <= endTime * GameHeader::sFps_)
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

void Text::LoadAsset()
{
	sFrameTex_ = TextureManager::GetInstance()->LoadTexture("Resources/Texture/white1x1.png");
	sTextTex_[static_cast<uint8_t>(TextName::MOVE)] = TextureManager::GetInstance()->LoadTexture("Resources/Texture/move.png");
	sTextTex_[static_cast<uint8_t>(TextName::ATTACK)] = TextureManager::GetInstance()->LoadTexture("Resources/Texture/attack.png");
	sTextTex_[static_cast<uint8_t>(TextName::CAMERAMOVE)] = TextureManager::GetInstance()->LoadTexture("Resources/Texture/camera.png");
	sTextTex_[static_cast<uint8_t>(TextName::CHARGEATTACK)] = TextureManager::GetInstance()->LoadTexture("Resources/Texture/chargeAttack.png");
	sTextTex_[static_cast<uint8_t>(TextName::READY)] = TextureManager::GetInstance()->LoadTexture("Resources/Texture/ready.png");
	sTextTex_[static_cast<uint8_t>(TextName::GO)] = TextureManager::GetInstance()->LoadTexture("Resources/Texture/go.png");
}

void Text::Begin(GameTimer* gameTimer, uint8_t startTime)
{
	frameScale_[0] = static_cast<float>(Easing::EaseOutCubic(gameTimer->GetFlameCount() - startTime * GameHeader::sFps_, 0.0f, frameSize_.x * 2, time_));
	frameScale_[1] = static_cast<float>(Easing::EaseOutCubic(gameTimer->GetFlameCount() - startTime * GameHeader::sFps_, 0.0f, frameSize_.y * 2, time_));
	frameScale_[2] = static_cast<float>(Easing::EaseOutCubic(gameTimer->GetFlameCount() - startTime * GameHeader::sFps_, 0.0f, frameSize_.x * 2, time_));
	frameScale_[3] = static_cast<float>(Easing::EaseOutCubic(gameTimer->GetFlameCount() - startTime * GameHeader::sFps_, 0.0f, frameSize_.y * 2, time_));

	textAlpha_ = static_cast<float>(Easing::EaseOutCubic(gameTimer->GetFlameCount() - startTime * GameHeader::sFps_, 0.0f, 1.0f, time_));
}

void Text::End(GameTimer* gameTimer, uint8_t endTime)
{
	frameScale_[0] = static_cast<float>(Easing::EaseInCubic(gameTimer->GetFlameCount() - (endTime - 1) * GameHeader::sFps_, frameSize_.x * 2, 0.0f, time_));
	frameScale_[1] = static_cast<float>(Easing::EaseInCubic(gameTimer->GetFlameCount() - (endTime - 1) * GameHeader::sFps_, frameSize_.y * 2, 0.0f, time_));
	frameScale_[2] = static_cast<float>(Easing::EaseInCubic(gameTimer->GetFlameCount() - (endTime - 1) * GameHeader::sFps_, frameSize_.x * 2, 0.0f, time_));
	frameScale_[3] = static_cast<float>(Easing::EaseInCubic(gameTimer->GetFlameCount() - (endTime - 1) * GameHeader::sFps_, frameSize_.y * 2, 0.0f, time_));

	textAlpha_ = static_cast<float>(Easing::EaseInCubic(gameTimer->GetFlameCount() - (endTime - 1) * GameHeader::sFps_, 1.0f, 0.0f, time_));
}