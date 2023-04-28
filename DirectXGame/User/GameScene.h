#pragma once

#include"InputManager.h"
#include"AudioManager.h"
#include"Camera.h"
#include"DrawOversight.h"
#include"BaseScene.h"
#include"Collision.h"
#include"LightManager.h"

class GameScene :public BaseScene
{
private:

	//�N���X�ǂݍ���
	InputManager* input = nullptr;
	AudioManager* audioManager = nullptr;

	std::unique_ptr<Camera>camera;
	std::unique_ptr<LightManager>lightManager;
	myMath::Vector3 lightPos = { 0.0f,0.0f ,0.0f };
	myMath::Vector3 lightColor = { 0.0f,0.0f ,0.0f };
	myMath::Vector3 lightAtten = { 0.0f,0.0f ,0.0f };

	//�V��
	std::unique_ptr<DrawOversight>model;
	Transform modelTrans;
	uint32_t modelTex;

	//��
	std::unique_ptr<DrawOversight>sphere;
	Transform sphereTrans;
	uint32_t sphereTex;
	uint32_t sphereTex2;
	Sphere spherePos;
	float sphereTime;
	myMath::Vector4 color = { 0.0f,1.0f,1.0f ,1.0f };

	//�O�p�`
	std::unique_ptr<DrawOversight>triangle;
	Triangle trianglePos;
	Transform triangleTrans;
	uint32_t triangleTex = 0;

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
	void CamMove();
	void ImGuiUpdate();
};