#pragma once
#include"BaseScene.h"
#include"InputManager.h"
#include"SceneManager.h"
#include"Score.h"
#include"SceneChangeAnimation.h"

class ResultScene :public BaseScene
{
private:

	//クラス読み込み
	InputManager* input = nullptr;
	SceneManager* sceneManager = nullptr;
	Score* score = nullptr;

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

