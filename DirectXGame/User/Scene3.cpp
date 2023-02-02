#include "Scene3.h"
#include"SceneManager.h"
#include<imgui.h>
#include"PhysicsMath.h"

void Scene3::Initialize()
{
	input = InputManager::GetInstance();

	camera = std::make_unique<Camera>();
	camera->Initialize(true);
	cameraPos = { 0.0f,3.0f,-10.0f };

	//天球
	model = std::make_unique<DrawOversight>();
	//model->SetModelBlendMode(BlendMode::Sub);
	modelTex = Model::CreateObjModel("Resources/skydome2");
	model->SetModel(modelTex);
	modelTrans.Initialize();

	//レイ
	ray = std::make_unique<DrawOversight>();
	rayTex = Model::CreateObjModel("Resources/cube");
	ray->SetModel(rayTex);
	rayTrans.Initialize();
	rayTrans.scale = { 0.1f,3.0f,0.1f };

	cube = std::make_unique<DrawOversight>();
	cube->SetModel(rayTex);
	cubeTrans.Initialize();

	//床
	plane = std::make_unique<DrawOversight>();
	planeTex = Model::CreateObjModel("Resources/ground");
	plane->SetModel(planeTex);
	planeTrans.Initialize();

	//レイの初期値を設定
	rayPos.start = { 0.0f,1.0f,0.0f,1.0f };
	rayPos.dir = { 0.0f,1.0f,0.0f,0.0f };

	//平面の初期値を設定
	planePos.normal = { 0.0f,-1.0f,0.0f ,0.0f };//法線ベクトル
	planePos.destance = 0.0f;//原点(0,0,0)からの距離
}

void Scene3::Destroy()
{
}

void Scene3::Update()
{
	if (input->KeyboardTriggerPush(DIK_SPACE))
	{
		SceneManager::GetInstance()->ChangeScene("SCENE4");
	}

	CamUpdate();
	Rotation();

	modelTrans.TransUpdate(camera.get());//天球
	planeTrans.TransUpdate(camera.get());

	rayTime++;
	rayTrans.translation.y = 3.0+PhysicsMath::SimpleHarmonicMotion(rayTime, 3.0f, 120.0f);
	rayPos.start.y = PhysicsMath::SimpleHarmonicMotion(rayTime, 3.0f, 120.0f);
	rayTrans.TransUpdate(camera.get());//レイ
	cubeTrans.translation.y = rayPos.start.y;
	cubeTrans.TransUpdate(camera.get());

	if (Collision::RayToPlane(rayPos, planePos))
	{
		color = { 1.0f,0.0f,0.0f,1.0f };
	}
	else
	{
		color = { 1.0f,1.0f,1.0f,1.0f };
	}
}

void Scene3::Draw()
{
	plane->DrawModel(&planeTrans);
	model->DrawModel(&modelTrans);
	ray->DrawModel(&rayTrans, color);
	cube->DrawModel(&cubeTrans);
}

void Scene3::Rotation()
{
	rayTrans.rotation.y -= 0.02f;
}

void Scene3::CamUpdate()
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
