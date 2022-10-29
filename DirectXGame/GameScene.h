#pragma once
#include"InputManager.h"
#include<memory>
//#include"Sprite.h"

class GameScene
{
private:

	//クラス読み込み
	InputManager* input = nullptr;
	//Sprite* sprite = nullptr;

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