#include "ResultScene.h"
#include"TitleScene.h"

void ResultScene::Initialize()
{
	input = InputManager::GetInstance();
	sceneManager = SceneManager::GetInstance();
}

void ResultScene::Update()
{
	if (input->KeyboardTriggerPush(DIK_SPACE))
	{
		BaseScene* scene = new TitleScene();
		sceneManager->SetNextScene(scene);
	}
}

void ResultScene::Draw()
{
}

void ResultScene::Destroy()
{
}