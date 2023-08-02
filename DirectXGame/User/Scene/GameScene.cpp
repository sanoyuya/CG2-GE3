#include "GameScene.h"
#include"SceneManager.h"
#include"PhysicsMath.h"
#include<imgui.h>
#include"ColliderManager.h"
#include"SceneChangeAnimation.h"
#include"PostEffect.h"

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
	skyDomeTex_ = Model::CreateObjModel("Resources/skydome2");
	skyDome_->SetModel(skyDomeTex_);
	skyDomeTrans_.Initialize();
	skyDomeTrans_.scale = { 2.0f,2.0f ,2.0f };

	//レベルエディタの初期化&読み込み
	gameLevelData_ = std::make_unique<GameLevelData>();
	gameLevelData_->Initialize("stage1");

	gameTimer_ = std::make_unique<GameTimer>();

	player_ = std::make_unique<Player>();
	player_->Initialize();
	playerDamageEffect_ = std::make_unique<PlayerDamageEffect>();

	camera_ = std::make_unique<RailCamera>();
	camera_->Initialize(gameLevelData_->GetCameraData());
	camera_->Update(player_.get());

	enemyManager_ = std::make_unique<EnemyManager>();
	enemyManager_->Initialize(gameLevelData_->GetEnemyData());

	radar_= std::make_unique<Radar>();
	radar_->Initialize(enemyManager_.get());

	bgm_ = audioManager_->LoadAudio("Resources/Sound/1~10.mp3", 0.1f);
	audioManager_->PlayWave(bgm_);
}

void GameScene::Destroy()
{
	ColliderManager::GetInstance()->Reset();
	PostEffect::SetEffectMode(EffectMode::None);
	audioManager_->StopWave(bgm_);
}

void GameScene::Update()
{
	SceneChangeAnimation::GetInstance()->Update();
	SceneChangeAnimation::GetInstance()->ChangeAfter();

	//プレイヤーのHPが0になったらゲームオーバー
	if (player_->GetDeathFlag()==true)
	{
		SceneChangeAnimation::GetInstance()->SetAnimationFlag(true);
		SceneChangeAnimation::GetInstance()->Change("GAMEOVER");
	}

	//カメラが最後まで到達したらゲームクリア
	if (camera_->GetTime() >= 0.95f)
	{
		SceneChangeAnimation::GetInstance()->SetAnimationFlag(true);
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
	}

	lightManager_->Update();

	//ポイントライト
	lightManager_->SetPointLightActive(0, true);
	lightManager_->SetPointLightPos(0, lightPos_);
	lightManager_->SetPointLightColor(0, lightColor_);
	lightManager_->SetPointLightAtten(0, lightAtten_);
	
	gameTimer_->Update();
	player_->Update(camera_->GetCameraPtr());
	camera_->Update(player_.get());
	gameLevelData_->Update(camera_->GetCameraPtr());
	skyDomeTrans_.TransUpdate(camera_->GetCameraPtr());//天球
	playerDamageEffect_->Update(player_.get());
	enemyManager_->Update(camera_->GetCameraPtr(), player_.get(),gameTimer_.get());
	ColliderManager::GetInstance()->Update(player_.get());
	radar_->Update(camera_->GetCameraPtr());
}

void GameScene::Draw()
{
	skyDome_->DrawModel(&skyDomeTrans_);
	gameLevelData_->Draw();
	enemyManager_->Draw();
	player_->Draw(camera_->GetCameraPtr());
	radar_->Draw(enemyManager_.get(),player_.get());
	SceneChangeAnimation::GetInstance()->Draw();
}