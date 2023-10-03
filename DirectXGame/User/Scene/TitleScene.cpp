#include "TitleScene.h"
#include"SceneManager.h"
#include<imgui.h>
#include"PhysicsMath.h"
#include"PostEffect.h"
#include"EasingFunction.h"
#include"SceneChangeAnimation.h"
#include"MultiTexturePostEffect.h"

void TitleScene::Initialize()
{
	input_ = InputManager::GetInstance();
	audioManager_ = AudioManager::GetInstance();

	camera_ = std::make_unique<Camera>();
	camera_->Initialize(true);
	camera_->SetEye({ 0,0,-25 });
	camera_->Update(true);

	lightManager_.reset(lightManager_->Create());
	Model::SetLight(lightManager_.get());

	title_ = std::make_unique<Sprite>();
	titleTex_ = title_->LoadTexture("Resources/gameLogo.png");
	title_->Sprite2DInitialize(titleTex_);

	pressButton_ = std::make_unique<Sprite>();
	pressButtonTex_ = pressButton_->LoadTexture("Resources/pressAButton.png");
	pressButton_->Sprite2DInitialize(pressButtonTex_);

	//天球
	skyDome_ = std::make_unique<Model>();
	skyDomeTex_ = skyDome_->CreateObjModel("Resources/skydome");
	skyDome_->SetModel(skyDomeTex_);
	skyDomeTrans_.Initialize();

	//戦闘機
	player_ = std::make_unique<Model>();
	playerTex_ = player_->CreateObjModel("Resources/F-35E");
	player_->SetModel(playerTex_);
	playerTrans_.Initialize();
	playerTrans_.parent = &skyDomeTrans_;
	playerTrans_.rotation.y = myMath::AX_PIF / 2;

	//パーティクルの初期化
	smokeEmitter_ = std::make_unique<PlayerEngineSmokeParticleEmitter>();
	smokeEmitter_->Initialize();
	smokeTrans_.Initialize();
	//エンジンの座標に合わせるため、モデルの中心座標から位置をずらせるように子を作成
	smokeTrans_.parent = &playerTrans_;

	animationBoxTex_ = TextureManager::GetInstance()->LoadTexture("Resources/white1x1.png");
	for (uint8_t i = 0; i < 2; i++)
	{
		animationBox_[i] = std::make_unique<Sprite>();
		animationBox_[i]->Sprite2DInitialize(animationBoxTex_);
	}

	cloudTex_ = Model::CreateObjModel("Resources/cube");
	for (uint8_t i = 0; i < 5; i++)
	{
		cloud_[i] = std::make_unique<Model>();
		cloud_[i]->SetModel(cloudTex_);
		cloudTrans_[i].Initialize();
		cloudTrans_[i].translation = { static_cast<float>(myMath::GetRand(-50.0f,50.0f)),static_cast<float>(myMath::GetRand(-7.5f,-5.0f)) ,static_cast<float>(myMath::GetRand(-5.0f,5.0f)) };
		cloudTrans_[i].scale = { static_cast<float>(myMath::GetRand(4.0f,8.0f)),static_cast<float>(myMath::GetRand(2.0f,4.0f)) ,static_cast<float>(myMath::GetRand(4.0f,8.0f)) };
	}

	bgm_ = audioManager_->LoadAudio("Resources/Sound/title.mp3",0.1f);
	audioManager_->PlayWave(bgm_);

	MultiTexturePostEffect::SetEffectMode(MultiTextureEffectMode::None);
}

void TitleScene::Destroy()
{
	audioManager_->StopWave(bgm_);
}

