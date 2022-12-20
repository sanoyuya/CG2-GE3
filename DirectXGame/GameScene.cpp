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
	cameraPos = { 0.0f,10.0f,-10.0f };

	//天球
	model = std::make_unique<DrawOversight>();
	//model->SetModelBlendMode(BlendMode::Sub);
	modelTex = Model::CreateObjModel("Resources/skydome2");
	model->SetModel(modelTex);
	modelTrans.Initialize();

	//ステージキューブ
	cube= std::make_unique<DrawOversight>();
	cubeTex = Model::CreateObjModel("Resources/cube");
	cube->SetModel(cubeTex);
	cubeTrans.scale = { 25.0f,1.0f ,25.0f };
	cubeTrans.Initialize();

	//球
	sphere= std::make_unique<DrawOversight>();
	sphereTex= Model::CreateObjModel("Resources/sphere");
	sphere->SetModel(sphereTex);
	sphereTrans.Initialize();

	sprite = std::make_unique<Sprite>();
	spriteTex = sprite->LoadTexture("Resources/visual.png");
	sprite->Sprite2DInitialize(spriteTex);
}

void GameScene::Update()
{
	CamMove();
	Rotation();
	modelTrans.TransUpdate(camera.get());//天球
	cubeTrans.TransUpdate(camera.get());//ステージキューブ
	sphereTrans.TransUpdate(camera.get());//球
}

void GameScene::Draw()
{
	model->DrawModel(&modelTrans);
	//cube->DrawModel(&cubeTrans);
	sphere->DrawModel(&sphereTrans);
	//sprite->DrawSprite2D({ 640.0f,360.0f });
}

void GameScene::Rotation()
{
	if (input->KeyboardKeepPush(DIK_A))
	{
		sphereTrans.rotation.y -= 0.02f;
	}
	if (input->KeyboardKeepPush(DIK_D))
	{
		sphereTrans.rotation.y += 0.02f;
	}
}

void GameScene::CamMove()
{
	if (input->KeyboardKeepPush(DIK_UP))
	{
		cameraPos.y += 0.5f;
	}
	if (input->KeyboardKeepPush(DIK_DOWN))
	{
		cameraPos.y -= 0.5f;
	}
	if (input->KeyboardKeepPush(DIK_RIGHT))
	{
		cameraPos.x += 0.05f;
	}
	if (input->KeyboardKeepPush(DIK_LEFT))
	{
		cameraPos.x -= 0.05f;
	}

	camera->SetEye(cameraPos);
	camera->SetTarget({ 0.0f,0.0f ,0.0f });
	camera->Update(true);
}

void GameScene::Reset()
{
	cameraPos = { 0.0f,0.0f,40.0f };
}