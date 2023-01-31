#pragma once

#include"InputManager.h"
#include"AudioManager.h"
#include<memory>
#include"Camera.h"
#include"DrawOversight.h"
#include"Transform.h"
#include"Sprite.h"
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

	//�X�e�[�W�L���[�u
	std::unique_ptr<DrawOversight>cube;
	Transform cubeTrans;
	uint32_t cubeTex;

	//��
	std::unique_ptr<DrawOversight>sphere;
	Transform sphereTrans;
	uint32_t sphereTex;

	//2D�X�v���C�g
	std::unique_ptr<Sprite>sprite;
	uint32_t spriteTex;
	myMath::Vector2 sprite2DPos = { 100.0f ,100.0f };

	//3D�X�v���C�g
	std::unique_ptr<Sprite>sprite3D;
	Transform sprite3DTrans;
	uint32_t sprite3DTex;
	myMath::Vector3 sprite3DPos;

	myMath::Vector3 cameraPos;
	float angleX = 0.0f;
	float angleY = 0.0f;
	const float length = 50.0f;

	uint16_t animationNum = 0;
	float kamiTime = 0.0f;

	float time = 0.0f;

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