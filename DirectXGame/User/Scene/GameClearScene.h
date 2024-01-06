#pragma once
#include"BaseScene.h"
#include"InputManager.h"
#include"DrawOversight.h"
#include"Camera.h"
#include"AudioManager.h"
#include"GameLevelData.h"
#include"GroundBack.h"
#include"BuildingManager.h"
#include"PlayerEngineSmokeParticleEmitter.h"

class GameClearScene :public BaseScene
{
private:

	//クラス読み込み
	InputManager* input_ = nullptr;
	AudioManager* audioManager_ = nullptr;
	std::unique_ptr<LightManager>lightManager_;

	std::unique_ptr<Camera>camera_;
	myMath::Vector3 cameraPos_ = {};
	myMath::Vector3 targetPos_ = {};

	std::unique_ptr<GameTimer>gameTimer_;

	std::unique_ptr<GameLevelData> gameLevelData_;
	std::unique_ptr<BuildingManager>buildingManager_;
	std::unique_ptr<GroundBack>groundBack_;

	//制御点
	std::vector<myMath::Vector3> controlPoints_;
	myMath::Vector3 playerPos_ = {};
	myMath::Vector3 frontPos_ = {};
	myMath::Vector3 up_ = { 0,1,0 };//上方向ベクトル
	Transform controlTrans_;

	std::unique_ptr<Model>player_;
	Transform playerTrans_;
	static uint32_t sPlayerTex_;

	std::unique_ptr<PlayerEngineSmokeParticleEmitter>smokeEmitter_;
	Transform smokeTrans_;

	static uint32_t sBgm_;

	static uint32_t sResultTex_;
	std::unique_ptr<Sprite>result_;
	float resultAlpha_ = 0.0f;

public:

	//初期化処理
	void Initialize()override;

	//終了処理
	void Destroy()override;

	//更新処理
	void Update()override;

	//描画処理
	void Draw()override;

	static void LoadAsset();

private:

	void Load(const CameraData& cameraData);

	void SmokeUpdate();
};