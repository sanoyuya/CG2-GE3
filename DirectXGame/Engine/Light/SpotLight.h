#pragma once
#include"myMath.h"

/// <summary>
/// �X�|�b�g���C�g
/// </summary>
class SpotLight
{
public://�T�u�N���X

	//�萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData
	{
		myMath::Vector4 lightv;
		myMath::Vector3 lightPos;
		float pad1;
		myMath::Vector3 lightColor;
		float pad2;
		myMath::Vector3 lightAtten;
		float pad3;
		myMath::Vector2 lightActorAngleCos;
		bool active;
		float pad4;
	};

private://�����o�ϐ�

	//���C�g����(�P�ʃx�N�g��)
	myMath::Vector4 lightDir = { 1,0,0,0 };
	//���C�g���W(���[���h���W�n)
	myMath::Vector3 lightPos = { 0,0,0 };
	//���C�g�̐F
	myMath::Vector3 lightColor = { 1,1,1 };
	//���C�g���������W��
	myMath::Vector3 lightAtten = { 1.0f,1.0f ,1.0f };
	//���C�g�����p�x(�J�n�p�x�A�I���p�x)
	myMath::Vector2 lightFactorAngleCos = { 0.5f,0.2f };
	//�L���t���O
	bool active = false;

public://�����o�֐�

	inline void SetLightDir(const myMath::Vector4& lightDir_) { lightDir = lightDir_.normalization(); }
	inline const myMath::Vector4& GetLightDir() { return lightDir; }
	inline void SetLightPos(const myMath::Vector3& lightPos_) { lightPos = lightPos_; }
	inline const myMath::Vector3& GetLightPos() { return lightPos; }
	inline void SetLightColor(const myMath::Vector3& lightColor_) { lightColor = lightColor_; }
	inline const myMath::Vector3& GetLightColor() { return lightColor; }
	inline void SetLightAtten(const myMath::Vector3& lightAtten_) { lightAtten = lightAtten_; }
	inline const myMath::Vector3& GetLightAtten() { return lightAtten; }
	inline void SetLightFactorAngle(const myMath::Vector2& lightFactorAngle_)
	{
		lightFactorAngleCos.x = cosf(DirectX::XMConvertToRadians(lightFactorAngle_.x));
		lightFactorAngleCos.y = cosf(DirectX::XMConvertToRadians(lightFactorAngle_.y));
	}
	inline const myMath::Vector2& GetLightFactorAngleCos() { return lightFactorAngleCos; }
	inline void SetActive(bool active_) { active = active_; }
	inline bool IsActive() { return active; }
};