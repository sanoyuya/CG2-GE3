#include "TitleScene.h"
#include"SceneManager.h"
#include<imgui.h>
#include"PhysicsMath.h"

void TitleScene::Initialize()
{
	input = InputManager::GetInstance();
	audioManager = AudioManager::GetInstance();

	camera = std::make_unique<Camera>();
	camera->Initialize(true);
	cameraPos = { 0.0f,3.0f,-10.0f };

	//天球
	model = std::make_unique<DrawOversight>();
	//model->SetModelBlendMode(BlendMode::Sub);
	modelTex = Model::CreateObjModel("Resources/skydome2");
	model->SetModel(modelTex);
	modelTrans.Initialize();

	//球
	sphere = std::make_unique<DrawOversight>();
	sphereTex = Model::CreateObjModel("Resources/sphere");
	sphere->SetModel(sphereTex);
	sphereTrans.Initialize();

	//床
	plane = std::make_unique<DrawOversight>();
	planeTex = Model::CreateObjModel("Resources/ground");
	plane->SetModel(planeTex);
	planeTrans.Initialize();

	//球の初期値を設定
	spherePos.center = { 0.0f,2.0f,0.0f,1.0f };
	spherePos.radius = 1.0f;//半径

	//平面の初期値を設定
	planePos.normal = { 0.0f,1.0f,0.0f ,0.0f };//法線ベクトル
	planePos.destance = 0.0f;//原点(0,0,0)からの距離
}

void TitleScene::Rotation()
{
	sphereTrans.rotation.y -= 0.02f;
}

void TitleScene::Destroy()
{
}

void TitleScene::Update()
{
	if (input->KeyboardTriggerPush(DIK_SPACE))
	{
		SceneManager::GetInstance()->ChangeScene("GAME");
	}

	camUpdate();
	Rotation();

	modelTrans.TransUpdate(camera.get());//天球
	planeTrans.TransUpdate(camera.get());

	sphereTime++;
	spherePos.center.y = PhysicsMath::SimpleHarmonicMotion(sphereTime, 2.0f, 120.0f);
	sphereTrans.translation.y = spherePos.center.y;
	sphereTrans.TransUpdate(camera.get());//球

	if (Collision::SphereToPlane(spherePos, planePos))
	{
		color = { 1.0f,0.0f,0.0f,1.0f };
	}
	else
	{
		color = { 1.0f,1.0f,1.0f,1.0f };
	}

	ImGui::Begin("test");
	ImGui::Text("pos:%f", sphereTrans.translation.y);
	ImGui::End();
}

void TitleScene::Draw()
{
	plane->DrawModel(&planeTrans);
	model->DrawModel(&modelTrans);
	sphere->DrawModel(&sphereTrans, color);
}

void TitleScene::camUpdate()
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