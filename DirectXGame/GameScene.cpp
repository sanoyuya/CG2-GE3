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
	tex3 = draw3->LoadTexture("Resources/boss2.png");
	tex4 = draw4->LoadTexture("Resources/ファレグ1_1.jpg");

	draw = std::make_unique<DrawOversight>();
	//draw->SetBlendMode(BlendMode::Add);
	draw->SpriteInitialize();
	draw2 = std::make_unique<DrawOversight>();
	draw2->SpriteInitialize();
	draw3 = std::make_unique<DrawOversight>();
	draw3->SpriteInitialize();
	draw4 = std::make_unique<DrawOversight>();
	draw4->SetBlendMode(BlendMode::Add);
	draw4->SpriteInitialize();

	//titleBGM = audioManager->LoadAudio("Resources/sound/title.mp3");//タイトルシーンBGM読み込み
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
	if (angle > myMath::AX_2PIF)
	{
		angle = 0.0f;
	}

	camera->Update(false);
}

void GameScene::Draw()
{
	if (input->KeyboardTriggerPush(DIK_SPACE))
	{
		//audioManager->StopWave(titleBGM);
	}
	aTime++;
	reimuTime++;
	draw2->DrawSprite(tex2, { 306.0f,255.0f }, { 1,1,1,1 }, { 0.5f,0.5f }, PhysicsMath::SimpleHarmonicMotion(aTime, 1.0f, 60.0f), { 0.5f,0.5f }, false, true);
	draw->DrawSprite(tex, { 640.0f + PhysicsMath::CircularMotion({640.0f,360.0f},100.0f,angle).x, 360.0f + PhysicsMath::CircularMotion({640.0f,360.0f},100.0f,angle).y }, { 1,1,1,1 }, { 1.0f + PhysicsMath::SimpleHarmonicMotion(reimuTime, 1.0f,60.0f),1.0f + PhysicsMath::SimpleHarmonicMotion(reimuTime, 1.0f,60.0f) }, angle);
	flame++;
	if (flame > 2)
	{
		num++;
		flame = 0;
	}
	draw3->DrawAnimationSpriteX(tex3, { 640.0f,360.0f }, 128.0f, num);
	draw4->DrawAnimationSpriteY(tex4, { 640.0f + hoge.x,360.0f + hoge.y }, 900.0f, num, { 1.0f,1.0f,1.0f,1.0f }, { 1.0f,1.0f }, -myMath::AX_PI / 2);
}