#pragma once
#include"InputManager.h"

class GameScene
{
private:

	//クラス読み込み
	InputManager* input = nullptr;

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