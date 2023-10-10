#pragma once
#include"BaseScene.h"
#include"InputManager.h"
#include"DrawOversight.h"
#include"Camera.h"
#include"AudioManager.h"

class GameClearScene :public BaseScene
{
private:

	//クラス読み込み
	InputManager* input_ = nullptr;
	AudioManager* audioManager_ = nullptr;
	std::unique_ptr<LightManager>lightManager_;

	std::unique_ptr<Camera>camera_;

	//天球
	std::unique_ptr<Model>skyDome_;
	Transform skyDomeTrans_;
	uint32_t skyDomeTex_;

	myMath::Vector3 cameraPos_;
	float angleX_ = 0.0f;
	float angleY_ = 0.0f;
	const float length_ = 50.0f;

	uint32_t bgm_ = 0;

	uint32_t resultTex_ = 0;
	std::unique_ptr<Sprite>result_;

public:

	//初期化処理
	void Initialize()override;

	//終了処理
	void Destroy()override;

	//更新処理
	void Update()override;

	//描画処理
	void Draw()override;
};