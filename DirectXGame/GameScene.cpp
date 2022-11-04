#include "GameScene.h"
#include"PhysicsMath.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Initialize()
{
	input = InputManager::GetInstance();
	audioManager = audioManager->GetInstance();

	camera = std::make_unique<Camera>();
	camera->Initialize(false);

	tex = draw->LoadTexture("Resources/reimu.png");
	tex2 = draw2->LoadTexture("Resources/A.jpg");

	draw = std::make_unique<DrawManager>();
	//draw->SetBlendMode(BlendMode::Add);
	draw->SpriteInitialize();
	draw2 = std::make_unique<DrawManager>();
	draw2->SpriteInitialize();

	titleBGM = audioManager->LoadAudio("Resources/sound/title.mp3");//タイトルシーンBGM読み込み
	//audioManager->PlayWave(titleBGM, true);//BGMを再生
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
	if (input->KeyboardTriggerPush(DIK_SPACE))
	{
		audioManager->StopWave(titleBGM);
	}
	draw2->DrawSprite(tex2, {306.0f,255.0f});
	draw->DrawSprite(tex, { 640.0f + hoge.x + PhysicsMath::CircularMotion({640.0f,360.0f},100,angle).x,hoge.y + 360.0f + PhysicsMath::CircularMotion({640.0f,360.0f},100,angle).y }, {1,1,1,1});
}