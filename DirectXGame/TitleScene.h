#pragma once
#include"BaseScene.h"
#include"InputManager.h"
#include"SceneManager.h"
#include"SceneChangeAnimation.h"
#include"DrawOversight.h"
#include"AudioManager.h"

//�^�C�g���V�[��
class TitleScene :public BaseScene
{
private:

	//�N���X�ǂݍ���
	InputManager* input = nullptr;
	SceneManager* sceneManager = nullptr;
	AudioManager* audioManager = nullptr;

	std::unique_ptr<Sprite>titleBack;
	uint16_t titleBackTex = 0;

	std::unique_ptr<Sprite>title;
	uint16_t titleTex = 0;

	std::unique_ptr<Sprite>press;
	uint16_t pressTex = 0;

	std::unique_ptr<DrawOversight>model;
	Transform modelPos;
	uint16_t minDiceTex = 0;

	std::unique_ptr<Camera>camera;
	myMath::Vector3 cameraPos;

	float timer = 0.0f;

	uint32_t titleBGM = 0;

public:

	//����������
	void Initialize()override;

	//�X�V����
	void Update()override;

	//�`�揈��
	void Draw()override;

	//�I������
	void Destroy()override;
};