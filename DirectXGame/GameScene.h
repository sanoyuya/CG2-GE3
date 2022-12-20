#pragma once

#include"InputManager.h"
#include"AudioManager.h"
#include<memory>
#include"Camera.h"
#include"DrawOversight.h"
#include"Transform.h"
#include"Sprite.h"

class GameScene
{
private:

	//�N���X�ǂݍ���
	InputManager* input = nullptr;
	AudioManager* audioManager = nullptr;

	std::unique_ptr<Camera>camera;

	//�V��
	std::unique_ptr<DrawOversight>model;
	Transform modelTrans;
	uint32_t modelTex;

	//�X�e�[�W�L���[�u
	std::unique_ptr<DrawOversight>cube;
	Transform cubeTrans;
	uint32_t cubeTex;

	//��
	std::unique_ptr<DrawOversight>sphere;
	Transform sphereTrans;
	uint32_t sphereTex;

	std::unique_ptr<Sprite>sprite;
	uint32_t spriteTex;

	myMath::Vector3 cameraPos;
	float angleX = 0.0f;
	float angleY = 0.0f;
	const float length = 50.0f;

	uint8_t scene = 0;

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

private:
	void Rotation();
	void CamMove();
	void Reset();
};