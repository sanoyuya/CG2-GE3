#include "StageSelectScene.h"
#include"Retention.h"
#include <algorithm>
#include"SceneChangeAnimation.h"
#include"GameHeader.h"
uint32_t StageSelectScene::sStageNumSpriteTex_;

void StageSelectScene::Initialize()
{
	input_ = InputManager::GetInstance();

	stageNumSprite_ = std::make_unique<Sprite>();
	stageNumSprite_->Sprite2DInitialize(sStageNumSpriteTex_);
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

void StageSelectScene::LoadAsset()
{
	sStageNumSpriteTex_ = TextureManager::GetInstance()->LoadTexture("Resources/Texture/number.png");
}

void StageSelectScene::Select()
{
	if (input_->KeyboardTriggerPush(DIK_SPACE) || input_->ControllerButtonTriggerPush(A))
	{
		Retention::GetInstance()->SetStageNum(stageNum_);
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