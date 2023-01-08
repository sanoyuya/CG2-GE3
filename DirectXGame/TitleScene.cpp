#include "TitleScene.h"
#include"GameScene.h"

void TitleScene::Initialize()
{
	input = InputManager::GetInstance();
	sceneManager = SceneManager::GetInstance();
}

void TitleScene::Destroy()
{
}

void TitleScene::Update()
{
	if (input->KeyboardTriggerPush(DIK_SPACE))
	{
		BaseScene* gemeScene = new GameScene();
		sceneManager->SetNextScene(gemeScene);
	}
}

void TitleScene::Draw()
{
}
