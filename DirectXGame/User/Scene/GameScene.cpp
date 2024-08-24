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

	player_ = std::make_unique<Player>();
	player_->Initialize();
}

void GameScene::Destroy()
{

}

void GameScene::Update()
{
	gameTimer_->Update();
	gameTimer_->ImGuiUpdate();

	player_->Update();
}

void GameScene::Draw()
{
	SceneChangeAnimation::GetInstance()->Draw();
}