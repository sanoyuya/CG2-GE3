#pragma once
#include<memory>
#include"myMath.h"
#include"Camera.h"
#include"ConstantBuffer.h"
#include"DrawCommon.h"

class Transform
{
private:

	// �萔�o�b�t�@
	std::shared_ptr<ConstantBuffer> constBuff_;
	//�萔�o�b�t�@�̃}�b�s���O�p�|�C���^
	worldViewpojCamera constBuffMap_;

	//�������p�̃r���[�s��v�Z
	static myMath::Matrix4 sDefaultViewMat_;

	//�������p�̃v���W�F�N�V�����s��v�Z
	static myMath::Matrix4 sDefaultProjectionMat_;

public:

	// ���[�J�����W
	myMath::Vector3 translation = { 0.0f, 0.0f, 0.0f };
	// X,Y,Z�����̃��[�J����]�p
	myMath::Vector3 rotation = { 0.0f, 0.0f, 0.0f };
	// ���[�J���X�P�[��
	myMath::Vector3 scale = { 1.0f, 1.0f, 1.0f };

	myMath::Matrix4 matWorld;

	// �e�ƂȂ郏�[���h�ϊ��ւ̃|�C���^
	const Transform* parent = nullptr;

	myMath::Vector3 parentToTranslation = { 0.0f, 0.0f, 0.0f };

public:

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	/// <summary>
	/// �s���]������
	/// </summary>
	void TransUpdate(Camera* camera);

	void Update();

	void MakeWorldMatrix();

	ID3D12Resource* GetconstBuff();

	worldViewpojCamera* GetWorldViewpojCamera();
};

namespace myMath
{
	Matrix4 MakeWorldMatrix4(Transform& transform);

	/// <summary>
	/// ���[���h���W�擾
	/// </summary>
	Vector3 GetWorldPosition(Transform& transform);
}
