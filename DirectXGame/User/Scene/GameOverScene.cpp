#include "GameOverScene.h"
#include"EasingFunction.h"
#include"SceneChangeAnimation.h"
#include"GameHeader.h"
#include"PhysicsMath.h"
uint32_t GameOverScene::sResultTex_;
uint32_t GameOverScene::sPlayerTex_;
uint32_t GameOverScene::sBgm_;

void GameOverScene::Initialize()
{
	input_ = InputManager::GetInstance();
	audioManager_ = AudioManager::GetInstance();

	gameTimer_ = std::make_unique<GameTimer>();

	//レベルエディタの初期化&読み込み
	gameLevelData_ = std::make_unique<GameLevelData>();
	gameLevelData_->SetGameTimer(gameTimer_.get());
	gameLevelData_->ConvertToString();
	gameLevelData_->SetFileName("gameOver/gameOver");
	gameLevelData_->SetGroundTiling({ 10.0f,10.0f });
	gameLevelData_->Initialize();

	camera_ = std::make_unique<Camera>();
	camera_->Initialize(true);
	cameraPos_ = gameLevelData_->GetCameraData().position;
	camera_->SetEye(cameraPos_);

	GameObject::SetCamera(camera_.get());

	lightManager_.reset(lightManager_->Create());
	Model::SetLight(lightManager_.get());

	result_ = std::make_unique<Sprite>();
	result_->Sprite2DInitialize(sResultTex_);

	groundBack_ = std::make_unique<GroundBack>();
	groundBack_->Initialize(gameLevelData_->GetGroundTranslation(), gameLevelData_->GetGroundSize());

	buildingManager_ = std::make_unique<BuildingManager>();
	buildingManager_->Initialize(gameLevelData_->GetBuildingList());

	Load(gameLevelData_->GetCameraData());
	controlTrans_.Initialize();

	//戦闘機
	player_ = std::make_unique<Model>();
	player_->SetModel(sPlayerTex_);
	playerTrans_.Initialize();
	playerTrans_.parent = &controlTrans_;

	//パーティクルの初期化
	smokeEmitter_ = std::make_unique<PlayerEngineSmokeParticleEmitter>();
	smokeEmitter_->Initialize();
	smokeEmitter_->SetColor({ 0.0f,0.0f ,0.0f ,1.0 });
	smokeTrans_.Initialize();
	//エンジンの座標に合わせるため、モデルの中心座標から位置をずらせるように子を作成
	smokeTrans_.parent = &playerTrans_;
	//モデルの中心座標から位置をずらす
	smokeTrans_.translation = { 0.0f,-0.3f,-4.0f };

	//死亡演出の初期化
	deathParticleEmitter_ = std::make_unique<EnemyDeathParticleEmitter>();
	deathParticleEmitter_->Initialize();

	bigBangEmitter_= std::make_unique<BigBang>();
	bigBangEmitter_->Initialize();

	audioManager_->PlayWave(sBgm_, true);
}

void GameOverScene::Destroy()
{
	audioManager_->StopWave(sBgm_);
}

void GameOverScene::Update()
{
	if (input_->KeyboardTriggerPush(DIK_SPACE) || input_->ControllerButtonTriggerPush(A))
	{
		SceneChangeAnimation::GetInstance()->Change("TITLE");
	}

	if (gameTimer_->GetFlameCount() / gameTimer_->GetGameTime() < 1.0f)
	{
		//自機を自機の向かう方向に向ける処理
		playerPos_ = myMath::CatmullRomSpline(controlPoints_, gameTimer_->GetFlameCount() / gameTimer_->GetGameTime());
		frontPos_ = myMath::CatmullRomSpline(controlPoints_, min((gameTimer_->GetFlameCount() + 0.1f) / gameTimer_->GetGameTime(),1.0f));
		myMath::MakeLookL(playerPos_, frontPos_, up_, controlTrans_.matWorld);

		playerTrans_.rotation.z = -0.0125f * gameTimer_->GetFlameCount();

		//パーティクルを毎フレーム作成
		smokeEmitter_->Create(smokeTrans_.parentToTranslation);

		//1秒に一回爆発演出を出す
		if (static_cast<uint8_t>(gameTimer_->GetFlameCount()) % static_cast<uint8_t>(GameHeader::sFps_) == 0)
		{
			deathParticleEmitter_->Create(myMath::CatmullRomSpline(controlPoints_, min((gameTimer_->GetFlameCount() + 5.0f) / gameTimer_->GetGameTime(), 1.0f)));
		}
	}
	else
	{
		deathParticleEmitter_->Create(playerTrans_.parentToTranslation);

		cameraPos_.x = PhysicsMath::CircularMotion({ 0.0f,0.0f }, 30.0f, angle_).x;
		cameraPos_.z = PhysicsMath::CircularMotion({ 0.0f,0.0f }, 30.0f, angle_).y;
		camera_->SetEye(cameraPos_);

		angle_ = (gameTimer_->GetFlameCount() - gameTimer_->GetGameTime()) * 0.005f;
	}

	//地面に着地したら大爆発するように
	if (gameTimer_->GetFlameCount() == gameTimer_->GetGameTime())
	{
		bigBangEmitter_->Create(playerTrans_.parentToTranslation);
	}

	resultAlpha_ = min((gameTimer_->GetFlameCount() - gameTimer_->GetGameTime()) / (GameHeader::sFps_ * 3.0f), 1.0f);

	camera_->SetTarget(playerPos_);
	camera_->Update(true);
	playerTrans_.TransUpdate(camera_.get());
	SmokeUpdate();
	//死亡演出のパーティクルの更新処理
	deathParticleEmitter_->Update(camera_.get());
	bigBangEmitter_->Update(camera_.get());

	gameLevelData_->Update(camera_.get());
	groundBack_->Update(camera_.get(), gameTimer_.get());
	buildingManager_->Update();
	gameTimer_->Update();

	if (GameHeader::isImgui_ == true)
	{
		gameTimer_->ImGuiUpdate();
	}
}

void GameOverScene::Draw()
{
	groundBack_->Draw();
	gameLevelData_->Draw();
	buildingManager_->Draw();
	player_->DrawModel(&playerTrans_);
	smokeEmitter_->Draw();
	//死亡演出の描画
	deathParticleEmitter_->Draw();
	bigBangEmitter_->Draw();

	result_->DrawSprite2D(GameHeader::windowsCenter_, { 1.0f,1.0f ,1.0f,resultAlpha_ }, { 0.5f,0.5f });
	SceneChangeAnimation::GetInstance()->Draw();
}

void GameOverScene::LoadAsset()
{
	sResultTex_ = TextureManager::GetInstance()->LoadTexture("Resources/Texture/defaultGameOver.png");
	sPlayerTex_ = Model::CreateObjModel("Resources/F-35E");
	sBgm_ = AudioManager::GetInstance()->LoadAudio("Resources/Sound/Blinded.mp3", 0.1f);
}

void GameOverScene::Load(const CameraData& cameraData)
{
	for (auto it = cameraData.controlPoints.begin(); it != cameraData.controlPoints.end(); ++it)
	{
		controlPoints_.push_back(it->position);
	}
}

void GameOverScene::SmokeUpdate()
{
	//子の更新処理
	smokeTrans_.TransUpdate(camera_.get());
	//パーティクルの更新
	smokeEmitter_->Update(camera_.get());
}