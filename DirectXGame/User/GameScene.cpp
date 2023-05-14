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
	lightPos = { 0.0f,0.0f,-2.0f };
	lightColor = { 1.0f,1.0f ,1.0f };
	lightAtten = { 0.3f,0.1f,0.1f };

	//天球
	model = std::make_unique<Model>();
	//model->SetModelBlendMode(BlendMode::Sub);
	modelTex = Model::CreateObjModel("Resources/skydome");
	model->SetModel(modelTex);
	modelTrans.Initialize();

	sphereTex = Model::CreateObjModel("Resources/sphere", true);
	sphere2Tex = Model::CreateObjModel("Resources/sphere2",true);
	
	//左側の球
	sphere = std::make_unique<Model>();
	sphere->SetShaderMode(ShaderMode::Phong);
	sphere->SetModel(sphereTex);
	sphereTrans.Initialize();
	sphereTrans.translation.x = -2.0f;

	//右側の球
	sphere2 = std::make_unique<Model>();
	sphere2->SetShaderMode(ShaderMode::Toon);
	sphere2->SetModel(sphereTex);
	sphere2Trans.Initialize();
	sphere2Trans.translation.x = 2.0f;
}

void GameScene::Destroy()
{
}

void GameScene::Update()
{
	/*if (input->KeyboardTriggerPush(DIK_SPACE))
	{
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}*/

	CamMove();
	Rotation();

	lightManager->Update();

	//ポイントライト
	lightManager->SetPointLightActive(0, true);
	lightManager->SetPointLightPos(0, lightPos);
	lightManager->SetPointLightColor(0, lightColor);
	lightManager->SetPointLightAtten(0, lightAtten);

	modelTrans.TransUpdate(camera.get());//天球
	sphereTrans.TransUpdate(camera.get());//球
	sphere2Trans.TransUpdate(camera.get());

	ImGuiUpdate();
}

void GameScene::Draw()
{
	sphere2->DrawModel(&sphere2Trans, color);
	model->DrawModel(&modelTrans);
	sphere->DrawModel(&sphereTrans, color);
}

void GameScene::Rotation()
{
	sphereTrans.rotation.y -= 0.02f;
	sphere2Trans.rotation.y -= 0.02f;
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

void GameScene::ImGuiUpdate()
{
	ImGui::Begin("sphere");
	ImGui::ColorEdit4("color", &color.x);
	if(ImGui::Button("texFlag"))
	{
		if (texFlag == false)
		{
			sphere->SetModel(sphereTex);
			sphere2->SetModel(sphereTex);
			texFlag = true;
		}
		else
		{
			sphere->SetModel(sphere2Tex);
			sphere2->SetModel(sphere2Tex);
			texFlag = false;
		}
	}
	ImGui::End();
	ImGui::Begin("light");
	ImGui::SliderFloat3("position", &lightPos.x, -10.0f, 10.0f);
	ImGui::ColorEdit3("color", &lightColor.x);
	ImGui::SliderFloat3("ateen", &lightAtten.x, 0.0f, 1.0f);
	ImGui::End();
}
