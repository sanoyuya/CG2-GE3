#include "TitleScene.h"
#include"GameHeader.h"
#include"SceneChangeAnimation.h"

void TitleScene::Initialize()
{
	input_ = InputManager::GetInstance();

	title_ = std::make_unique<Sprite2D>();
	titleTex_ = TextureManager::GetInstance()->LoadTexture("Resources/default/defaultTitle.png");
	title_->Sprite2DInitialize(titleTex_);
}

void TitleScene::Destroy()
{

}

void TitleScene::Update()
{
	if (input_->KeyboardTriggerPush(DIK_SPACE))
	{
		SceneChangeAnimation::GetInstance()->Change("GAME");
	}
}

void TitleScene::Draw()
{
	title_->DrawSprite2D(GameHeader::windowsCenter_);

	SceneChangeAnimation::GetInstance()->Draw();
}