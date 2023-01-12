#pragma once
#include"BaseScene.h"
#include"InputManager.h"
#include"SceneManager.h"
#include"SceneChangeAnimation.h"

//�^�C�g���V�[��
class TitleScene :public BaseScene
{
private:

	//�N���X�ǂݍ���
	InputManager* input = nullptr;
	SceneManager* sceneManager = nullptr;

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