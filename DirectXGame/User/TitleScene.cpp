#include "TitleScene.h"
#include"SceneManager.h"

void TitleScene::Initialize()
{
	input = InputManager::GetInstance();
}

void TitleScene::Destroy()
{
}

void TitleScene::Update()
{
	if (input->KeyboardTriggerPush(DIK_SPACE))
	{
		SceneManager::GetInstance()->ChangeScene("GAME");
	}
}

void TitleScene::Draw()
{
}