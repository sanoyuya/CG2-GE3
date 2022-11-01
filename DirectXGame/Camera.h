#pragma once
#include"myMath.h"

/// <summary>
/// �J����
/// </summary>
class Camera
{
private:

	float aspect = 0.0f;
	float nearClip = 0.0f;
	float farClip = 0.0f;
	float angle = 0.0f;				//�J�����p�x
	float distance = 50.0f;			//�J��������
	myMath::Matrix4 matView;		//�r���[�s��
	myMath::Matrix4 matViewInverse;	//�t�r���[�s��	
	myMath::Matrix4 matProjection;	//�ˉe�s��
	myMath::Vector3 eye;			//���_���W
	myMath::Vector3 target;			//�����_���W
	myMath::Vector3 up;				//������x�N�g��

	//bool projectionFlag = false;	//���s���e�Ɠ������e��؂�ւ���t���O

public:

	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="projectionFlag">���s���e�Ɠ������e��؂�ւ���t���O</param>
	void Initialize(bool projectionFlag);

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="projectionFlag">���s���e�Ɠ������e��؂�ւ���t���O</param>
	void Update(bool projectionFlag);

	/// <summary>
	/// �r���[�s��̌v�Z
	/// </summary>
	void UpdateMatView();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="projectionFlag">���s���e�Ɠ������e��؂�ւ���t���O</param>
	void UpdateMatProjection(bool projectionFlag);

	//�Q�b�^�[
	const myMath::Matrix4& GetMatView();
	const myMath::Matrix4& GetMatViewInverse();
	const myMath::Matrix4& GetMatProjection();
	const myMath::Vector3& GetEye();
	const myMath::Vector3& GetTarget();
	const myMath::Vector3& GetUp();

	//�Z�b�^�[
	void SetEye(const myMath::Vector3& eye_);
	void SetTarget(const myMath::Vector3& target_);
	void SetUp(const myMath::Vector3& up_);
};