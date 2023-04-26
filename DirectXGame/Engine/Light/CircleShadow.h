#pragma once
#include"myMath.h"

/// <summary>
/// �ۉe
/// </summary>
class CircleShadow
{
public://�T�u�N���X

	//�萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData
	{
		myMath::Vector4 dir;
		myMath::Vector3 casterPos;
		float distanceCasterLight;
		myMath::Vector3 atten;
		float pad3;
		myMath::Vector2 factorAngleCos;
		bool active;
		float pad4;
	};

private://�����o�ϐ�
	//����(�P�ʃx�N�g��)
	myMath::Vector4 dir = { 1,0,0,0 };
	//�L���X�^�[�ƃ��C�g�̋���
	float distanceCasterLight = 100.0f;
	//�L���X�^�[���W(���[���h���W�n)
	myMath::Vector3 casterPos = { 0,0,0 };
	//���������W��
	myMath::Vector3 atten = { 0.5f,0.6f,0.0f };
	//�����p�x
	myMath::Vector2 factorAngleCos = { 0.2f,0.5f };
	//�L���t���O
	bool active = false;

public://�����o�֐�
	inline void SetDir(const myMath::Vector4& dir_) { dir = dir_.normalization(); }
	inline const myMath::Vector4& GetDir() { return dir; }
	inline void SetCasterPos(const myMath::Vector3& casterPos_) { casterPos = casterPos_; }
	inline const myMath::Vector3& GetCasterPos() { return casterPos; }
	inline void SetDistanceCasterLight(float distanceCasterlight_) { distanceCasterLight = distanceCasterlight_; }
	inline float GetDistanceCasterLight() { return distanceCasterLight; }
	inline void SetAtten(const myMath::Vector3& atten_) { atten = atten_; }
	inline const myMath::Vector3& GetAtten() { return atten; }
	inline void SetFactorAngle(const myMath::Vector2& factorAngleCos_)
	{
		factorAngleCos.x = cosf(DirectX::XMConvertToRadians(factorAngleCos_.x));
		factorAngleCos.y = cosf(DirectX::XMConvertToRadians(factorAngleCos_.y));
	}
	inline const myMath::Vector2& GetFactorAngleCos() { return factorAngleCos; }
	inline void SetActive(bool active_) { active = active_; }
	inline bool IsActive() { return active; }
};