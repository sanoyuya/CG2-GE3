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

	//�V��
	model = std::make_unique<DrawOversight>();
	//model->SetModelBlendMode(BlendMode::Sub);
	modelTex = Model::CreateObjModel("Resources/skydome2");
	model->SetModel(modelTex);
	modelTrans.Initialize();

	//��
	sphere = std::make_unique<DrawOversight>();
	sphereTex = Model::CreateObjModel("Resources/sphere");
	sphere->SetModel(sphereTex);
	sphereTrans.Initialize();

	//��
	plane = std::make_unique<DrawOversight>();
	planeTex = Model::CreateObjModel("Resources/ground");
	plane->SetModel(planeTex);
	planeTrans.Initialize();

	//���̏����l��ݒ�
	spherePos.center = { 0.0f,2.0f,0.0f,1.0f };
	spherePos.radius = 1.0f;//���a

	//���ʂ̏����l��ݒ�
	planePos.normal = { 0.0f,1.0f,0.0f ,0.0f };//�@���x�N�g��
	planePos.destance = 0.0f;//���_(0,0,0)����̋���
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

	modelTrans.TransUpdate(camera.get());//�V��
	planeTrans.TransUpdate(camera.get());

	sphereTime++;
	spherePos.center.y = PhysicsMath::SimpleHarmonicMotion(sphereTime, 2.0f, 120.0f);
	sphereTrans.translation.y = spherePos.center.y;
	sphereTrans.TransUpdate(camera.get());//��

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