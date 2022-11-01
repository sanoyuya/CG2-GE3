#pragma once
#include"InputManager.h"
#include<memory>
#include"Camera.h"
#include"Sprite.h"
#include"TextureManager.h"

class GameScene
{
private:

	//�N���X�ǂݍ���
	InputManager* input = nullptr;
	std::unique_ptr<Camera>camera;

	TextureData tex;
	std::unique_ptr<Sprite>sprite;
	TextureData tex2;
	std::unique_ptr<Sprite>sprite2;

	float angle = 0.0f;
	myMath::Vector2 hoge = { 0,0 };

public:
	GameScene();
	~GameScene();
	void Initialize();
	void Update();
	void Draw();

	//�V���O���g��
	static GameScene* GetInstance();
};