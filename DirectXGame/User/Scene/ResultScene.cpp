#include "ResultScene.h"
#include"SceneChangeAnimation.h"
#include"PhysicsMath.h"

void ResultScene::Initialize()
{
	input_ = InputManager::GetInstance();
	audioManager_ = AudioManager::GetInstance();

	camera_ = std::make_unique<Camera>();
	camera_->Initialize(true);
	cameraPos_ = { 0.0f,0.0f,0.0f };

	lightManager_.reset(lightManager_->Create());
	Model::SetLight(lightManager_.get());

	result_ = std::make_unique<Sprite>();
	resultTex_ = result_->LoadTexture("Resources/defaultResult.png");
	result_->Sprite2DInitialize(resultTex_);

	//天球
	skyDome_ = std::make_unique<Model>();
	skyDomeTex_ = Model::CreateObjModel("Resources/skydome2");
	skyDome_->SetModel(skyDomeTex_);
	skyDomeTrans_.Initialize();

	bgm_ = audioManager_->LoadAudio("Resources/Sound/title.mp3", 0.1f);
	audioManager_->PlayWave(bgm_);
}

void ResultScene::Destroy()
{
	audioManager_->StopWave(bgm_);
}

void ResultScene::Update()
{
	if (input_->KeyboardTriggerPush(DIK_SPACE))
	{
		SceneChangeAnimation::GetInstance()->SetAnimationFlag(true);
	}
	SceneChangeAnimation::GetInstance()->Change("TITLE");

	camUpdate();

	if (time_ >= 180.0f)
	{
		time_ = 0.0f;
	}
	time_++;

	if (input_->KeyboardTriggerPush(DIK_R))
	{
		time_ = 0.0f;
	}

	const myMath::Vector2 center = { 640.0f,360.0f };
	resultPos_ = center + PhysicsMath::FigureOfEight(100.0f, 50.0f, time_, 180.0f);

	skyDomeTrans_.TransUpdate(camera_.get());//天球

	lightManager_->Update();

	//ポイントライト
	lightManager_->SetPointLightActive(0, true);
	lightManager_->SetPointLightPos(0, { 0.0f,0.0f ,0.0f });
	lightManager_->SetPointLightColor(0, { 1.0f,1.0f,1.0f });
	lightManager_->SetPointLightAtten(0, { 0.3f,0.1f,0.1f });
}

void ResultScene::Draw()
{
	skyDome_->DrawModel(&skyDomeTrans_);
	result_->DrawSprite2D(resultPos_);
	SceneChangeAnimation::GetInstance()->Draw();
}

void ResultScene::camUpdate()
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