#include "Pose.h"
#include"GameHeader.h"
#include"SceneChangeAnimation.h"
#include <algorithm>
uint32_t Pose::sPoseTex_;
uint32_t Pose::sPoseBackTex_;
std::array<uint32_t, 3> Pose::sPoseSelectTex_;
uint32_t Pose::sPoseSelectFlameSpriteTex_;

void Pose::Initialize()
{
	input_ = InputManager::GetInstance();

	poseSprite_ = std::make_unique<Sprite>();
	poseSprite_->Sprite2DInitialize(sPoseTex_);

	poseBack_ = std::make_unique<Sprite>();
	poseBack_->Sprite2DInitialize(sPoseBackTex_);

	poseSelectFlameSprite_ = std::make_unique<Sprite>();
	poseSelectFlameSprite_->Sprite2DInitialize(sPoseSelectFlameSpriteTex_);

	for (uint8_t i = 0; i < 3; i++)
	{
		poseSelectSprite_[i] = std::make_unique<Sprite>();
	}
	poseSelectSprite_[0]->Sprite2DInitialize(sPoseSelectTex_[0]);
	poseSelectSprite_[1]->Sprite2DInitialize(sPoseSelectTex_[1]);
	poseSelectSprite_[2]->Sprite2DInitialize(sPoseSelectTex_[2]);
}

void Pose::Update()
{
	OpenPose();

	if (poseFlag_ == true)
	{
		PoseSelect();
	}
}

void Pose::Draw()
{
	if (poseFlag_ == true)
	{
		poseBack_->DrawSprite2D(GameHeader::windowsCenter_, { 0.0f,0.0f ,0.0f,0.70f }, GameHeader::windowsSize_);
		poseSprite_->DrawSprite2D({ 150.0f,100.0f });

		poseSelectSprite_[0]->DrawSprite2D({ GameHeader::windowsCenter_.x,GameHeader::windowsCenter_.y - betweenTheLines });
		poseSelectSprite_[1]->DrawSprite2D(GameHeader::windowsCenter_);
		poseSelectSprite_[2]->DrawSprite2D({ GameHeader::windowsCenter_.x,GameHeader::windowsCenter_.y + betweenTheLines });

		poseSelectFlameSprite_->DrawSprite2D({ GameHeader::windowsCenter_.x,GameHeader::windowsCenter_.y + poseModeNum_ * betweenTheLines - betweenTheLines });
	}
}

const bool Pose::GetPoseFlag()
{
	return poseFlag_;
}

const bool Pose::GetResetFlag()
{
	return resetFlag_;
}

void Pose::SetResetFlag(const bool flag)
{
	resetFlag_ = flag;
}

void Pose::LoadAsset()
{
	sPoseTex_ = TextureManager::GetInstance()->LoadTexture("Resources/Texture/pose.png");
	sPoseBackTex_ = TextureManager::GetInstance()->LoadTexture("Resources/Texture/white1x1.png");

	sPoseSelectFlameSpriteTex_ = TextureManager::GetInstance()->LoadTexture("Resources/Texture/poseSelectFlame.png");
	sPoseSelectTex_[0] = TextureManager::GetInstance()->LoadTexture("Resources/Texture/resume.png");
	sPoseSelectTex_[1] = TextureManager::GetInstance()->LoadTexture("Resources/Texture/restart.png");
	sPoseSelectTex_[2] = TextureManager::GetInstance()->LoadTexture("Resources/Texture/returnTitle.png");
}

void Pose::OpenPose()
{
	if (input_->KeyboardTriggerPush(DIK_P) || input_->ControllerButtonTriggerPush(START))
	{
		if (poseFlag_ == false)
		{
			poseFlag_ = true;
		}
		else
		{
			poseFlag_ = false;
		}
	}
}

void Pose::PoseSelect()
{
	if (input_->KeyboardTriggerPush(DIK_UP) || input_->ControllerStickTriggerPush(L_UP, 0.0f))
	{
		poseModeNum_--;
	}
	if (input_->KeyboardTriggerPush(DIK_DOWN) || input_->ControllerStickTriggerPush(L_DOWN, 0.0f))
	{
		poseModeNum_++;
	}
	poseModeNum_ = std::clamp(poseModeNum_, static_cast<int8_t>(0), static_cast<int8_t>(2));
	poseMode_ = static_cast<PoseMode>(poseModeNum_);

	if (input_->KeyboardTriggerPush(DIK_SPACE) || input_->ControllerButtonTriggerPush(A))
	{
		switch (poseMode_)
		{
		case PoseMode::RESUME:

			poseFlag_ = false;

			break;
		case PoseMode::RESTART:

			SceneChangeAnimation::GetInstance()->Change("GAME");
			poseFlag_ = false;

			break;
		case PoseMode::TITLE:

			SceneChangeAnimation::GetInstance()->Change("TITLE");
			poseFlag_ = false;

			break;
		default:
			break;
		}
	}
}