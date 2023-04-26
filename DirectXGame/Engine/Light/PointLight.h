#pragma once
#include"myMath.h"

/// <summary>
/// �_����
/// </summary>
class PointLight
{
public://�T�u�N���X

	//�萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData
	{
		myMath::Vector3 lightPos;
		float pad1;
		myMath::Vector3 lightColor;
		float pad2;
		myMath::Vector3 lightAtten;
		unsigned int active;
	};

private://�����o�ϐ�
	//���C�g���W(���[���h���W�n)
	myMath::Vector3 lightPos = { 0,0,0 };
	//���C�g�̐F
	myMath::Vector3 lightColor = { 1,1,1 };
	//���C�g���������W��
	myMath::Vector3 lightAtten = { 1.0f,1.0f ,1.0f };
	//�L���t���O
	bool active = false;

public://�����o�֐�

	inline void SetLightPos(const myMath::Vector3& lightPos_) { lightPos = lightPos_; }
	inline const myMath::Vector3& GetLightPos() { return lightPos; }
	inline void SetLightColor(const myMath::Vector3& lightColor_) { lightColor = lightColor_; }
	inline const myMath::Vector3& GetLightColor() { return lightColor; }
	inline void SetLightAtten(const myMath::Vector3& lightAtten_) { lightAtten = lightAtten_; }
	inline const myMath::Vector3& GetLightAtten() { return lightAtten; }
	inline void SetActive(bool active_) { active = active_; }
	inline bool IsActive() { return active; }
};