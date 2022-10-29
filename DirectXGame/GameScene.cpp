#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Initialize()
{
	input = InputManager::GetInstance();
}

void GameScene::Update()
{
	if (input->KeyboardTriggerPush(DIK_0))
	{
		hoge++;
	}

	if (input->MouseTriggerPush(LEFT))
	{
		hoge++;
	}

	if (input->ControllerButtonTriggerPush(A))
	{
		hoge++;
	}

	if (input->ControllerStickTriggerPush(L_UP))
	{
		hoge++;
	}
}

void GameScene::Draw()
{

}

GameScene* GameScene::GetInstance()
{
	static GameScene instance;
	return &instance;
}