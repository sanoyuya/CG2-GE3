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

	tex = TextureManager::GetInstance()->LoadTexture("Resources/reimu.png");
	tex2= TextureManager::GetInstance()->LoadTexture("Resources/A.jpg");

	sprite = std::make_unique<Sprite>();
	sprite->Initialize();
	sprite2 = std::make_unique<Sprite>();
	sprite2->Initialize();
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

	angle += 0.02f;

	camera->Update(false);
}

void GameScene::Draw()
{
	sprite->Draw(tex, camera.get(), { 640.0f + hoge.x,360.0f + hoge.y,0 });
	sprite2->Draw(tex2, camera.get(), { 306.0f / 2,255.0f / 2,0 }, { 0.5f,0.5f,0.5f });
}

GameScene* GameScene::GetInstance()
{
	static GameScene instance;
	return &instance;
}