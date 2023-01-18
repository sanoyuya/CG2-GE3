#include "TitleScene.h"

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
		sceneManager->ChangeScene("GAME");
	}
}

void TitleScene::Draw()
{
}
