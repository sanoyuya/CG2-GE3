#include "GameScene.h"
#include"SceneManager.h"
#include"PhysicsMath.h"
#include<imgui.h>

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
	gameLevelData_->Initialize("untitled");

	camera_ = std::make_unique<RailCamera>();
	camera_->Initialize(gameLevelData_->GetCameraData());
	camera_->Update();

	player_ = std::make_unique<Player>();
	player_->Initialize();
}

void GameScene::Destroy()
{
}

void GameScene::Update()
{
	if (input_->KeyboardTriggerPush(DIK_SPACE))
	{
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}
	else if (input_->KeyboardTriggerPush(DIK_R))
	{
		gameLevelData_->ReLoad();
		camera_->ReLoad(gameLevelData_->GetCameraData());
	}

	lightManager_->Update();

	//ポイントライト
	lightManager_->SetPointLightActive(0, true);
	lightManager_->SetPointLightPos(0, lightPos_);
	lightManager_->SetPointLightColor(0, lightColor_);
	lightManager_->SetPointLightAtten(0, lightAtten_);

	camera_->Update();

	gameLevelData_->Update(camera_->GetCameraPtr());

	skyDomeTrans_.TransUpdate(camera_->GetCameraPtr());//天球
	player_->Update(camera_->GetCameraPtr());
}

void GameScene::Draw()
{
	skyDome_->DrawModel(&skyDomeTrans_);
	gameLevelData_->Draw();
	player_->Draw();
}