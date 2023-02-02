#include"Scene5.h"
#include"SceneManager.h"
#include<imgui.h>
#include"PhysicsMath.h"

void Scene5::Initialize()
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

	//レイの初期値を設定
	rayPos.start = { 0.0f,3.0f,0.0f,1.0f };
	rayPos.dir = { 0.0f,-1.0f,0.0f,0.0f };

	cube = std::make_unique<DrawOversight>();
	cube->SetModel(rayTex);
	cubeTrans.Initialize();
	cubeTrans.translation.y = 3.0f;

	//球
	sphere = std::make_unique<DrawOversight>();
	sphereTex = Model::CreateObjModel("Resources/sphere");
	sphere->SetModel(sphereTex);
	sphereTrans.Initialize();
}

void Scene5::Destroy()
{
}

void Scene5::Update()
{
	if (input->KeyboardTriggerPush(DIK_SPACE))
	{
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}

	CamUpdate();
	Rotation();

	modelTrans.TransUpdate(camera.get());//天球
	sphereTrans.TransUpdate(camera.get());//球

	rayTime++;
	rayPos.start.x = PhysicsMath::SimpleHarmonicMotion(rayTime, 3.0f, 120.0f);
	rayTrans.translation.x = rayPos.start.x;
	rayTrans.TransUpdate(camera.get());//レイ
	cubeTrans.translation.x = rayPos.start.x;
	cubeTrans.TransUpdate(camera.get());

	if (Collision::RayToSphere(rayPos, spherePos))
	{
		color = { 1.0f,0.0f,0.0f,1.0f };
	}
	else
	{
		color = { 1.0f,1.0f,1.0f,1.0f };
	}
}

void Scene5::Draw()
{
	sphere->DrawModel(&sphereTrans);
	model->DrawModel(&modelTrans);
	ray->DrawModel(&rayTrans, color);
	cube->DrawModel(&cubeTrans);
}

void Scene5::Rotation()
{
	rayTrans.rotation.y -= 0.02f;
}

void Scene5::CamUpdate()
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