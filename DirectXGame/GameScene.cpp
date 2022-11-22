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

	tex = draw->LoadTexture("Resources/visual (1).png");
	tex2 = draw2->LoadTexture("Resources/visual.png");
	tex3 = draw3->LoadTexture("Resources/boss2.png");
	tex4 = draw4->LoadTexture("Resources/GodQueenProject/faleg/1_1.jpg");
	violetTex = draw->LoadTexture("Resources/title_violet.png");
	pokeTex = draw->LoadTexture("Resources/ad5a403d7b1e498d5c5b2a6c609782cc.png");

	draw = std::make_unique<DrawOversight>();
	//draw->SetBlendMode(BlendMode::Add);
	draw->SpriteInitialize();
	draw2 = std::make_unique<DrawOversight>();
	draw2->SpriteInitialize();
	draw3 = std::make_unique<DrawOversight>();
	draw3->SpriteInitialize();
	draw4 = std::make_unique<DrawOversight>();
	//draw4->SetBlendMode(BlendMode::Add);
	draw4->SpriteInitialize();
	violet = std::make_unique<DrawOversight>();
	violet->SpriteInitialize();
	poke = std::make_unique<DrawOversight>();
	poke->SpriteInitialize();

	//titleBGM = audioManager->LoadAudio("Resources/sound/title.mp3");//�^�C�g���V�[��BGM�ǂݍ���
	//audioManager->PlayWave(titleBGM, true);//BGM��Đ�
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
	draw2->DrawSprite(tex2, { 306.0f,255.0f }, { 1,1,1,1 }, { 0.5f,0.5f }, PhysicsMath::SimpleHarmonicMotion(aTime, 1.0f, 60.0f), { 0.5f,0.5f }, false, false);
	draw->DrawSprite(tex, { 640.0f + PhysicsMath::CircularMotion({640.0f,360.0f},100.0f,angle).x, 360.0f + PhysicsMath::CircularMotion({640.0f,360.0f},100.0f,angle).y }, { 1,1,1,1 }, { 1.0f + PhysicsMath::SimpleHarmonicMotion(reimuTime, 1.0f,60.0f),1.0f + PhysicsMath::SimpleHarmonicMotion(reimuTime, 1.0f,60.0f) }, angle);
	flame++;
	if (flame > 2)
	{
		num++;
		flame = 0;
	}
	draw3->DrawAnimationSpriteX(tex3, { 640.0f,360.0f }, 19, num);
	draw4->DrawAnimationSpriteY(tex4, { 640.0f + hoge.x,360.0f + hoge.y }, 16, num, { 1.0f,1.0f,1.0f,1.0f }, { 1.0f,1.0f }, -myMath::AX_PI / 2);
	violet->DrawSprite(violetTex, { 1280 - 290 / 2,720 - 170 / 2 }, { 1.0f,1.0f,1.0f,1.0f }, { 0.5f,0.5f });

	pokeFlame++;
	if (pokeFlame > 10)
	{
		pokeNum++;
		pokeFlame = 0;
	}
	poke->DrawAnimationSpriteXY(pokeTex, { 640 + hoge.x,360 + hoge.y }, 25, 26, pokeNum, { 1.0f,1.0f,1.0f,1.0f }, { 2.5f,2.5f });
}