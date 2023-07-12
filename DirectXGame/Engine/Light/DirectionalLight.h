#pragma once
#include"myMath.h"

/// <summary>
/// ���C�g
/// </summary>
class DirectionalLight
{
public://�T�u�N���X

	//�萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData
	{
		myMath::Vector4 lightv;//���C�g�ւ̕�����\���x�N�g��
		myMath::Vector3 lightcolor;//���C�g�̐F
		bool active;
	};

private:

	//���C�g��������(�P�ʃx�N�g��)
	myMath::Vector4 lightdir_ = { 1,0,0,0 };
	//���C�g�F
	myMath::Vector3 lightcolor_ = { 1,1,1 };
	//�_�[�e�B�t���O
	bool dirty_ = false;
	//�L���t���O
	bool active_ = false;

public:

	/// <summary>
	/// ���C�g�������Z�b�g
	/// </summary>
	/// <param name="light">���C�g����</param>
	inline void SetLightDir(const myMath::Vector4& lightdir){ lightdir_ = lightdir.normalization(); }
	inline const myMath::Vector4& GetLightDir() { return lightdir_; }

	/// <summary>
	/// ���C�g�F���Z�b�g
	/// </summary>
	/// <param name="lightcolor">���C�g�F</param>
	inline void SetLightColor(const myMath::Vector3& lightcolor) { lightcolor_ = lightcolor; }
	inline const myMath::Vector3& GetLightColor() { return lightcolor_; }

	/// <summary>
	/// �L���t���O���Z�b�g
	/// </summary>
	/// <param name="active">�L���t���O</param>
	inline void SetActive(bool active) { active_ = active; }

	/// <summary>
	/// �L���`�F�b�N
	/// </summary>
	/// <returns>�L���t���O</returns>
	inline bool IsActive() { return active_; }
};