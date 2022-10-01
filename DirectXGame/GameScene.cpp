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
}

void GameScene::Draw()
{
}

GameScene* GameScene::GetInstance()
{
	static GameScene instance;
	return &instance;
}
