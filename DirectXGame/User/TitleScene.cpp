#include "TitleScene.h"
#include"SceneManager.h"
#include<imgui.h>
#include"PhysicsMath.h"

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

	violetSprite2D = std::make_unique<Sprite>();
	violetSprite2DTex= violetSprite2D->LoadTexture("Resources/title_violet.png");
	violetSprite2D->Sprite2DInitialize(violetSprite2DTex);

	pokeSprite3D = std::make_unique<Sprite>();
	pokeSprite3DTex = pokeSprite3D->LoadTexture("Resources/ad5a403d7b1e498d5c5b2a6c609782cc.png");
	pokeSprite3D->Sprite3DInitialize(pokeSprite3DTex);
	pokeSprite3DTrans.Initialize();
	pokeSprite3DTrans.translation.z = 50.0f;

	pokeSprite3D2 = std::make_unique<Sprite>();
	pokeSprite3D2->SetSprite3DBlendMode(BlendMode::Add);
	pokeSprite3D2->Sprite3DInitialize(pokeSprite3DTex);
	pokeSprite3D2Trans.Initialize();
	pokeSprite3D2Trans.translation.x = -20.0f;
	pokeSprite3D2Trans.translation.z = 49.0f;

	pokeSprite3D3 = std::make_unique<Sprite>();
	pokeSprite3D3->SetSprite3DBlendMode(BlendMode::Sub);
	pokeSprite3D3->Sprite3DInitialize(pokeSprite3DTex);
	pokeSprite3D3Trans.Initialize();
	pokeSprite3D3Trans.translation.x = 20.0f;
	pokeSprite3D3Trans.translation.z = 49.0f;

	bgmVolume = 0.025f;
	bgm = audioManager->LoadAudio("Resources/Sound/title.mp3", bgmVolume);
	audioManager->PlayWave(bgm,true);
	bgmFlag = true;
}

void TitleScene::Destroy()
{
	audioManager->StopWave(bgm);
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
		pokeNum++;
		pokeTime = 0;
	}
	uintPokeNowNum = static_cast<uint16_t>(pokeNowNum);

	violetTime++;

	camUpdate();

	audioManager->ChangeVolume(bgm, bgmVolume);

	ImGui::Begin("camera");
	ImGui::SetWindowSize({ 300,100 });
	ImGui::SliderFloat3("position", &cameraPos.x, -50.0f, 50.0f, "%.1f");
	ImGui::End();

	ImGui::Begin("pokemonSprite3D");
	ImGui::SetWindowSize({ 500,250 });
	ImGui::SliderFloat3("position", &pokeSprite3DTrans.translation.x, -50.0f, 50.0f, "%.1f");
	ImGui::SliderFloat3("rotation", &pokeSprite3DTrans.rotation.x, -myMath::AX_PIF/2, myMath::AX_PIF/2, "%.1f");
	ImGui::SliderFloat3("scale", &pokeSprite3DTrans.scale.x, 0.5f, 2.0f, "%.1f");
	ImGui::SliderFloat4("color", &pokeColor.x, 0.0f, 1.0f, "%.1f");
	ImGui::SliderInt("pokeNum", &pokeNowNum, 0, 648);
	ImGui::SliderInt("billboardFlag", &nowBillboard, 0, 4);
	ImGui::Checkbox("flipX", &flipX);
	ImGui::Checkbox("flipY", &flipY);
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

void TitleScene::Draw()
{
	skyDome->DrawModel(&skyDomeTrans);
	pokeSprite3D->DrawAnimationSpriteXY3D(camera.get(), pokeSprite3DTrans, 25, 26, uintPokeNowNum, static_cast<BillboardFlag>(nowBillboard), pokeColor, { 0.5f,0.5 }, flipX, flipY);
	pokeSprite3D2->DrawAnimationSpriteXY3D(camera.get(), pokeSprite3D2Trans, 25, 26, pokeNum);
	pokeSprite3D3->DrawAnimationSpriteXY3D(camera.get(), pokeSprite3D3Trans, 25, 26, pokeNum);
	violetSprite2D->DrawSprite2D({ 290 / 2,635 }, { 0.5f + PhysicsMath::SimpleHarmonicMotion(violetTime,0.5f,300.0f),1.0f ,1.0f ,1.0f }, { 0.5f,0.5f });
}

void TitleScene::camUpdate()
{
	if (input->KeyboardKeepPush(DIK_UP))
	{
		cameraPos.y += 0.2f;
	}
	if (input->KeyboardKeepPush(DIK_DOWN))
	{
		cameraPos.y -= 0.2f;
	}
	if (input->KeyboardKeepPush(DIK_RIGHT))
	{
		cameraPos.x += 0.2f;
	}
	if (input->KeyboardKeepPush(DIK_LEFT))
	{
		cameraPos.x -= 0.2f;
	}

	camera->SetEye(cameraPos);
	camera->SetTarget({ 0.0f,0.0f,50.0f });
	camera->Update(true);
}