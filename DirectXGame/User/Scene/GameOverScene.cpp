#include "GameOverScene.h"
#include"EasingFunction.h"
#include"SceneChangeAnimation.h"

void GameOverScene::Initialize()
{
	input_ = InputManager::GetInstance();
	audioManager_ = AudioManager::GetInstance();

	camera_ = std::make_unique<Camera>();
	camera_->Initialize(true);
	cameraPos_ = { 0.0f,0.0f,0.0f };

	lightManager_.reset(lightManager_->Create());
	Model::SetLight(lightManager_.get());

	result_ = std::make_unique<Sprite>();
	resultTex_ = result_->LoadTexture("Resources/defaultGameOver.png");
	result_->Sprite2DInitialize(resultTex_);

	//“V‹…
	skyDome_ = std::make_unique<Model>();
	skyDomeTex_ = Model::CreateObjModel("Resources/skydome2");
	skyDome_->SetModel(skyDomeTex_);
	skyDomeTrans_.Initialize();

	bgm_ = audioManager_->LoadAudio("Resources/Sound/title.mp3", 0.1f);
	audioManager_->PlayWave(bgm_);
}

void GameOverScene::Destroy()
{
	audioManager_->StopWave(bgm_);
}

void GameOverScene::Update()
{
	if (input_->KeyboardTriggerPush(DIK_SPACE) || input_->ControllerButtonTriggerPush(A))
	{
		SceneChangeAnimation::GetInstance()->SetAnimationFlag(true);
	}
	SceneChangeAnimation::GetInstance()->Update();
	SceneChangeAnimation::GetInstance()->ChangeAfter();
	SceneChangeAnimation::GetInstance()->Change("TITLE");
}

void GameOverScene::Draw()
{
	skyDome_->DrawModel(&skyDomeTrans_);
	result_->DrawSprite2D({ 640.0f,360.0f });
	SceneChangeAnimation::GetInstance()->Draw();
}