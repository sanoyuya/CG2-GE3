#pragma once
#include"InputManager.h"

class GameScene
{
private:

	//�N���X�ǂݍ���
	InputManager* input = nullptr;

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