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

	//“V‹…
	model = std::make_unique<DrawOversight>();
	//model->SetModelBlendMode(BlendMode::Sub);
	modelTex = Model::CreateObjModel("Resources/skydome2");
	model->SetModel(modelTex);
	modelTrans.Initialize();

	object = std::make_unique<DrawOversight>();
	cubeTex = Model::CreateObjModel("Resources/cube");
	objectTex = Model::CreateObjModel("Resources/F-35E");
	object->SetModel(cubeTex);
	objectTrans.Initialize();
	objectTrans.translation.x = -2.0f;
	objectColor = { 1.0f,1.0f ,1.0f ,1.0f };

	object2 = std::make_unique<DrawOversight>();
	object2->SetModel(cubeTex);
	object2->SetModelBlendMode(BlendMode::Add);
	objectTrans2.Initialize();
	objectTrans2.translation.y = 3.0f;

	//‹…
	sphere= std::make_unique<DrawOversight>();
	sphereTex= Model::CreateObjModel("Resources/sphere");
	sphere->SetModel(sphereTex);
	sphereTrans.Initialize();
	sphereTrans.translation.x = 2.0f;

	bgmVolume = 0.025f;
	bgm = audioManager->LoadAudio("Resources/Sound/1~10.mp3", bgmVolume);
	audioManager->PlayWave(bgm, true);
	bgmFlag = true;
}

void GameScene::Destroy()
{
	audioManager->StopWave(bgm);
}

void GameScene::Update()
{
	if (input->KeyboardTriggerPush(DIK_SPACE))
	{
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}

	CamMove();
	Rotation();

	modelTrans.TransUpdate(camera.get());//“V‹…
	objectTrans.TransUpdate(camera.get());
	objectTrans2.TransUpdate(camera.get());
	sphereTrans.TransUpdate(camera.get());//‹…

	if (input->KeyboardTriggerPush(DIK_H) || input->MouseTriggerPush(RIGHT) || input->ControllerButtonTriggerPush(A))
	{
		if (texFlag == false)
		{
			object->SetModel(objectTex);
			object2->SetModel(objectTex);
			texFlag = true;
		}
		else
		{
			object->SetModel(cubeTex);
			object2->SetModel(cubeTex);
			texFlag = false;
		}
	}

	ImGui::Begin("object");
	ImGui::SetWindowSize({ 500,150 });
	ImGui::SliderFloat3("position", &objectTrans.translation.x, -50.0f, 50.0f, "%.1f");
	ImGui::SliderFloat3("rotation", &objectTrans.rotation.x, -myMath::AX_PIF / 2, myMath::AX_PIF / 2, "%.1f");
	ImGui::SliderFloat3("scale", &objectTrans.scale.x, 0.5f, 2.0f, "%.1f");
	ImGui::SliderFloat4("color", &objectColor.x, 0.0f, 1.0f, "%.1f");
	if (ImGui::Button("modelChange"))
	{
		if (texFlag == false)
		{
			object->SetModel(objectTex);
			object2->SetModel(objectTex);
			texFlag = true;
		}
		else
		{
			object->SetModel(cubeTex);
			object2->SetModel(objectTex);
			texFlag = false;
		}
	}
	ImGui::End();

	ImGui::Begin("camera");
	ImGui::SetWindowSize({ 300,100 });
	ImGui::SliderFloat3("position", &cameraPos.x, -25.0f, 25.0f, "%.1f");
	ImGui::End();

	ImGui::Begin("audio");
	ImGui::SetWindowSize({ 200,80 });
	ImGui::SliderFloat("volume", &bgmVolume, 0.0f, 1.0f, "%.3f");
	if (ImGui::Button("soundPlay"))
	{
		if (bgmFlag == true)
		{
			audioManager->StopWave(bgm);
			bgmFlag = false;
		}
		else
		{
			audioManager->PlayWave(bgm, true);
			bgmFlag = true;
		}
	}
	ImGui::End();
}

void GameScene::Draw()
{
	model->DrawModel(&modelTrans);

	time++;
	object->DrawModel(&objectTrans, objectColor);
	object2->DrawModel(&objectTrans2);
	sphere->DrawModel(&sphereTrans);
	
}

void GameScene::Rotation()
{
	objectTrans2.rotation.y += 0.02f;
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

void GameScene::Reset()
{
	cameraPos = { 0.0f,0.0f,-10.0f };
}