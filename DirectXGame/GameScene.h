#pragma once
#include"InputManager.h"
#include<memory>
//#include"Sprite.h"

class GameScene
{
private:

	//�N���X�ǂݍ���
	InputManager* input = nullptr;
	//Sprite* sprite = nullptr;

	int hoge = 0;

public:
	GameScene();
	~GameScene();
	void Initialize();
	void Update();
	void Draw();

	//�V���O���g��
	static GameScene* GetInstance();
};