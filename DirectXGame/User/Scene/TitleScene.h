#pragma once
#include"BaseScene.h"
#include"InputManager.h"
#include"DrawOversight.h"
#include"Camera.h"
#include"AudioManager.h"
#include"Collision.h"
#include"LightManager.h"
#include"ParticleEmitter.h"
#include"EnemyDeathParticleEmitter.h"

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
	uint32_t skyDomeTex_;

	myMath::Vector3 cameraPos_;

	uint32_t bgm_ = 0;

	uint32_t titleTex_ = 0;
	std::unique_ptr<Sprite>title_;

	float time_ = 0.0f;
	myMath::Vector2 position_ = { 640.0f,0.0f };

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
	
	void camUpdate();
};