void TitleScene::Update()
{
	if (input_->KeyboardTriggerPush(DIK_SPACE) || input_->ControllerButtonTriggerPush(A))
	{
		animationFlag_ = true;
	}
#ifdef _DEBUG
	else if (input_->KeyboardTriggerPush(DIK_D) || input_->ControllerButtonTriggerPush(Y))
	{
		SceneChangeAnimation::GetInstance()->Change("DEMO");
	}
#endif // DEBUG

	skyDomeTrans_.translation.x += 0.15f;

	camera_->SetEye({ skyDomeTrans_.translation.x, 0,-25 });
	camera_->SetTarget(skyDomeTrans_.translation);
	camera_->Update(true);

	skyDomeTrans_.TransUpdate(camera_.get());//天球
	PlayerUpdate();

	time_++;
	position_.y = 100.0f + PhysicsMath::SimpleHarmonicMotion(time_);

	lightManager_->Update();

	if (animationFlag_ == true)
	{
		if (animationTime_ <= 30)
		{
			animationBoxScale_ = static_cast<float>(Easing::EaseOutCubic(animationTime_, 0.0f, 100.0f, 30));
		}
		if (animationTime_ > 100)
		{
			SceneChangeAnimation::GetInstance()->Change("GAME");
		}
		animationTime_++;
	}

	for (uint8_t i = 0; i < 5; i++)
	{
		if (animationFlag_ == false)
		{
			if (cloudTrans_[i].translation.x < playerTrans_.parentToTranslation.x - 50.0f)
			{
				cloudTrans_[i].translation = { playerTrans_.parentToTranslation.x + 75.0f,static_cast<float>(myMath::GetRand(-7.5f,-5.0f)) ,static_cast<float>(myMath::GetRand(-5.0f,5.0f)) };
				cloudTrans_[i].scale = { static_cast<float>(myMath::GetRand(4.0f,8.0f)),static_cast<float>(myMath::GetRand(2.0f,4.0f)) ,static_cast<float>(myMath::GetRand(4.0f,8.0f)) };
			}
		}

		cloudTrans_[i].TransUpdate(camera_.get());
	}

	//ポイントライト
	/*lightManager_->SetPointLightActive(0, true);
	lightManager_->SetPointLightPos(0, { 0.0f,0.0f ,0.0f });
	lightManager_->SetPointLightColor(0, { 1.0f,1.0f,1.0f });
	lightManager_->SetPointLightAtten(0, { 0.3f,0.1f,0.1f });*/
}

void TitleScene::Draw()
{
	skyDome_->DrawModel(&skyDomeTrans_);
	smokeEmitter_->Draw();
	player_->DrawModel(&playerTrans_);

	for (uint8_t i = 0; i < 5; i++)
	{
		cloud_[i]->DrawModel(&cloudTrans_[i], { 1.0f,1.0f,1.0f,0.5f });
	}

	if (animationFlag_ == false)
	{
		title_->DrawSprite2D({ position_ });
		pressButton_->DrawSprite2D({ 640.0f,600.0f });
	}
	else
	{
		animationBox_[0]->DrawSprite2D({ 640.0f,0.0f }, { 0.0f,0.0f,0.0f ,1.0f }, { 1280.0f,animationBoxScale_ }, 0.0f, { 0.5f,0.0f });
		animationBox_[1]->DrawSprite2D({ 640.0f,720.0f }, { 0.0f,0.0f,0.0f ,1.0f }, { 1280.0f,animationBoxScale_ }, 0.0f, { 0.5f,1.0f });
	}

	SceneChangeAnimation::GetInstance()->Draw();
}

void TitleScene::SmokeUpdate()
{
	//モデルの中心座標から位置をずらす
	smokeTrans_.translation = { 0.0f,-0.3f,-4.0f };
	//子の更新処理
	smokeTrans_.TransUpdate(camera_.get());
	//パーティクルを毎フレーム作成
	smokeEmitter_->Create(smokeTrans_.parentToTranslation);
	//パーティクルの更新
	smokeEmitter_->Update(camera_.get());
}

void TitleScene::PlayerUpdate()
{
	if (animationFlag_ == false)
	{
		playerTrans_.translation.x = PhysicsMath::SimpleHarmonicMotion(time_, 0.25f, 180.0f);
	}
	else
	{
		playerTrans_.translation.x = static_cast<float>(Easing::EaseInBack(animationTime_, playerTrans_.translation.x, playerTrans_.translation.x + 2.0f, 120));
	}
	playerTrans_.translation.y = PhysicsMath::SimpleHarmonicMotion(time_, 0.5f, 240.0f);

	playerTrans_.TransUpdate(camera_.get());//戦闘機

	SmokeUpdate();
}
