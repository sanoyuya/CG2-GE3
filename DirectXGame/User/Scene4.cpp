#include "Scene4.h"
#include"SceneManager.h"
#include<imgui.h>
#include"PhysicsMath.h"

void Scene4::Initialize()
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
	cubeTrans.translation.y = 3.0f;

	//床
	triangle = std::make_unique<DrawOversight>();
	triangleTex = Model::CreateObjModel("Resources/triangle");
	triangle->SetModel(triangleTex);
	triangleTrans.Initialize();

	//レイの初期値を設定
	rayPos.start = { 0.0f,3.0f,0.0f,1.0f };
	rayPos.dir = { 0.0f,-1.0f,0.0f,0.0f };

	//平面の初期値を設定
	trianglePos.p0 = { -1.000000f, 0.000000f, 1.000000f,1.0f };
	trianglePos.p1 = { 1.000000f, 0.000000f, 1.000000f,1.0f };
	trianglePos.p2 = { -1.000000f, 0.000000f, -1.000000f,1.0f };
	trianglePos.normal = { 0.0f,1.0f ,0.0f ,0.0f };
}

void Scene4::Destroy()
{
}

void Scene4::Update()
{
	if (input->KeyboardTriggerPush(DIK_SPACE))
	{
		SceneManager::GetInstance()->ChangeScene("SCENE5");
	}

	CamUpdate();
	Rotation();

	modelTrans.TransUpdate(camera.get());//天球
	triangleTrans.TransUpdate(camera.get());

	rayTime++;
	rayPos.start.x = PhysicsMath::SimpleHarmonicMotion(rayTime, 3.0f, 120.0f);
	rayTrans.translation.x = rayPos.start.x;
	rayTrans.TransUpdate(camera.get());//レイ
	cubeTrans.translation.x = rayPos.start.x;
	cubeTrans.TransUpdate(camera.get());

	if (Collision::RayToTriangle(rayPos, trianglePos))
	{
		color = { 1.0f,0.0f,0.0f,1.0f };
	}
	else
	{
		color = { 1.0f,1.0f,1.0f,1.0f };
	}
}

void Scene4::Draw()
{
	triangle->DrawModel(&triangleTrans);
	model->DrawModel(&modelTrans);
	ray->DrawModel(&rayTrans, color);
	cube->DrawModel(&cubeTrans);
}

void Scene4::Rotation()
{
	rayTrans.rotation.y -= 0.02f;
}

void Scene4::CamUpdate()
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
