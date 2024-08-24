#pragma once
#include"DrawOversight.h"
#include"BaseScene.h"
#include"myMath.h"
#include"GameTimer.h"
#include"InputManager.h"
#include"Player.h"

class GameScene:public BaseScene
{
private:

	//クラス読み込み
	InputManager* input_ = nullptr;

	std::unique_ptr<GameTimer>gameTimer_;

	std::unique_ptr<Player>player_;

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


};