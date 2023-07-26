#pragma once
#include"ParticleManager.h"

class ParticleBase
{
public:

	/// <summary>
	/// ���N���X�̃f�X�g���N�^
	/// </summary>
	virtual ~ParticleBase() = default;

	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize() = 0;

	/// <summary>
	/// ��������
	/// </summary>
	/// <param name="center">���S���W</param>
	virtual void Create(const myMath::Vector3 center) = 0;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="camera">�J�����̃|�C���^</param>
	virtual void Update(Camera* camera) = 0;

	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Draw() = 0;
};