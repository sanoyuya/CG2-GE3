#pragma once
#include"BaseScene.h"
#include"InputManager.h"
#include"DrawOversight.h"
#include"Camera.h"
#include"AudioManager.h"
#include"Collision.h"
#include"LevelEditor.h"
#include <map>
#include"EditorObject.h"

//�^�C�g���V�[��
class TitleScene :public BaseScene
{
private:

	//�N���X�ǂݍ���
	InputManager* input = nullptr;
	AudioManager* audioManager = nullptr;

	std::unique_ptr<Camera>camera;

	//�V��
	std::unique_ptr<Model>skyDome;
	Transform skyDomeTrans;
	uint32_t skyDomeTex;

	myMath::Vector3 cameraPos;
	float angleX = 0.0f;
	float angleY = 0.0f;
	const float length = 50.0f;

	std::unique_ptr<LevelData> levelData = nullptr;
	std::map<std::string, EditorObject*>models;
	std::vector<std::unique_ptr<EditorObject>>objects;

	myMath::Vector3 pos;
	float time = 0.0f;

	uint32_t playerTex = 0;
	uint32_t sphereTex = 0;
	uint32_t tex = 0;

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
	
	void Move();
	void camUpdate();
};