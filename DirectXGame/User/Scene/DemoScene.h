#pragma once
#include"DrawOversight.h"
#include"BaseScene.h"
#include"InputManager.h"
#include"AudioManager.h"

class DemoScene:public BaseScene
{
private:

	//クラス読み込み
	InputManager* input_ = nullptr;
	AudioManager* audioManager_ = nullptr;

	std::unique_ptr<Camera>camera_;

	//天球
	std::unique_ptr<Model>skyDome_;
	Transform skyDomeTrans_;
	uint32_t skyDomeTex_;

	std::unique_ptr<Sprite>sprite_;
	uint32_t spriteTex_ = 0;
	float angle_ = 0.0f;

	std::unique_ptr<Model>model_;
	Transform modelTrans_;
	uint32_t modelTex_;

	std::unique_ptr<Model>point_;
	Transform pointTrans_;
	uint32_t pointTex_;

	myMath::Vector3 baseVec_ = { 0,0,1 };
	myMath::Vector3 frontVec_ = {};

	float flame_;
	uint16_t num_ = 0;

public:

	//初期化処理
	void Initialize()override;

	//終了処理
	void Destroy()override;

	//更新処理
	void Update()override;

	//描画処理
	void Draw()override;

	void ImGuiUpdate();
};

