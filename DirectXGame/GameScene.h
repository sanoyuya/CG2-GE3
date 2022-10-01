#pragma once
#include"Input.h"

class GameScene
{
private:

	//クラス読み込み
	Input* input = nullptr;

public:
	GameScene();
	~GameScene();
	void Initialize();
	void Update();
	void Draw();

	//ゲッター
	static GameScene* GetInstance();
};