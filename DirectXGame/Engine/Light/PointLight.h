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
		uint8_t active;
	};

private://�����o�ϐ�

	//���C�g���W(���[���h���W�n)
	myMath::Vector3 lightPos_ = { 0,0,0 };
	//���C�g�̐F
	myMath::Vector3 lightColor_ = { 1,1,1 };
	//���C�g���������W��
	myMath::Vector3 lightAtten_ = { 1.0f,1.0f ,1.0f };
	//�L���t���O
	bool active_ = false;

public://�����o�֐�

	inline void SetLightPos(const myMath::Vector3& lightPos) { lightPos_ = lightPos; }
	inline const myMath::Vector3& GetLightPos() { return lightPos_; }
	inline void SetLightColor(const myMath::Vector3& lightColor) { lightColor_ = lightColor; }
	inline const myMath::Vector3& GetLightColor() { return lightColor_; }
	inline void SetLightAtten(const myMath::Vector3& lightAtten) { lightAtten_ = lightAtten; }
	inline const myMath::Vector3& GetLightAtten() { return lightAtten_; }
	inline void SetActive(bool active) { active_ = active; }
	inline bool IsActive() { return active_; }
};