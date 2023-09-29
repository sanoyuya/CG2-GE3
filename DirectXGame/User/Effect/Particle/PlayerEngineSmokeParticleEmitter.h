#pragma once
#include"ParticleBase.h"

class PlayerEngineSmokeParticleEmitter :public ParticleBase
{
private:

	std::unique_ptr<ParticleManager>particleMan_;
	uint32_t tex_;

public:

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerEngineSmokeParticleEmitter() = default;

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ��������
	/// </summary>
	/// <param name="center">���S���W</param>
	void Create(const myMath::Vector3 center);

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="camera">�J�����̃|�C���^</param>
	void Update(Camera* camera);

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();
};