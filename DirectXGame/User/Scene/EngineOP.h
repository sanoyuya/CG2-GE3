#pragma once
#include"DrawOversight.h"
#include"BaseScene.h"
#include"myMath.h"

class EngineOP :public BaseScene
{
private:

	std::unique_ptr<Sprite>engineLogo_;
	uint32_t engineLogoTex_ = 0;
	myMath::Vector2 center_ = { 640,360 };
	myMath::Vector4 logoColor_ = { 0.0f,0.0f,0.0f,0.0f };

	std::unique_ptr<Sprite>back_;
	uint32_t backTex_ = 0;

	//アニメーション関連
	uint16_t animationTimer_ = 0;
	uint16_t animationEndTime_ = 180;

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