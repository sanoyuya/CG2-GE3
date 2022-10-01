#pragma once
#include"Input.h"

class GameScene
{
private:

	//クラス読み込み
	Input* input = nullptr;

	int hoge = 0;

public:
	GameScene();
	~GameScene();
	void Initialize();
	void Update();
	void Draw();

	//シングルトン
	static GameScene* GetInstance();
};