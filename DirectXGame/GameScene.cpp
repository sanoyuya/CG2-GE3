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
	
	kami = std::make_unique<DrawOversight>();
	kamiTex = kami->LoadTexture("Resources/GodQueenProject/faleg/1_1.jpg");
	kami->SpriteInitialize(kamiTex);

	violet = std::make_unique<DrawOversight>();
	//violet->SetSpriteBlendMode(BlendMode::Add);
	violetTex = violet->LoadTexture("Resources/title_violet.png");
	violet->SpriteInitialize(violetTex);

	poke = std::make_unique<DrawOversight>();
	pokeTex = poke->LoadTexture("Resources/ad5a403d7b1e498d5c5b2a6c609782cc.png");
	poke->SpriteInitialize(pokeTex);

	model = std::make_unique<DrawOversight>();
	modelTex = Model::CreateObjModel("Resources/skydome2");
	model->SetModel(modelTex);
	modelTrans.Initialize();

	fModel = std::make_unique<DrawOversight>();
	//fModel->SetModelBlendMode(BlendMode::Alpha);
	fModelTex = Model::CreateObjModel("Resources/F-15");
	fModel2Tex = Model::CreateObjModel("Resources/F-35E");
	fModel->SetModel(fModelTex);
	fModelTrans.Initialize();
}

void GameScene::Update()
{
	if (input->KeyboardKeepPush(DIK_W))
	{
		cameraPos.z -= 0.5f;
	}
	if (input->KeyboardKeepPush(DIK_A))
	{
		cameraPos.x += 0.5f;
	}
	if (input->KeyboardKeepPush(DIK_S))
	{
		cameraPos.z += 0.5f;
	}
	if (input->KeyboardKeepPush(DIK_D))
	{
		cameraPos.x -= 0.5f;
	}

	if (input->KeyboardKeepPush(DIK_1))
	{
		fModel->SetModel(fModelTex);
		//model->SetModel(modelTex);
	}
	else if (input->KeyboardKeepPush(DIK_2))
	{
		fModel->SetModel(fModel2Tex);
		//model->SetModel(f2Tex);
	}

	camera->SetEye(cameraPos);
	camera->SetTarget({ cameraPos.x,cameraPos.y,-1.0f });
	camera->Update(true);

	angle += 0.01f;
	if (angle > myMath::AX_2PIF)
	{
		angle = 0.0f;
	}

	fModelTrans.translation.x = PhysicsMath::CircularMotion({ 0,0 }, 20.0f, angle).x;
	fModelTrans.translation.y = PhysicsMath::CircularMotion({ 0,0 }, 20.0f, angle).y;

	modelTrans.TransUpdate(camera.get());
	fModelTrans.TransUpdate(camera.get());
}

void GameScene::Draw()
{
	model->DrawModel(&modelTrans);
	fModel->DrawModel(&fModelTrans);

	kamiTime++;
	if (kamiTime > 2)
	{
		kamiNum++;
		kamiTime = 0;
	}

	//kami->DrawAnimationSpriteY({ 640 + hoge.x,360 + hoge.y }, 16, kamiNum, { 1.0f,1.0f ,1.0f ,1.0f }, { 1.0f,1.0f }, -myMath::AX_PI / 2);

	flame++;
	if (flame > 10)
	{
		pokeNum++;
		flame = 0;
	}

	violet->DrawSprite({ 1280 - 290 / 2,720 - 170 / 2 }, { 1.0f,1.0f,1.0f,1.0f }, { 0.5f,0.5f });
	poke->DrawAnimationSpriteXY({ 48,32 }, 25, 26, pokeNum, { 1.0f,1.0f,1.0f,1.0f }, { 2.5f,2.5f });
}