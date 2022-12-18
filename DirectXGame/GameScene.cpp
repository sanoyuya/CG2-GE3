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
	cameraPos = { 0.0f,length,length/4 };

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
	cubeTrans.scale = { 25.0f / 2,25.0f / 2 ,25.0f / 2 };
	cubeTrans.Initialize();
}

void GameScene::Update()
{
	CamMove();
	modelTrans.TransUpdate(camera.get());//天球
	cubeTrans.TransUpdate(camera.get());//ステージキューブ
}

void GameScene::Draw()
{
	model->DrawModel(&modelTrans);
	cube->DrawModel(&cubeTrans);
}

void GameScene::Rotation()
{

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