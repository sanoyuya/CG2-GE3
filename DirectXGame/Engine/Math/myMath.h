#pragma once
#include"Vector2.h"
#include"Vector3.h"
#include"Vector4.h"
#include"Matrix4.h"
#include<vector>

//2D�ϊ��s��(�萔�o�b�t�@)
struct ConstBufferDataTransform
{
	DirectX::XMMATRIX mat;//3D�ϊ��s��
};

namespace myMath
{
	//��
	constexpr float AX_PIF = 3.141592654f;
	constexpr float AX_2PIF = 6.283185307f;
	constexpr double AX_PI = 3.141592654;
	constexpr double AX_2PI = 6.283185307;

	//��
	constexpr float EPSILON = 2.2204460492503131E-16f;

	/// <summary>
	/// ���s���e�ϊ��s��𐶐�(����n)
	/// </summary>
	/// <param name="left"> : ����</param>
	/// <param name="right"> : �E��</param>
	/// <param name="bottom"> : ����</param>
	/// <param name="top"> : �㑤</param>
	/// <param name="near_"> : �j�A�N���b�v����</param>
	/// <param name="far_"> : �t�@�[�N���b�v����</param>
	/// <param name="matrix"> : �������s��</param>
	void MakeOrthogonalL(float left, float right, float bottom, float top, float near_, float far_, Matrix4& matrix);

	/// <summary>
	/// ���s���e�ϊ��s��𐶐�(�E��n)
	/// </summary>
	/// <param name="left"> : ����</param>
	/// <param name="right"> : �E��</param>
	/// <param name="bottom"> : ����</param>
	/// <param name="top"> : �㑤</param>
	/// <param name="near_"> : �j�A�N���b�v����</param>
	/// <param name="far_"> : �t�@�[�N���b�v����</param>
	/// <param name="matrix"> : �������s��</param>
	void MakeOrthogonalR(float left, float right, float bottom, float top, float near_, float far_, Matrix4& matrix);

	/// <summary>
	/// �������e�ϊ��s��𐶐�(����n)
	/// </summary>
	/// <param name="fovAngleY"> : �㉺��p</param>
	/// <param name="aspect"> : �A�X�y�N�g��(��ʉ���/��ʏc��)</param>
	/// <param name="near_"> : �j�A�N���b�v����</param>
	/// <param name="far_"> : �t�@�[�N���b�v����</param>
	/// <param name="matrix"> : �������s��</param>
	void MakePerspectiveL(float fovAngleY, float aspect, float near_, float far_, Matrix4& matrix);

	/// <summary>
	/// �������e�ϊ��s��𐶐�(�E��n)
	/// </summary>
	/// <param name="fovAngleY"> : �㉺��p</param>
	/// <param name="aspect"> : �A�X�y�N�g��(��ʉ���/��ʏc��)</param>
	/// <param name="near_"> : �j�A�N���b�v����</param>
	/// <param name="far_"> : �t�@�[�N���b�v����</param>
	/// <param name="matrix"> : �������s��</param>
	void MakePerspectiveR(float fovAngleY, float aspect, float near_, float far_, Matrix4& matrix);

	/// <summary>
	/// Sin�ACos�𗼕��o��
	/// </summary>
	/// <param name="sin_"> : sin�̌��ʂ�������</param>
	/// <param name="cos_"> : cos�̌��ʂ�������</param>
	/// <param name="angle"> : ���W�A���p</param>
	void SinCos(float& sin_, float& cos_, float angle);

	/// <summary>
	/// �x���@���烉�W�A���ϊ�
	/// </summary>
	/// <param name="angle"> : �p�x</param>
	float ChangeRadians(const float& angle);

	/// <summary>
	/// ���W�A������x���@�ϊ�
	/// </summary>
	/// <param name="angle"> : �p�x</param>
	float ChangeDira(const float& angle);

	/// <summary>
	/// �x�N�g���ƍs��̊|���Z
	/// </summary>
	/// <param name="x">�|������x�N�g����X���W</param>
	/// <param name="y">�|������x�N�g����Y���W</param>
	/// <param name="z">�|������x�N�g����Z���W</param>
	/// <param name="mat">�|����s��</param>
	void CoordinateTransformation3D(float& x, float& y, float& z, Matrix4& mat);

	/// <summary>
	/// �r���[�ϊ��s��𐶐�
	/// </summary>
	/// <param name="eye"></param>
	/// <param name="target"></param>
	/// <param name="up"></param>
	void MakeLookL(Vector3& eye, Vector3& target, Vector3& up, Matrix4& mat);

	/// <summary>
	/// �����_���Ȓl���擾
	/// </summary>
	/// <param name="min">�ŏ��l</param>
	/// <param name="max">�ő�l</param>
	double GetRand(double min, double max);

	/// <summary>
	/// ��̒l���قړ�������
	/// </summary>
	bool Approximately(float a, float b);

	/// <summary>
	/// �G���~�[�g�Ȑ�
	/// </summary>
	/// <param name="p0">����_</param>
	/// <param name="p1">����_</param>
	/// <param name="v0">����_</param>
	/// <param name="v1">����_</param>
	/// <param name="t">����(0.0�`1.0)</param>
	/// <returns></returns>
	Vector3 HermiteGetPoint(Vector3 p0, Vector3 p1, Vector3 v0, Vector3 v1, float t);

	/// <summary>
	/// �L���b�g�����[�����X�v���C�� 
	/// </summary>
	/// <param name="points">����_</param>
	/// <param name="t">����(0.0�`1.0)</param>
	Vector3 CatmullRomSpline(std::vector<Vector3>& points, float t);

	//���`�⊮(1���֐��⊮)
	const Vector3 lerp(const Vector3& start, const Vector3& end, const float t);

	Vector3 Beziers(Vector3 startPos, Vector3 endPos,Vector3 controlPoint, float t);
}