#pragma once
#include"InputManager.h"
#include"AudioManager.h"
#include"Camera.h"
#include"DrawOversight.h"
#include"BaseScene.h"
#include"Collision.h"
#include"LightManager.h"
#include"PostEffect.h"
#include"GameLevelData.h"
#include"EnemyManager.h"
#include"PlayerDamageEffect.h"
#include"Radar.h"
#include"GameTimer.h"
#include"BulletManager.h"
#include"GroundBack.h"
#include"BuildingManager.h"
#include"EnemyLocationSprite.h"
#include"Tutorial.h"
#include"Pose.h"

class GameScene :public BaseScene
{
private:

	//クラス読み込み
	InputManager* input_ = nullptr;
	AudioManager* audioManager_ = nullptr;

	std::unique_ptr<RailCamera>camera_;
	std::unique_ptr<LightManager>lightManager_;
	myMath::Vector3 lightPos_ = { 0.0f,0.0f ,0.0f };
	myMath::Vector3 lightColor_ = { 0.0f,0.0f ,0.0f };
	myMath::Vector3 lightAtten_ = { 0.0f,0.0f ,0.0f };

	//天球
	std::unique_ptr<Model>skyDome_;
	Transform skyDomeTrans_;
	static uint32_t sSkyDomeTex_;
	static uint32_t sSkyDomeTex2_;

	std::unique_ptr<GameLevelData> gameLevelData_;

	std::unique_ptr<Player>player_;
	std::unique_ptr<PlayerDamageEffect>playerDamageEffect_;

	std::unique_ptr<EnemyManager>enemyManager_;

	std::unique_ptr<BulletManager>bulletManager_;

	std::unique_ptr<Radar>radar_;

	std::unique_ptr<GameTimer>gameTimer_;

	std::unique_ptr<BuildingManager>buildingManager_;

	static uint32_t sBgm_;

	bool poseFlag_ = false;

	std::unique_ptr<GroundBack>groundBack_;

	std::unique_ptr<EnemyLocationSprite>enemyLocationSprite_;

	std::unique_ptr<Tutorial>tutorial_;

	std::unique_ptr<Pose>pose_;

public:

	~GameScene();

	//初期化処理
	void Initialize()override;

	//終了処理
	void Destroy()override;

	//更新処理
	void Update()override;

	//描画処理
	void Draw()override;

	static void LoadAsset();
};