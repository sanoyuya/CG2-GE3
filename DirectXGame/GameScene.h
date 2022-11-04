#pragma once

#include"InputManager.h"
#include"AudioManager.h"
#include<memory>
#include"Camera.h"
#include"Sprite.h"
#include"TextureManager.h"
#include"DrawManager.h"

class GameScene
{
private:

	//�N���X�ǂݍ���
	InputManager* input = nullptr;
	AudioManager* audioManager = nullptr;

	std::unique_ptr<Camera>camera;

	std::unique_ptr<DrawManager>draw;
	TextureData tex;
	std::unique_ptr<DrawManager>draw2;
	TextureData tex2;

	uint32_t titleBGM;

	float angle = 0.0f;
	myMath::Vector2 hoge = { 0,0 };

	float timeY = 0;

public:
	GameScene();
	~GameScene();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();
};