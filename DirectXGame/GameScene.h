#pragma once

#include"InputManager.h"
#include"AudioManager.h"
#include<memory>
#include"Camera.h"
#include"Sprite.h"
#include"TextureManager.h"
#include"DrawOversight.h"

class GameScene
{
private:

	//�N���X�ǂݍ���
	InputManager* input = nullptr;
	AudioManager* audioManager = nullptr;

	std::unique_ptr<Camera>camera;

	std::unique_ptr<DrawOversight>draw;
	TextureData tex;
	std::unique_ptr<DrawOversight>draw2;
	TextureData tex2;
	std::unique_ptr<DrawOversight>draw3;
	TextureData tex3;
	std::unique_ptr<DrawOversight>draw4;
	TextureData tex4;
	float flame = 0.0f;
	uint16_t num = 0;

	uint32_t titleBGM;

	float angle = 0.0f;
	myMath::Vector2 hoge = { 0,0 };

	float aTime = 0.0f;
	float reimuTime = 0.0f;

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