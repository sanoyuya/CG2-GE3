#pragma once
#include"Camera.h"

//�I�u�W�F�N�g���N���X
class GameObject
{
public:

	virtual ~GameObject() = default;

	//����������
	virtual void Initialize() = 0;

	//�X�V����
	virtual void Update() = 0;

	//�`�揈��
	virtual void Draw() = 0;

	//�I�u�W�F�N�g�̖��O�擾����
	virtual std::string GetName() = 0;
};