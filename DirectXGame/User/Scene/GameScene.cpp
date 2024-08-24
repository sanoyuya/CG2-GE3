#include "GameScene.h"
#include"GameHeader.h"
#include"SceneChangeAnimation.h"
#include"EasingFunction.h"
#include <algorithm>
#include<imgui.h>

void GameScene::Initialize()
{
	input_ = InputManager::GetInstance();

	gameTimer_ = std::make_unique<GameTimer>();
}

void GameScene::Destroy()
{

}

void GameScene::Update()
{
	gameTimer_->Update();
	gameTimer_->ImGuiUpdate();
}

void GameScene::Draw()
{
	SceneChangeAnimation::GetInstance()->Draw();
}