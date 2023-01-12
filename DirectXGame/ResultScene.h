#pragma once
#include"BaseScene.h"
#include"InputManager.h"
#include"SceneManager.h"
#include"Score.h"
#include"SceneChangeAnimation.h"
#include"AudioManager.h"

class ResultScene :public BaseScene
{
private:

	//クラス読み込み
	InputManager* input = nullptr;
	SceneManager* sceneManager = nullptr;
	AudioManager* audioManager = nullptr;

	Score* score = nullptr;

	std::unique_ptr<Sprite>resultBack;
	uint16_t resultBackTex = 0;

	std::unique_ptr<Sprite>thanks;
	uint16_t thanksTex = 0;

	std::unique_ptr<Sprite>press;
	uint16_t pressTex = 0;

	float timer = 0.0f;

	uint32_t resultBGM = 0;

public:

	//初期化処理
	void Initialize()override;

	//更新処理
	void Update()override;

	//描画処理
	void Draw()override;

	//終了処理
	void Destroy()override;
};