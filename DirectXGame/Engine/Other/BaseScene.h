#pragma once

//�V�[�����N���X
class BaseScene
{
public:

	virtual ~BaseScene() = default;

	//����������
	virtual void Initialize() = 0;

	//�I������
	virtual void Destroy() = 0;

	//�X�V����
	virtual void Update() = 0;

	//�`�揈��
	virtual void Draw() = 0;
};