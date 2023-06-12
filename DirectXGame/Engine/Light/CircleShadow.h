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
	myMath::Vector4 dir_ = { 1,0,0,0 };
	//�L���X�^�[�ƃ��C�g�̋���
	float distanceCasterLight_ = 100.0f;
	//�L���X�^�[���W(���[���h���W�n)
	myMath::Vector3 casterPos_ = { 0,0,0 };
	//���������W��
	myMath::Vector3 atten_ = { 0.5f,0.6f,0.0f };
	//�����p�x
	myMath::Vector2 factorAngleCos_ = { 0.2f,0.5f };
	//�L���t���O
	bool active_ = false;

public://�����o�֐�

	inline void SetDir(const myMath::Vector4& dir) { dir_ = dir.normalization(); }
	inline const myMath::Vector4& GetDir() { return dir_; }
	inline void SetCasterPos(const myMath::Vector3& casterPos) { casterPos_ = casterPos; }
	inline const myMath::Vector3& GetCasterPos() { return casterPos_; }
	inline void SetDistanceCasterLight(float distanceCasterlight) { distanceCasterLight_ = distanceCasterlight; }
	inline float GetDistanceCasterLight() { return distanceCasterLight_; }
	inline void SetAtten(const myMath::Vector3& atten) { atten_ = atten; }
	inline const myMath::Vector3& GetAtten() { return atten_; }
	inline void SetFactorAngle(const myMath::Vector2& factorAngleCos)
	{
		factorAngleCos_.x = cosf(DirectX::XMConvertToRadians(factorAngleCos.x));
		factorAngleCos_.y = cosf(DirectX::XMConvertToRadians(factorAngleCos.y));
	}
	inline const myMath::Vector2& GetFactorAngleCos() { return factorAngleCos_; }
	inline void SetActive(bool active) { active_ = active; }
	inline bool IsActive() { return active_; }
};