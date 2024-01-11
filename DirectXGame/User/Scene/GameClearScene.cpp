#include "GameClearScene.h"
#include"EasingFunction.h"
#include"SceneChangeAnimation.h"
#include"GameHeader.h"
#include"PhysicsMath.h"
uint32_t GameClearScene::sResultTex_;
uint32_t GameClearScene::sPlayerTex_;
uint32_t GameClearScene::sBgm_;

void GameClearScene::Initialize()
{
	input_ = InputManager::GetInstance();
	audioManager_ = AudioManager::GetInstance();

	gameTimer_ = std::make_unique<GameTimer>();

	//レベルエディタの初期化&読み込み
	gameLevelData_ = std::make_unique<GameLevelData>();
	gameLevelData_->SetGameTimer(gameTimer_.get());
	gameLevelData_->ConvertToString();
	gameLevelData_->SetFileName("gameClear/gameClear");
	gameLevelData_->SetGroundTiling({ 10.0f,10.0f });
	gameLevelData_->Initialize();

	camera_ = std::make_unique<Camera>();
	camera_->Initialize(true);
	cameraPos_ = gameLevelData_->GetCameraData().position;
	camera_->SetEye(cameraPos_);

	GameObject::SetCamera(camera_.get());

	lightManager_.reset(lightManager_->Create());
	Model::SetLight(lightManager_.get());

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
	smokeTrans_.Initialize();
	//エンジンの座標に合わせるため、モデルの中心座標から位置をずらせるように子を作成
	smokeTrans_.parent = &playerTrans_;
	//モデルの中心座標から位置をずらす
	smokeTrans_.translation = { 0.0f,-0.3f,-4.0f };

	result_ = std::make_unique<Sprite>();
	result_->Sprite2DInitialize(sResultTex_);

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

	if (gameTimer_->GetFlameCount() / gameTimer_->GetGameTime() < 1.0f)
	{
		//自機を自機の向かう方向に向ける処理
		playerPos_ = myMath::CatmullRomSpline(controlPoints_, gameTimer_->GetFlameCount() / gameTimer_->GetGameTime());
		frontPos_ = myMath::CatmullRomSpline(controlPoints_, min((gameTimer_->GetFlameCount() + 0.1f) / gameTimer_->GetGameTime(), 1.0f));
		myMath::MakeLookL(playerPos_, frontPos_, up_, controlTrans_.matWorld);

		targetPos_ = playerPos_;
	}
	else
	{
		playerTrans_.rotation.z = -0.0125f * gameTimer_->GetFlameCount();

		targetPos_ = { playerPos_.x + PhysicsMath::SimpleHarmonicMotion(gameTimer_->GetFlameCount(),2.0f,180.0f),playerPos_.y ,playerPos_.z + PhysicsMath::SimpleHarmonicMotion(gameTimer_->GetFlameCount(),2.0f,240.0f) };
	}

	resultAlpha_ = min((gameTimer_->GetFlameCount() - gameTimer_->GetGameTime() / 2) / (GameHeader::sFps_ * 3.0f), 1.0f);

	//パーティクルを毎フレーム作成
	smokeEmitter_->Create(smokeTrans_.parentToTranslation);

	camera_->SetTarget(targetPos_);
	camera_->Update(true);
	playerTrans_.TransUpdate(camera_.get());
	SmokeUpdate();

	gameLevelData_->Update(camera_.get());
	groundBack_->Update(camera_.get(), gameTimer_.get());
	buildingManager_->Update();
	gameTimer_->Update();

	if (GameHeader::isImgui_ == true)
	{
		gameTimer_->ImGuiUpdate();
	}
}

void GameClearScene::Draw()
{
	groundBack_->Draw();
	gameLevelData_->Draw();
	buildingManager_->Draw();
	player_->DrawModel(&playerTrans_);
	smokeEmitter_->Draw();

	result_->DrawSprite2D(GameHeader::windowsCenter_, { 1.0f,1.0f ,1.0f,resultAlpha_ }, { 0.5f,0.5f });
	SceneChangeAnimation::GetInstance()->Draw();
}

void GameClearScene::LoadAsset()
{
	sResultTex_ = TextureManager::GetInstance()->LoadTexture("Resources/Texture/defaultGameClear.png");
	sPlayerTex_ = Model::CreateObjModel("Resources/F-35E");
	sBgm_ = AudioManager::GetInstance()->LoadAudio("Resources/Sound/Blinded.mp3", 0.1f);
}

void GameClearScene::Load(const CameraData& cameraData)
{
	for (auto it = cameraData.controlPoints.begin(); it != cameraData.controlPoints.end(); ++it)
	{
		controlPoints_.push_back(it->position);
	}
}

void GameClearScene::SmokeUpdate()
{
	//子の更新処理
	smokeTrans_.TransUpdate(camera_.get());
	//パーティクルの更新
	smokeEmitter_->Update(camera_.get());
}