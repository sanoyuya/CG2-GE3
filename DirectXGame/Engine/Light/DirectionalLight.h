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
	myMath::Vector4 lightdir = { 1,0,0,0 };
	//���C�g�F
	myMath::Vector3 lightcolor = { 1,1,1 };
	//�_�[�e�B�t���O
	bool dirty = false;
	//�L���t���O
	bool active = false;

public:

	/// <summary>
	/// ���C�g�������Z�b�g
	/// </summary>
	/// <param name="light">���C�g����</param>
	inline void SetLightDir(const myMath::Vector4& lightdir_){ lightdir = lightdir_.normalization(); }
	inline const myMath::Vector4& GetLightDir() { return lightdir; }

	/// <summary>
	/// ���C�g�F���Z�b�g
	/// </summary>
	/// <param name="lightcolor">���C�g�F</param>
	inline void SetLightColor(const myMath::Vector3& lightcolor_) { lightcolor = lightcolor_; }
	inline const myMath::Vector3& GetLightColor() { return lightcolor; }

	/// <summary>
	/// �L���t���O���Z�b�g
	/// </summary>
	/// <param name="active">�L���t���O</param>
	inline void SetActive(bool active_) { active = active_; }

	/// <summary>
	/// �L���`�F�b�N
	/// </summary>
	/// <returns>�L���t���O</returns>
	inline bool IsActive() { return active; }
};