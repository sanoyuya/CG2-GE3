#pragma once
#include"BaseScene.h"
#include"InputManager.h"

//�^�C�g���V�[��
class TitleScene :public BaseScene
{
private:

	//�N���X�ǂݍ���
	InputManager* input = nullptr;

public:

	//����������
	void Initialize()override;

	//�I������
	void Destroy()override;

	//�X�V����
	void Update()override;

	//�`�揈��
	void Draw()override;
};