#include "Transform.h"
#include"DirectXBase.h"

myMath::Matrix4 Transform::defaultProjectionMat = { 1.3579f, 0.0f, 0.0f, 0.0f, 0.0f, 2.4142f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0001f, 1.0f, 0.0f, 0.0f, -0.1000f, 0.0f };
myMath::Matrix4 Transform::defaultViewMat = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 50.0f, 0.0f };

void Transform::Initialize()
{
	//�萔�o�b�t�@����(3D���W�ϊ��s��)
	constBuff = std::make_shared<ConstantBuffer>();
	constBuff->Create(sizeof(worldViewpojCamera));

	myMath::Matrix4 matScale, matRot, matTrans;

	//�X�P�[���A��]�A���s�ړ��s��̌v�Z
	matScale.MakeScaling(scale);
	matRot.MakeRotation(rotation);
	matTrans.MakeTranslation(translation);

	//���[���h�s��̍���
	//�ό`�����Z�b�g
	matWorld = myMath::MakeIdentity();
	//���[���h�s��ɃX�P�[�����O�𔽉f
	matWorld *= matScale;
	//���[���h�s��ɉ�]�𔽉f
	matWorld *= matRot;
	//���[���h�s��ɕ��s�ړ��𔽉f
	matWorld *= matTrans;
	//�e�s��̎w�肪����ꍇ�́A�|���Z����
	if (parent)
	{
		matWorld *= parent->matWorld;
	}

	//�萔�o�b�t�@�ɏ�������
	constBuffMap.matWorld = matWorld * defaultViewMat * defaultProjectionMat;
	constBuffMap.world = matWorld;
	constBuffMap.cameraPos = { 0.0f,0.0f,-50.0f };

	constBuff->Update(&constBuffMap);
}

void Transform::TransUpdate(Camera* camera)
{
	myMath::Matrix4 matScale, matRot, matTrans;

	//�X�P�[���A��]�A���s�ړ��s��̌v�Z
	matScale.MakeScaling(scale);
	matRot.MakeRotation(rotation);
	matTrans.MakeTranslation(translation);

	//���[���h�s��̍���
	//�ό`�����Z�b�g
	matWorld = myMath::MakeIdentity();
	//���[���h�s��ɃX�P�[�����O�𔽉f
	matWorld *= matScale;
	//���[���h�s��ɉ�]�𔽉f
	matWorld *= matRot;
	//���[���h�s��ɕ��s�ړ��𔽉f
	matWorld *= matTrans;
	//�e�s��̎w�肪����ꍇ�́A�|���Z����
	if (parent)
	{
		matWorld *= parent->matWorld;
	}

	//�萔�o�b�t�@�ɏ�������
	constBuffMap.matWorld = matWorld * camera->GetMatViewInverse() * camera->GetMatProjection();
	constBuffMap.world = matWorld;
	constBuffMap.cameraPos = camera->GetEye();
	constBuff->Update(&constBuffMap);
}

void Transform::Update()
{
	constBuff->Update(&constBuffMap);
}

void Transform::MakeWorldMatrix()
{
	myMath::Matrix4 matScale, matRot, matTrans;

	//�X�P�[���A��]�A���s�ړ��s��̌v�Z
	matScale.MakeScaling(scale);
	matRot.MakeRotation(rotation);
	matTrans.MakeTranslation(translation);

	//���[���h�s��̍���
	//�ό`�����Z�b�g
	matWorld = myMath::MakeIdentity();
	//���[���h�s��ɃX�P�[�����O�𔽉f
	matWorld *= matScale;
	//���[���h�s��ɉ�]�𔽉f
	matWorld *= matRot;
	//���[���h�s��ɕ��s�ړ��𔽉f
	matWorld *= matTrans;
	//�e�s��̎w�肪����ꍇ�́A�|���Z����
	if (parent)
	{
		matWorld *= parent->matWorld;
	}
}

ID3D12Resource* Transform::GetconstBuff()
{
	return constBuff->GetResource();
}

worldViewpojCamera* Transform::GetWorldViewpojCamera()
{
	return &constBuffMap;
}

namespace myMath
{
	Matrix4 MakeWorldMatrix4(Transform& transform)
	{
		Matrix4 matWorld = MakeIdentity();

		Matrix4 matScal, matRot, matTrans;

		//�X�P�[�����O�{��
		matScal.MakeScaling(transform.scale);

		//��]�s��
		matRot.MakeRotation(transform.rotation);

		// matWorld_�Ɉړ��ʂ��|���Z
		matTrans.MakeTranslation(transform.translation);

		matWorld = matScal * matRot * matTrans;

		if (transform.parent)
		{
			matWorld *= transform.parent->matWorld;
		}

		return matWorld;
	}

	Vector3 GetWorldPosition(Transform& transform)
	{
		//���[���h���W������ϐ�
		Vector3 worldPos;
		//���[���h�s��̕��s�ړ��������擾(���[���h���W)
		worldPos.x = transform.matWorld.m[3][0];
		worldPos.y = transform.matWorld.m[3][1];
		worldPos.z = transform.matWorld.m[3][2];

		return worldPos;
	}
}