#include "GameScene.h"
#include"PhysicsMath.h"
#include<imgui.h>
#include"ColliderManager.h"
#include"SceneChangeAnimation.h"
#include"MultiTexturePostEffect.h"
#include"Retention.h"
uint32_t GameScene::sBgm_;

GameScene::~GameScene()
{
	ColliderManager::GetInstance()->Reset();
}

void GameScene::Initialize()
{
	input_ = InputManager::GetInstance();
	audioManager_ = AudioManager::GetInstance();

	lightManager_.reset(lightManager_->Create());
	Model::SetLight(lightManager_.get());
	lightPos_ = { 0.0f,0.0f,-2.0f };
	lightColor_ = { 1.0f,1.0f ,1.0f };
	lightAtten_ = { 0.3f,0.1f,0.1f };

	gameTimer_ = std::make_unique<GameTimer>();
	//レベルエディタの初期化&読み込み
	gameLevelData_ = std::make_unique<GameLevelData>();
	gameLevelData_->SetGameTimer(gameTimer_.get());
	gameLevelData_->Initialize();

	camera_ = std::make_unique<RailCamera>();
	camera_->Initialize(gameLevelData_->GetCameraData());
	camera_->Update(gameTimer_.get());

	GameObject::SetCamera(camera_->GetCameraPtr());
	GameObject::SetGameTimer(gameTimer_.get());

	bulletManager_ = std::make_unique<BulletManager>();
	bulletManager_->Initialize();

	player_ = std::make_unique<Player>();
	player_->Initialize();
	player_->SetCamera(camera_.get());
	player_->SetBulletManager(bulletManager_.get());
	playerDamageEffect_ = std::make_unique<PlayerDamageEffect>();

	enemyManager_ = std::make_unique<EnemyManager>();
	enemyManager_->Initialize(gameLevelData_->GetEnemyData(), player_.get(), bulletManager_.get());

	radar_ = std::make_unique<Radar>();
	radar_->Initialize(enemyManager_.get());

	tutorial_ = std::make_unique<Tutorial>();
	tutorial_->Initialize(gameTimer_.get());

	groundBack_= std::make_unique<GroundBack>();
	groundBack_->Initialize(gameLevelData_->GetGroundTranslation(), gameLevelData_->GetGroundSize());

	buildingManager_ = std::make_unique<BuildingManager>();
	buildingManager_->Initialize(gameLevelData_->GetBuildingList());

	enemyLocationSprite_ = std::make_unique<EnemyLocationSprite>();
	enemyLocationSprite_->Load(enemyManager_.get());

	pose_ = std::make_unique<Pose>();
	pose_->Initialize();

	audioManager_->PlayWave(sBgm_, true);
}

void GameScene::Destroy()
{
	ColliderManager::GetInstance()->Reset();
	MultiTexturePostEffect::SetEffectMode(MultiTextureEffectMode::None);
	audioManager_->StopWave(sBgm_);
}

void GameScene::Update()
{
	//プレイヤーのHPが0になったらゲームオーバー
	if (player_->GetIsDead() == true)
	{
		SceneChangeAnimation::GetInstance()->Change("GAMEOVER");
	}

	//カメラが最後まで到達したらゲームクリア
	if (gameTimer_->GetFlameCount() / gameTimer_->GetGameTime() >= 0.95f)
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
		enemyManager_->ReLoad(gameLevelData_->GetEnemyData(), player_.get(), bulletManager_.get());
		bulletManager_->Reset();
		buildingManager_->ReLoad(gameLevelData_->GetBuildingList());
		enemyLocationSprite_->ReLoad(enemyManager_.get());
		tutorial_->Rest();
	}

	if (input_->KeyboardTriggerPush(DIK_T))
	{
		ColliderManager::GetInstance()->Reset();
		SceneChangeAnimation::GetInstance()->Change("TITLE");
	}

	pose_->Update();

	lightManager_->Update();

	//ポイントライト
	lightManager_->SetPointLightActive(0, false);
	lightManager_->SetPointLightPos(0, lightPos_);
	lightManager_->SetPointLightColor(0, lightColor_);
	lightManager_->SetPointLightAtten(0, lightAtten_);

	if (pose_->GetPoseFlag() == false)
	{
		camera_->BeginUpdate(gameTimer_.get());
		gameTimer_->Update();
		player_->Update();
		camera_->Update(gameTimer_.get());
		gameLevelData_->Update(camera_->GetCameraPtr());
		groundBack_->Update(camera_->GetCameraPtr(), gameTimer_.get());
		buildingManager_->Update();
		playerDamageEffect_->Update(player_.get());
		enemyManager_->Update();
		bulletManager_->Update();
		ColliderManager::GetInstance()->Update(player_.get());
		radar_->Update(camera_->GetCameraPtr());
		tutorial_->Update();
	}
#ifdef _DEBUG
	gameTimer_->ImGuiUpdate();
	camera_->ImGuiUpdate();
	player_->ImGuiUpdate();
	ColliderManager::GetInstance()->ImGuiUpdate();
	ImGui::Begin("EnemyReset");
	if (ImGui::Button("EnemyReset"))
	{
		gameLevelData_->Initialize();
		enemyManager_->ReLoad(gameLevelData_->GetEnemyData(), player_.get(), bulletManager_.get());
	}
	ImGui::End();
#endif _DEBUG
}

void GameScene::Draw()
{
	groundBack_->Draw();
	bulletManager_->Draw();
	gameLevelData_->Draw();
	buildingManager_->Draw();
	enemyManager_->Draw();
	bulletManager_->Draw();
	player_->Draw();
	radar_->Draw(enemyManager_.get(), player_.get());
	enemyLocationSprite_->Draw(enemyManager_.get(), camera_->GetCameraPtr());
	tutorial_->Draw();
	
	pose_->Draw();
	SceneChangeAnimation::GetInstance()->Draw();
}

void GameScene::LoadAsset()
{
	sBgm_ = AudioManager::GetInstance()->LoadAudio("Resources/Sound/1~10.mp3", 0.1f);
}