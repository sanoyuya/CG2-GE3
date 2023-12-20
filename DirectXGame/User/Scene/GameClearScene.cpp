#include "GameClearScene.h"
#include"EasingFunction.h"
#include"SceneChangeAnimation.h"
uint32_t GameClearScene::sResultTex_;
uint32_t GameClearScene::sSkyDomeTex_;
uint32_t GameClearScene::sBgm_;

void GameClearScene::Initialize()
{
	input_ = InputManager::GetInstance();
	audioManager_ = AudioManager::GetInstance();

	camera_ = std::make_unique<Camera>();
	camera_->Initialize(true);
	cameraPos_ = { 0.0f,0.0f,0.0f };

	lightManager_.reset(lightManager_->Create());
	Model::SetLight(lightManager_.get());

	result_ = std::make_unique<Sprite>();
	result_->Sprite2DInitialize(sResultTex_);

	//天球
	skyDome_ = std::make_unique<Model>();
	skyDome_->SetModel(sSkyDomeTex_);
	skyDomeTrans_.Initialize();

	audioManager_->PlayWave(sBgm_, true);
}

void GameClearScene::Destroy()
{
	audioManager_->StopWave(sBgm_);
}

void GameClearScene::Update()
{
	if (input_->KeyboardTriggerPush(DIK_SPACE) || input_->ControllerButtonTriggerPush(A))
	{
		SceneChangeAnimation::GetInstance()->Change("TITLE");
	}
}

void GameClearScene::Draw()
{
	skyDome_->DrawModel(&skyDomeTrans_);
	result_->DrawSprite2D({ 640.0f,360.0f });
	SceneChangeAnimation::GetInstance()->Draw();
}

void GameClearScene::LoadAsset()
{
	sResultTex_ = TextureManager::GetInstance()->LoadTexture("Resources/defaultGameClear.png");
	sSkyDomeTex_ = Model::CreateObjModel("Resources/skydome2");
	sBgm_ = AudioManager::GetInstance()->LoadAudio("Resources/Sound/Blinded.mp3", 0.1f);
}