#include "GameScene.h"
#include"SceneManager.h"
#include"PhysicsMath.h"
#include<imgui.h>

void GameScene::Initialize()
{
	input = InputManager::GetInstance();
	audioManager = AudioManager::GetInstance();

	camera = std::make_unique<Camera>();
	camera->Initialize(true);
	cameraPos = { 0.0f,0.0f,-10.0f };

	lightManager.reset(lightManager->Create());
	Model::SetLight(lightManager.get());

	//天球
	model = std::make_unique<DrawOversight>();
	model->SetShaderMode(ShaderMode::Phong);
	//model->SetModelBlendMode(BlendMode::Sub);
	modelTex = Model::CreateObjModel("Resources/skydome");
	model->SetModel(modelTex);
	modelTrans.Initialize();

	//球
	sphere = std::make_unique<DrawOversight>();
	sphere->SetShaderMode(ShaderMode::Phong);
	sphereTex = Model::CreateObjModel("Resources/sphere",true);
	sphere->SetModel(sphereTex);
	sphereTrans.Initialize();

	//球の初期値を設定
	spherePos.center = { 0.0f,-1.0f,0.0f,1.0f };
	spherePos.radius = 1.0f;//半径
	sphereTrans.translation.y = spherePos.center.y;

	//床
	triangle = std::make_unique<DrawOversight>();
	triangleTex = Model::CreateObjModel("Resources/triangle");
	triangle->SetModel(triangleTex);
	triangleTrans.Initialize();
	triangleTrans.rotation.x = -myMath::AX_PIF/2;

	//平面の初期値を設定
	trianglePos.p0 = { -1.000000f, 1.000000f, 0.000000f,1.0f };
	trianglePos.p1 = { -1.000000f, -1.000000f, 0.000000f,1.0f };
	trianglePos.p2 = { 1.000000f, 1.000000f, 0.000000f,1.0f };
	trianglePos.normal = { 0.0f,0.0f ,0.0f ,0.0f };
}

void GameScene::Destroy()
{
}

void GameScene::Update()
{
	if (input->KeyboardTriggerPush(DIK_SPACE))
	{
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}

	CamMove();
	Rotation();

	lightManager->Update();

	//ポイントライト
	lightManager->SetPointLightActive(0, true);
	lightManager->SetPointLightPos(0, { 0.0f,0.0f ,-2.0f });
	lightManager->SetPointLightColor(0, { 1.0f,1.0f ,1.0f });
	lightManager->SetPointLightAtten(0, { 0.3f,0.1f,0.1f });

	modelTrans.TransUpdate(camera.get());//天球
	triangleTrans.TransUpdate(camera.get());

	sphereTime++;
	spherePos.center.x = PhysicsMath::SimpleHarmonicMotion(sphereTime, 3.0f, 120.0f);
	sphereTrans.translation.x = spherePos.center.x;
	sphereTrans.TransUpdate(camera.get());//球

	if (Collision::SphereToTriangle(spherePos, trianglePos))
	{
		color = { 1.0f,0.0f,0.0f,1.0f };
	}
	else
	{
		color = { 1.0f,1.0f,1.0f,1.0f };
	}
}

void GameScene::Draw()
{
	triangle->DrawModel(&triangleTrans);
	model->DrawModel(&modelTrans);
	sphere->DrawModel(&sphereTrans);
}

void GameScene::Rotation()
{
	sphereTrans.rotation.y -= 0.02f;
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