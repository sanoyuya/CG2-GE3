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
	skyDomeTex_ = Model::CreateObjModel("Resources/skydome3");
	skyDomeTex2_ = Model::CreateObjModel("Resources/skydome");
	skyDomeTrans_.Initialize();
	skyDomeTrans_.scale = { 20.0f,20.0f ,20.0f };

	//レベルエディタの初期化&読み込み
	gameLevelData_ = std::make_unique<GameLevelData>();
	gameTimer_ = std::make_unique<GameTimer>();
	switch (Retention::GetInstance()->GetStageNum())
	{
	case Stage::Tutorial:
		gameLevelData_->Initialize("stage0/stage");
		skyDome_->SetModel(skyDomeTex_);
		gameTimer_->SetGameTime(static_cast<uint32_t>(60 * 60 * 3.0));
		break;
	case Stage::Stage1:
		gameLevelData_->Initialize("stage1/stage");
		skyDome_->SetModel(skyDomeTex2_);
		gameTimer_->SetGameTime(60 * 60 * 1);
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

	player_ = std::make_unique<Player>();
	player_->Initialize();
	playerDamageEffect_ = std::make_unique<PlayerDamageEffect>();

	camera_ = std::make_unique<RailCamera>();
	camera_->Initialize(gameLevelData_->GetCameraData());
	camera_->Update(gameTimer_.get());

	enemyManager_ = std::make_unique<EnemyManager>();
	enemyManager_->Initialize(gameLevelData_->GetEnemyData());

	bulletManager_ = std::make_unique<BulletManager>();
	bulletManager_->Initialize();

	radar_ = std::make_unique<Radar>();
	radar_->Initialize(enemyManager_.get());

	TextInitialize();

	groundBack_= std::make_unique<GroundBack>();
	groundBack_->Initialize(gameLevelData_->GetGroundTranslation(), gameLevelData_->GetGroundSize());

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
		ColliderManager::GetInstance()->Reset();
		SceneChangeAnimation::GetInstance()->Change("GAMEOVER");
	}

	//カメラが最後まで到達したらゲームクリア
	if (gameTimer_->GetFlameCount() / gameTimer_->GetGameTime() >= 0.95f)
	{
		ColliderManager::GetInstance()->Reset();
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

	if (input_->KeyboardTriggerPush(DIK_T))
	{
		ColliderManager::GetInstance()->Reset();
		SceneChangeAnimation::GetInstance()->Change("TITLE");
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
	lightManager_->SetPointLightActive(0, false);
	lightManager_->SetPointLightPos(0, lightPos_);
	lightManager_->SetPointLightColor(0, lightColor_);
	lightManager_->SetPointLightAtten(0, lightAtten_);

	if (Pose::GetInstance()->GetPoseFlag() == false)
	{
		camera_->BeginUpdate(gameTimer_.get());
		gameTimer_->Update();
		player_->SetCamera(camera_.get());
		player_->SetBulletManager(bulletManager_.get());
		player_->Update();
		camera_->Update(gameTimer_.get());
		gameLevelData_->Update(camera_->GetCameraPtr());
		groundBack_->Update(camera_->GetCameraPtr(), gameTimer_.get());
		skyDomeTrans_.TransUpdate(camera_->GetCameraPtr());//天球
		playerDamageEffect_->Update(player_.get());
		enemyManager_->Update(camera_->GetCameraPtr(), player_.get(), gameTimer_.get(), bulletManager_.get());
		bulletManager_->Update(camera_->GetCameraPtr());
		ColliderManager::GetInstance()->Update(player_.get());
		radar_->Update(camera_->GetCameraPtr());
		if (Retention::GetInstance()->GetStageNum() == Stage::Tutorial)
		{
			TextUpdate();
		}
	}
#ifdef _DEBUG
	gameTimer_->ImGuiUpdate();
	camera_->ImGuiUpdate();
	player_->ImGuiUpdate();
	ColliderManager::GetInstance()->ImGuiUpdate();
#endif _DEBUG
}

void GameScene::Draw()
{
	skyDome_->DrawModel(&skyDomeTrans_, { 0.0125f,0.0125f,0.0125f,1.0f });
	groundBack_->Draw();
	gameLevelData_->Draw();
	enemyManager_->Draw();
	bulletManager_->Draw();
	player_->Draw();
	radar_->Draw(enemyManager_.get(), player_.get());
	if (Retention::GetInstance()->GetStageNum() == Stage::Tutorial)
	{
		TextDraw();
	}
	Pose::GetInstance()->Draw();
	SceneChangeAnimation::GetInstance()->Draw();
}

void GameScene::TextInitialize()
{
	if (Retention::GetInstance()->GetStageNum() == Stage::Tutorial)
	{
		moveText_ = std::make_unique<Text>();
		moveText_->Initialize("Resources/move.png");

		attackText_ = std::make_unique<Text>();
		attackText_->Initialize("Resources/attack.png");

		cameraText_ = std::make_unique<Text>();
		cameraText_->Initialize("Resources/camera.png");

		chargeAttackText_ = std::make_unique<Text>();
		chargeAttackText_->Initialize("Resources/chargeAttack.png");

		readyText_ = std::make_unique<Text>();
		readyText_->Initialize("Resources/ready.png");

		goText_ = std::make_unique<Text>();
		goText_->Initialize("Resources/go.png");
	}
}

void GameScene::TextUpdate()
{
	moveText_->Update(gameTimer_.get(), 3, 7);//Blender上で設定できるようにしたい
	attackText_->Update(gameTimer_.get(), 9, 13);
	cameraText_->Update(gameTimer_.get(), 20, 25);
	chargeAttackText_->Update(gameTimer_.get(), 50, 55);
	readyText_->Update(gameTimer_.get(), 81, 84);
	goText_->Update(gameTimer_.get(), 84, 86);
}

void GameScene::TextDraw()
{
	moveText_->Draw();
	attackText_->Draw();
	cameraText_->Draw();
	chargeAttackText_->Draw();
	readyText_->Draw();
	goText_->Draw();
}