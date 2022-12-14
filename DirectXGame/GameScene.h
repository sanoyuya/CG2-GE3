#pragma once

#include"InputManager.h"
#include"AudioManager.h"
#include<memory>
#include"Camera.h"
#include"DrawOversight.h"
#include"Transform.h"

class GameScene
{
private:

	//�N���X�ǂݍ���
	InputManager* input = nullptr;
	AudioManager* audioManager = nullptr;

	std::unique_ptr<Camera>camera;

	std::unique_ptr<DrawOversight>kami;
	uint32_t kamiTex = 0;
	uint16_t kamiNum = 0;
	float kamiTime = 0.0f;
	myMath::Vector2 hoge = { 0,0 };

	//�E���̃p�b�P�[�W�^�C�g��
	std::unique_ptr<DrawOversight>violet;
	uint32_t violetTex = 0;

	//����̃|�P����
	std::unique_ptr<DrawOversight>poke;
	uint32_t pokeTex = 0;
	float flame = 0.0f;
	uint16_t pokeNum = 0;

	//�V��
	std::unique_ptr<DrawOversight>model;
	Transform modelTrans;
	uint32_t modelTex;

	//�퓬�@�̂��
	std::unique_ptr<DrawOversight>fModel;
	Transform fModelTrans;
	uint32_t fModelTex;
	uint32_t fModel2Tex;
	float angle = 0.0f;

	myMath::Vector3 cameraPos;

	//uint32_t titleBGM = 0;

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