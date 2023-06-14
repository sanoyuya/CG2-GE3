#pragma once
#include"myMath.h"
#include"WindowsApp.h"

/// <summary>
/// �J����
/// </summary>
class Camera
{
private:

	static float sWidth_;
	static float sHeight_;

	float aspect_ = 0.0f;
	float nearClip_ = 0.0f;
	float farClip_ = 0.0f;
	float angle_ = 0.0f;				//�J�����p�x
	float distance_ = 50.0f;			//�J��������
	myMath::Matrix4 matView_;		//�r���[�s��
	myMath::Matrix4 matViewInverse_;	//�t�r���[�s��	
	myMath::Matrix4 matProjection_;	//�ˉe�s��
	myMath::Vector3 eye_;			//���_���W
	myMath::Vector3 target_;			//�����_���W
	myMath::Vector3 up_;				//������x�N�g��

	//bool projectionFlag = false;	//���s���e�Ɠ������e��؂�ւ���t���O

public:

	static void StaticInitialize(WindowsApp* windowsApp);

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
	/// ���e�v�Z
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
	void SetEye(const myMath::Vector3& eye);
	void SetTarget(const myMath::Vector3& target);
	void SetUp(const myMath::Vector3& up);
	void SetNearClip(const float nearClip);
	void SetFarClip(const float farClip);
};