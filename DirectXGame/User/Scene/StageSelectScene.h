#pragma once
#include"DrawOversight.h"
#include"BaseScene.h"
#include"Retention.h"
#include"InputManager.h"

class StageSelectScene :public BaseScene
{
private:

	//クラス読み込み
	InputManager* input_ = nullptr;

	std::unique_ptr<Sprite>sprite_;
	uint32_t spriteTex_ = 0;
	float angle_ = 0.0f;

	uint16_t stageNum_ = 0;
	const uint16_t minStage = 0;
	const uint16_t maxStage = 3;

	std::unique_ptr<Sprite>stageNumSprite_;
	uint32_t stageNumSpriteTex_ = 0;

public:

	//初期化処理
	void Initialize()override;

	//終了処理
	void Destroy()override;

	//更新処理
	void Update()override;

	//描画処理
	void Draw()override;

private:

	void Select();
};