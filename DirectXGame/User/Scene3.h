#pragma once
#include"BaseScene.h"
#include"InputManager.h"
#include"DrawOversight.h"
#include"Camera.h"
#include"Collision.h"

class Scene3 :public BaseScene
{
private:

	//�N���X�ǂݍ���
	InputManager* input = nullptr;

	std::unique_ptr<Camera>camera;

	//�V��
	std::unique_ptr<DrawOversight>model;
	Transform modelTrans;
	uint32_t modelTex;

	//���C
	std::unique_ptr<DrawOversight>ray;
	Transform rayTrans;
	uint32_t rayTex;
	Ray rayPos;
	float rayTime;
	myMath::Vector4 color = { 0.0f,0.0f,0.0f ,0.0f };

	//�L���[�u
	std::unique_ptr<DrawOversight>cube;
	Transform cubeTrans;

	//��
	std::unique_ptr<DrawOversight>plane;
	Transform planeTrans;
	uint32_t planeTex = 0;
	Plane planePos;

	myMath::Vector3 cameraPos;
	float angleX = 0.0f;
	float angleY = 0.0f;
	const float length = 50.0f;


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
	void CamUpdate();
};