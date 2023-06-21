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
	InputManager* input_ = nullptr;
	AudioManager* audioManager_ = nullptr;

	std::unique_ptr<Camera>camera_;

	//�V��
	std::unique_ptr<Model>skyDome_;
	Transform skyDomeTrans_;
	uint32_t skyDomeTex_;

	myMath::Vector3 cameraPos_;
	float angleX_ = 0.0f;
	float angleY_ = 0.0f;
	const float length_ = 50.0f;

	std::map<std::string, EditorObject*>models_;
	std::vector<std::unique_ptr<EditorObject>>objects_;

	myMath::Vector3 pos_;
	float time_ = 0.0f;

	uint32_t playerTex_ = 0;
	uint32_t sphereTex_ = 0;
	uint32_t tex_ = 0;

	uint32_t bgm_ = 0;

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
	void LevelDataInitialize();
};