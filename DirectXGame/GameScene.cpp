#include "GameScene.h"
#include"PhysicsMath.h"
#include<imgui.h>

void GameScene::Destroy()
{
}

void GameScene::Initialize()
{
	input = InputManager::GetInstance();
	audioManager = audioManager->GetInstance();

	camera = std::make_unique<Camera>();
	camera->Initialize(true);
	cameraPos = { 0.0f,0.0f,-10.0f };

	//天球
	model = std::make_unique<DrawOversight>();
	//model->SetModelBlendMode(BlendMode::Sub);
	modelTex = Model::CreateObjModel("Resources/skydome2");
	model->SetModel(modelTex);
	modelTrans.Initialize();

	//ステージキューブ
	cube = std::make_unique<DrawOversight>();
	cubeTex = Model::CreateObjModel("Resources/cube");
	cube->SetModel(cubeTex);
	cubeTrans.Initialize();
	cubeTrans.translation.x = -2.0f;

	//球
	sphere= std::make_unique<DrawOversight>();
	sphereTex= Model::CreateObjModel("Resources/sphere");
	sphere->SetModel(sphereTex);
	sphereTrans.Initialize();
	sphereTrans.translation.x = 2.0f;

	sprite = std::make_unique<Sprite>();
	spriteTex = sprite->LoadTexture("Resources/GodQueenProject/ru/1_1.jpg");
	sprite->Sprite2DInitialize(spriteTex);

	sprite3D= std::make_unique<Sprite>();
	sprite3DTex=sprite->LoadTexture("Resources/GodQueenProject/faleg/1_1.jpg");
	sprite3D->Sprite3DInitialize(sprite3DTex);
	sprite3DTrans.Initialize();
	sprite3DTrans.rotation.z = myMath::AX_PIF / 2;
	sprite3DTrans.scale = { 1.0f / 100,1.0f / 100 ,1.0f / 100 };
	sprite3DTrans.translation.z = 2.0f;
}

void GameScene::Update()
{
	CamMove();
	Rotation();
	modelTrans.TransUpdate(camera.get());//天球
	cubeTrans.TransUpdate(camera.get());//ステージキューブ
	sphereTrans.TransUpdate(camera.get());//球

	ImGui::SliderFloat2("sprite2D", &sprite2DPos.x, 100.0f, 300, "%f", 1.0f);
	ImGui::SetWindowSize({ 400,300 });
	ImGui::SliderFloat3("sprite3D", &sprite3DTrans.translation.x, -5.0f, 5.0f);
}

void GameScene::Draw()
{
	model->DrawModel(&modelTrans);

	kamiTime++;
	if (kamiTime > 1)
	{
		animationNum++;
		kamiTime = 0;
	}
	sprite3D->DrawAnimationSpriteY3D(camera.get(), sprite3DTrans,16,animationNum);
	sprite->DrawAnimationSpriteY2D(sprite2DPos, 16, animationNum, { 1.0f,1.0f ,1.0f ,1.0f }, { 1.0f / 3,1.0f / 3 }, -myMath::AX_PIF / 2);

	time++;
	cube->DrawModel(&cubeTrans, { PhysicsMath::SimpleHarmonicMotion(time, 0.25f, 180.0f) + 0.25f,0.8f,0.8f,0.75f });
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
		cameraPos.y += 0.05f;
	}
	if (input->KeyboardKeepPush(DIK_DOWN))
	{
		cameraPos.y -= 0.05f;
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
	cameraPos = { 0.0f,0.0f,-10.0f };
}