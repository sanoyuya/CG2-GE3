#include "GameScene.h"
#include"PhysicsMath.h"
#include<imgui.h>
#include"ColliderManager.h"
#include"SceneChangeAnimation.h"
#include"MultiTexturePostEffect.h"
#include"Retention.h"
#include"Pose.h"

void GameScene::Initialize()
{
	input_ = InputManager::GetInstance();
	audioManager_ = AudioManager::GetInstance();

	lightManager_.reset(lightManager_->Create());
	Model::SetLight(lightManager_.get());
	lightPos_ = { 0.0f,0.0f,-2.0f };
	lightColor_ = { 1.0f,1.0f ,1.0f };
	lightAtten_ = { 0.3f,0.1f,0.1f };

	//天球
	skyDome_ = std::make_unique<Model>();
	skyDomeTex_ = Model::CreateObjModel("Resources/skydome");
	skyDome_->SetModel(skyDomeTex_);
	skyDomeTrans_.Initialize();
	skyDomeTrans_.scale = { 5.0f,5.0f ,5.0f };

	//レベルエディタの初期化&読み込み
	gameLevelData_ = std::make_unique<GameLevelData>();
	switch (Retention::GetInstance()->GetStageNum())
	{
	case Stage::Tutorial:
		gameLevelData_->Initialize("stage0");
		break;
	case Stage::Stage1:
		gameLevelData_->Initialize("stage1");
		break;
	case Stage::Stage2:
		gameLevelData_->Initialize("stage2");
		break;
	case Stage::Stage3:
		gameLevelData_->Initialize("stage3");
		break;
	default:
		break;
	}

	gameTimer_ = std::make_unique<GameTimer>();

	player_ = std::make_unique<Player>();
	player_->Initialize();
	playerDamageEffect_ = std::make_unique<PlayerDamageEffect>();

	camera_ = std::make_unique<RailCamera>();
	camera_->Initialize(gameLevelData_->GetCameraData());
	camera_->Update();

	enemyManager_ = std::make_unique<EnemyManager>();
	enemyManager_->Initialize(gameLevelData_->GetEnemyData());

	bulletManager_ = std::make_unique<BulletManager>();
	bulletManager_->Initialize();

	radar_ = std::make_unique<Radar>();
	radar_->Initialize(enemyManager_.get());

	bgm_ = audioManager_->LoadAudio("Resources/Sound/1~10.mp3", 0.1f);
	audioManager_->PlayWave(bgm_);
}

void GameScene::Destroy()
{
	ColliderManager::GetInstance()->Reset();
	MultiTexturePostEffect::SetEffectMode(MultiTextureEffectMode::None);
	audioManager_->StopWave(bgm_);
}

void GameScene::Update()
{
	//プレイヤーのHPが0になったらゲームオーバー
	if (player_->GetIsDead() == true)
	{
		SceneChangeAnimation::GetInstance()->Change("GAMEOVER");
	}

	//カメラが最後まで到達したらゲームクリア
	if (camera_->GetTime() >= 0.95f)
	{
		SceneChangeAnimation::GetInstance()->Change("GAMECLEAR");
	}

	if (input_->KeyboardTriggerPush(DIK_R))
	{
		ColliderManager::GetInstance()->Reset();
		gameLevelData_->ReLoad();
		gameTimer_->Reset();
		camera_->ReLoad(gameLevelData_->GetCameraData());
		player_->Reset();
		enemyManager_->ReLoad(gameLevelData_->GetEnemyData());
		bulletManager_->Reset();
	}

	if (input_->KeyboardTriggerPush(DIK_P) || input_->ControllerButtonTriggerPush(START))
	{
		if (Pose::GetInstance()->GetPoseFlag() == false)
		{
			Pose::GetInstance()->SetPoseFlag(true);
		}
		else
		{
			Pose::GetInstance()->SetPoseFlag(false);
		}
	}

	lightManager_->Update();

	//ポイントライト
	lightManager_->SetPointLightActive(0, true);
	lightManager_->SetPointLightPos(0, lightPos_);
	lightManager_->SetPointLightColor(0, lightColor_);
	lightManager_->SetPointLightAtten(0, lightAtten_);

	if (Pose::GetInstance()->GetPoseFlag() == false)
	{
		gameTimer_->Update();
		player_->SetCamera(camera_.get());
		player_->SetBulletManager(bulletManager_.get());
		player_->Update();
		camera_->Update();
		gameLevelData_->Update(camera_->GetCameraPtr());
		skyDomeTrans_.TransUpdate(camera_->GetCameraPtr());//天球
		playerDamageEffect_->Update(player_.get());
		enemyManager_->Update(camera_->GetCameraPtr(), player_.get(), gameTimer_.get(), bulletManager_.get());
		bulletManager_->Update(camera_->GetCameraPtr());
		ColliderManager::GetInstance()->Update(player_.get());
		radar_->Update(camera_->GetCameraPtr());
	}
#ifdef _DEBUG
	camera_->ImGuiUpdate();
	player_->ImGuiUpdate();
	ColliderManager::GetInstance()->ImGuiUpdate();
#endif _DEBUG
}

void GameScene::Draw()
{
	skyDome_->DrawModel(&skyDomeTrans_);
	gameLevelData_->Draw();
	enemyManager_->Draw();
	bulletManager_->Draw();
	player_->Draw();
	radar_->Draw(enemyManager_.get(), player_.get());
	Pose::GetInstance()->Draw();
	SceneChangeAnimation::GetInstance()->Draw();
}