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

	camera = std::make_unique<Camera>();
	camera->Initialize(false);

	tex = draw->LoadTexture("Resources/reimu.png");
	tex2 = draw2->LoadTexture("Resources/A.jpg");

	draw = std::make_unique<DrawManager>();
	draw->SpriteInitialize();
	draw2 = std::make_unique<DrawManager>();
	draw2->SpriteInitialize();
}

void GameScene::Update()
{

	if (input->KeyboardKeepPush(DIK_UP))
	{
		hoge.y -= 5;
	}
	if (input->KeyboardKeepPush(DIK_DOWN))
	{
		hoge.y += 5;
	}
	if (input->KeyboardKeepPush(DIK_LEFT))
	{
		hoge.x -= 5;
	}
	if (input->KeyboardKeepPush(DIK_RIGHT))
	{
		hoge.x += 5;
	}

	angle += 0.1f;

	camera->Update(false);
}

void GameScene::Draw()
{
	draw->DrawGraph(tex, camera.get(), { 640.0f + hoge.x,360.0f + hoge.y,0 }, {1,1,1} ,{0, 0, 0});
	draw2->DrawGraph(tex2, camera.get(), {306.0f,255.0f,0});
}