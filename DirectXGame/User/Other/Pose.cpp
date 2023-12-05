#include "Pose.h"
#include"GameHeader.h"

void Pose::Initialize()
{
	poseSprite_ = std::make_unique<Sprite>();
	poseTex_ = poseSprite_->LoadTexture("Resources/pose.png");
	poseSprite_->Sprite2DInitialize(poseTex_);

	poseBack_ = std::make_unique<Sprite>();
	poseBackTex_ = poseBack_->LoadTexture("Resources/white1x1.png");
	poseBack_->Sprite2DInitialize(poseBackTex_);
}

void Pose::Update()
{
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

Pose* Pose::GetInstance()
{
	static Pose instance;
	return &instance;
}
