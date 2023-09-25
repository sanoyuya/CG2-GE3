#pragma once

/// <summary>
/// �X�e�[�W�̃x�[�X
/// </summary>
class BaseStage
{
public:

	virtual ~BaseStage() = default;

	//����������
	virtual void Initialize() = 0;

	//�I������
	virtual void Destroy() = 0;

	//�X�V����
	virtual void Update() = 0;

	//�`�揈��
	virtual void Draw() = 0;
};