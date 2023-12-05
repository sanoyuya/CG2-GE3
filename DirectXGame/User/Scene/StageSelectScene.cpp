#include "StageSelectScene.h"
#include"Retention.h"
#include <algorithm>
#include"SceneChangeAnimation.h"
#include"GameHeader.h"

void StageSelectScene::Initialize()
{
	input_ = InputManager::GetInstance();

	stageNumSprite_ = std::make_unique<Sprite>();
	stageNumSpriteTex_ = stageNumSprite_->LoadTexture("Resources/number.png");
	stageNumSprite_->Sprite2DInitialize(stageNumSpriteTex_);
}

void StageSelectScene::Destroy()
{
}

void StageSelectScene::Update()
{
	Select();
}

void StageSelectScene::Draw()
{
	stageNumSprite_->DrawAnimationSpriteX2D(GameHeader::windowsCenter_, 10, stageNum_);
	SceneChangeAnimation::GetInstance()->Draw();
}

void StageSelectScene::Select()
{
	if (input_->KeyboardTriggerPush(DIK_SPACE) || input_->ControllerButtonTriggerPush(A))
	{
		Retention::GetInstance()->SetStageNum(static_cast<Stage>(stageNum_));
		SceneChangeAnimation::GetInstance()->Change("GAME");
	}
	else if (input_->KeyboardTriggerPush(DIK_RIGHT) || input_->ControllerStickTriggerPush(L_RIGHT))
	{
		stageNum_++;
	}
	else if (input_->KeyboardTriggerPush(DIK_LEFT) || input_->ControllerStickTriggerPush(L_LEFT))
	{
		stageNum_--;
	}
	stageNum_ = std::clamp(stageNum_, minStage, maxStage);
}