#include "TitleScene.h"
#include"SceneManager.h"
#include<imgui.h>

void TitleScene::Initialize()
{
	input = InputManager::GetInstance();
	audioManager = AudioManager::GetInstance();

	//カメラの生成
	camera = std::make_unique<Camera>();
	camera->Initialize(true);
	cameraPos = { 0.0f,0.0f,-10.0f };

	//天球
	skyDome = std::make_unique<DrawOversight>();
	//model->SetModelBlendMode(BlendMode::Sub);
	skyDomeTex = Model::CreateObjModel("Resources/skydome2");
	skyDome->SetModel(skyDomeTex);
	skyDomeTrans.Initialize();

	pokeSprite3D = std::make_unique<Sprite>();
	pokeSprite3DTex = pokeSprite3D->LoadTexture("Resources/ad5a403d7b1e498d5c5b2a6c609782cc.png");
	pokeSprite3D->Sprite3DInitialize(pokeSprite3DTex);
	pokeSprite3DTrans.Initialize();
	pokeSprite3DTrans.translation.z = 50.0f;
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

	skyDomeTrans.TransUpdate(camera.get());//天球
	pokeSprite3DTrans.TransUpdate(camera.get());//3Dスプライト

	pokeTime++;
	if (pokeTime > 30)
	{
		pokeNowNum++;
		pokeTime = 0;
	}

	camera->Update(true);
}

void TitleScene::Draw()
{
	skyDome->DrawModel(&skyDomeTrans);
	pokeSprite3D->DrawAnimationSpriteXY3D(camera.get(), pokeSprite3DTrans, 25, 26, pokeNowNum);

	/*ImGui::Begin("Exercise");
	ImGui::SetWindowSize({ 500,100 });
	ImGui::SliderFloat3("position", &pokeSprite3DTrans.translation.x, 0.0f, 500.0f, "%.1f");
	ImGui::End();*/
}