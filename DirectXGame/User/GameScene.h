#pragma once

#include"InputManager.h"
#include"AudioManager.h"
#include"Camera.h"
#include"DrawOversight.h"
#include"BaseScene.h"

class GameScene :public BaseScene
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

	std::unique_ptr<DrawOversight>object;
	Transform objectTrans;
	uint32_t cubeTex;
	uint32_t objectTex;
	myMath::Vector4 objectColor = {};
	bool texFlag = false;

	std::unique_ptr<DrawOversight>object2;
	Transform objectTrans2;

	//��
	std::unique_ptr<DrawOversight>sphere;
	Transform sphereTrans;
	uint32_t sphereTex;

	myMath::Vector3 cameraPos;
	float angleX = 0.0f;
	float angleY = 0.0f;
	const float length = 50.0f;

	float time = 0.0f;

	uint32_t bgm = 0;
	float bgmVolume = 0.0f;
	bool bgmFlag = false;

public:

	//����������
	void Initialize()override;

	//�I������
	void Destroy()override;

	//�X�V����
	void Update()override;

	//�`�揈��
	void Draw()override;

private:
	void Rotation();
	void CamMove();
	void Reset();
};