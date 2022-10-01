#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Initialize()
{
	input = Input::GetInstance();
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

	if (input->JoyPadButtonTriggerPush(A))
	{
		hoge++;
	}

	if (input->JoyPadStickTriggerPush(L_UP))
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
