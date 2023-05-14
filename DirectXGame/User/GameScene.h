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
	std::unique_ptr<Model>model;
	Transform modelTrans;
	uint32_t modelTex;

	//Phong��
	std::unique_ptr<Model>sphere;
	Transform sphereTrans;
	uint32_t sphereTex;
	uint32_t sphereTex2;
	Sphere spherePos;
	float sphereTime;
	myMath::Vector4 color = { 0.5f,0.0f,0.0f ,1.0f };
	bool texFlag = false;

	//Toon��
	std::unique_ptr<Model>sphere2;
	Transform sphere2Trans;
	uint32_t sphere2Tex = 0;

	//�������C�g��
	std::unique_ptr<Model>sphere3;
	Transform sphere3Trans;

	std::unique_ptr<Model>lightSphere;
	Transform lightSphereTrans;
	bool lightDisplayFlag = false;

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