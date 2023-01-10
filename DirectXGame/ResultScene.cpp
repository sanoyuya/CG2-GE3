#include "ResultScene.h"
#include"TitleScene.h"

void ResultScene::Initialize()
{
	input = InputManager::GetInstance();
	sceneManager = SceneManager::GetInstance();
	score = Score::GetInstance();
	score->SetTimePos({ 640,360 });
}

void ResultScene::Update()
{
	if (input->KeyboardTriggerPush(DIK_SPACE) || input->ControllerButtonTriggerPush(A))
	{
		BaseScene* scene = new TitleScene();
		sceneManager->SetNextScene(scene);
	}
}

void ResultScene::Draw()
{
	score->Draw({ 1.0f,1.0f ,1.0f ,1.0f }, 0.0f);
}

void ResultScene::Destroy()
{
	score->Reset();
}