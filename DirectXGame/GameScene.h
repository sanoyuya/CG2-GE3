#pragma once
#include"Input.h"

class GameScene
{
private:

	//�N���X�ǂݍ���
	Input* input = nullptr;

public:
	GameScene();
	~GameScene();
	void Initialize();
	void Update();
	void Draw();

	//�Q�b�^�[
	static GameScene* GetInstance();
};