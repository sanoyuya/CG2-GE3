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
	myMath::Vector4 lightDir_ = { 1,0,0,0 };
	//���C�g���W(���[���h���W�n)
	myMath::Vector3 lightPos_ = { 0,0,0 };
	//���C�g�̐F
	myMath::Vector3 lightColor_ = { 1,1,1 };
	//���C�g���������W��
	myMath::Vector3 lightAtten_ = { 1.0f,1.0f ,1.0f };
	//���C�g�����p�x(�J�n�p�x�A�I���p�x)
	myMath::Vector2 lightFactorAngleCos_ = { 0.5f,0.2f };
	//�L���t���O
	bool active_ = false;

public://�����o�֐�

	inline void SetLightDir(const myMath::Vector4& lightDir) { lightDir_ = lightDir.normalization(); }
	inline const myMath::Vector4& GetLightDir() { return lightDir_; }
	inline void SetLightPos(const myMath::Vector3& lightPos) { lightPos_ = lightPos; }
	inline const myMath::Vector3& GetLightPos() { return lightPos_; }
	inline void SetLightColor(const myMath::Vector3& lightColor) { lightColor_ = lightColor; }
	inline const myMath::Vector3& GetLightColor() { return lightColor_; }
	inline void SetLightAtten(const myMath::Vector3& lightAtten) { lightAtten_ = lightAtten; }
	inline const myMath::Vector3& GetLightAtten() { return lightAtten_; }
	inline void SetLightFactorAngle(const myMath::Vector2& lightFactorAngle)
	{
		lightFactorAngleCos_.x = cosf(DirectX::XMConvertToRadians(lightFactorAngle.x));
		lightFactorAngleCos_.y = cosf(DirectX::XMConvertToRadians(lightFactorAngle.y));
	}
	inline const myMath::Vector2& GetLightFactorAngleCos() { return lightFactorAngleCos_; }
	inline void SetActive(bool active) { active_ = active; }
	inline bool IsActive() { return active_; }
};