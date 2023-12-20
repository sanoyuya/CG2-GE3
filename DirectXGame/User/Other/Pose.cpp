#include "Pose.h"
#include"GameHeader.h"
uint32_t Pose::sPoseTex_;
uint32_t Pose::sPoseBackTex_;

void Pose::Initialize()
{
	input_ = InputManager::GetInstance();

	poseSprite_ = std::make_unique<Sprite>();
	poseSprite_->Sprite2DInitialize(sPoseTex_);

	poseBack_ = std::make_unique<Sprite>();
	poseBack_->Sprite2DInitialize(sPoseBackTex_);
}

void Pose::Update()
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

void Pose::Draw()
{
	if (poseFlag_ == true)
	{
		poseBack_->DrawSprite2D(GameHeader::windowsCenter_, { 0.0f,0.0f ,0.0f,0.70f }, GameHeader::windowsSize_);
		poseSprite_->DrawSprite2D({ 150.0f,100.0f });
	}
}

void Pose::SetPoseFlag(const bool flag)
{
	if (poseFlag_ != flag)
	{
		poseFlag_ = flag;
	}
}

const bool Pose::GetPoseFlag()
{
	return poseFlag_;
}

void Pose::LoadAsset()
{
	sPoseTex_ = TextureManager::GetInstance()->LoadTexture("Resources/pose.png");
	sPoseBackTex_ = TextureManager::GetInstance()->LoadTexture("Resources/white1x1.png");
}