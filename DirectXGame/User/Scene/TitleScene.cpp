#include "TitleScene.h"
#include"SceneManager.h"
#include<imgui.h>
#include"PhysicsMath.h"
#include"PostEffect.h"
#include"EasingFunction.h"
#include"SceneChangeAnimation.h"

void TitleScene::Initialize()
{
	input_ = InputManager::GetInstance();
	audioManager_ = AudioManager::GetInstance();

	camera_ = std::make_unique<Camera>();
	camera_->Initialize(true);
	camera_->SetEye({ 0,0,-50 });

	lightManager_.reset(lightManager_->Create());
	Model::SetLight(lightManager_.get());

	title_ = std::make_unique<Sprite>();
	titleTex_ = title_->LoadTexture("Resources/gameLogo.png");
	title_->Sprite2DInitialize(titleTex_);

	//天球
	skyDome_ = std::make_unique<Model>();
	skyDomeTex_ = Model::CreateObjModel("Resources/skydome2");
	skyDome_->SetModel(skyDomeTex_);
	skyDomeTrans_.Initialize();

	bgm_ = audioManager_->LoadAudio("Resources/Sound/title.mp3",0.1f);
	audioManager_->PlayWave(bgm_);
}

void TitleScene::Destroy()
{
	audioManager_->StopWave(bgm_);
}

void TitleScene::Update()
{
	if (input_->KeyboardTriggerPush(DIK_SPACE)||input_->ControllerButtonTriggerPush(A))
	{
		SceneChangeAnimation::GetInstance()->SetAnimationFlag(true);
	}
	SceneChangeAnimation::GetInstance()->Update();
	SceneChangeAnimation::GetInstance()->ChangeAfter();
	SceneChangeAnimation::GetInstance()->Change("GAME");

	skyDomeTrans_.TransUpdate(camera_.get());//天球

	time_++;
	position_.y = 360.0f+PhysicsMath::SimpleHarmonicMotion(time_);

	lightManager_->Update();

	//ポイントライト
	lightManager_->SetPointLightActive(0, true);
	lightManager_->SetPointLightPos(0, { 0.0f,0.0f ,0.0f });
	lightManager_->SetPointLightColor(0, { 1.0f,1.0f,1.0f });
	lightManager_->SetPointLightAtten(0, { 0.3f,0.1f,0.1f });
}

void TitleScene::Draw()
{
	//skyDome_->DrawModel(&skyDomeTrans_);
	title_->DrawSprite2D({ position_ });
	SceneChangeAnimation::GetInstance()->Draw();
}

void TitleScene::camUpdate()
{
	if (input_->KeyboardKeepPush(DIK_UP))
	{
		cameraPos_.y += 0.05f;
	}
	if (input_->KeyboardKeepPush(DIK_DOWN))
	{
		cameraPos_.y -= 0.05f;
	}
	if (input_->KeyboardKeepPush(DIK_RIGHT))
	{
		cameraPos_.x += 0.05f;
	}
	if (input_->KeyboardKeepPush(DIK_LEFT))
	{
		cameraPos_.x -= 0.05f;
	}

	camera_->SetEye(cameraPos_);
	camera_->SetTarget({ 0.0f,0.0f ,0.0f });
	camera_->Update(true);
}