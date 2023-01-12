#pragma once
#include"BaseScene.h"
#include"InputManager.h"
#include"SceneManager.h"
#include"Score.h"
#include"SceneChangeAnimation.h"

class ResultScene :public BaseScene
{
private:

	//�N���X�ǂݍ���
	InputManager* input = nullptr;
	SceneManager* sceneManager = nullptr;
	Score* score = nullptr;

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

