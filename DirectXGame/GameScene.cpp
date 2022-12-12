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
	camera->Initialize(true);

	/*tex = draw->LoadTexture("Resources/visual (1).png");
	tex2 = draw2->LoadTexture("Resources/visual.png");
	tex3 = draw3->LoadTexture("Resources/boss2.png");
	tex4 = draw4->LoadTexture("Resources/GodQueenProject/ru/1_1.jpg");*/
	violetTex = draw->LoadTexture("Resources/title_violet.png");
	pokeTex = draw->LoadTexture("Resources/ad5a403d7b1e498d5c5b2a6c609782cc.png");

	//draw = std::make_unique<DrawOversight>();
	////draw->SetBlendMode(BlendMode::Add);
	//draw->SpriteInitialize(tex);
	//draw2 = std::make_unique<DrawOversight>();
	//draw2->SpriteInitialize(tex2);
	//draw3 = std::make_unique<DrawOversight>();
	//draw3->SpriteInitialize(tex3);
	//draw4 = std::make_unique<DrawOversight>();
	////draw4->SetBlendMode(BlendMode::Add);
	//draw4->SpriteInitialize(tex4);
	violet = std::make_unique<DrawOversight>();
	violet->SpriteInitialize(violetTex);
	poke = std::make_unique<DrawOversight>();
	poke->SpriteInitialize(pokeTex);

	//titleBGM = audioManager->LoadAudio("Resources/sound/title.mp3");//�^�C�g���V�[��BGM�ǂݍ���
	//audioManager->PlayWave(titleBGM, true);//BGM��Đ�

	model = std::make_unique<DrawOversight>();
	modelTex = Model::CreateObjModel("Resources/skydome");
	model->SetModel(modelTex);
	modelTrans.Initialize();

	f = std::make_unique<DrawOversight>();
	fTex = Model::CreateObjModel("Resources/F-15");
	f->SetModel(fTex);
	fTrans.Initialize();
}

void GameScene::Update()
{
	if (input->KeyboardKeepPush(DIK_W))
	{
		cameraPos.z -= 5;
	}
	if (input->KeyboardKeepPush(DIK_A))
	{
		cameraPos.x += 5;
	}
	if (input->KeyboardKeepPush(DIK_S))
	{
		cameraPos.z += 5;
	}
	if (input->KeyboardKeepPush(DIK_D))
	{
		cameraPos.x -= 5;
	}

	angle += 0.1f;
	if (angle > myMath::AX_2PIF)
	{
		angle = 0.0f;
	}

	camera->SetEye(cameraPos);
	camera->SetTarget({ cameraPos.x,cameraPos.y,cameraPos.z - 5.0f });
	camera->Update(true);

	mTime++;
	modelTrans.translation.x = PhysicsMath::CircularMotion({ 0,0 }, 20.0f, angle).x;
	modelTrans.translation.y = PhysicsMath::CircularMotion({ 0,0 }, 20.0f, angle).y;
	modelTrans.TransUpdate(camera.get());
	fTrans.TransUpdate(camera.get());
}

void GameScene::Draw()
{
	model->Draw(&modelTrans);
	f->Draw(&fTrans);

	violet->DrawSprite({ 1280 - 290 / 2,720 - 170 / 2 }, { 1.0f,1.0f,1.0f,1.0f }, { 0.5f,0.5f });

	pokeFlame++;
	if (pokeFlame > 10)
	{
		pokeNum++;
		pokeFlame = 0;
	}
	poke->DrawAnimationSpriteXY({ 36,32 }, 25, 26, pokeNum, { 1.0f,1.0f,1.0f,1.0f }, { 2.5f,2.5f });
}