#pragma once
#include"BaseScene.h"
#include"InputManager.h"
#include"DrawOversight.h"
#include"Camera.h"
#include"AudioManager.h"
#include"LightManager.h"
#include"PlayerEngineSmokeParticleEmitter.h"

//タイトルシーン
class TitleScene :public BaseScene
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
	static uint32_t sSkyDomeTex_;

	myMath::Vector3 cameraPos_;

	static uint32_t sBgm_;

	static uint32_t sTitleTex_;
	std::unique_ptr<Sprite>title_;

	static uint32_t sPressButtonTex_;
	std::unique_ptr<Sprite>pressButton_;

	float time_ = 0.0f;
	myMath::Vector2 position_ = { 640.0f,0.0f };

	std::unique_ptr<Model>player_;
	Transform playerTrans_;
	static uint32_t sPlayerTex_;

	std::unique_ptr<PlayerEngineSmokeParticleEmitter>smokeEmitter_;
	Transform smokeTrans_;

	bool animationFlag_ = false;
	uint8_t animationTime_ = 0;

	static uint32_t sAnimationBoxTex_;
	std::array<std::unique_ptr<Sprite>,2>animationBox_;
	float animationBoxScale_ = 0.0f;

	std::array<std::unique_ptr<Model>, 5>cloud_;
	std::array<Transform, 5>cloudTrans_;
	static uint32_t sCloudTex_;

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

	void SmokeUpdate();

	void PlayerUpdate();
};