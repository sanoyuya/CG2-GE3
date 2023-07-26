#pragma once
#include<DirectXMath.h>
#include "Vector3.h"

namespace myMath
{
	class Matrix4
	{
	public:
		float m[4][4];

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <returns>�P�ʍs��Ƃ��ď���������܂�</returns>
		Matrix4();

		Matrix4(float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33);

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		Matrix4(const DirectX::XMMATRIX& Matrix4);

		/// <summary>
		/// �g��s����쐬
		/// </summary>
		/// <param name="scale"> : �g�嗦</param>
		void MakeScaling(const Vector3& scale);

		/// <summary>
		/// �g��s����쐬
		/// </summary>
		/// <param name="x,y,z"> : �g�嗦</param>
		void MakeScaling(float x, float y, float z);

		/// <summary>
		/// ���s�ړ��s����쐬
		/// </summary>
		/// <param name="trans"> : ���s�ړ�</param>
		void MakeTranslation(const Vector3& trans);

		/// <summary>
		/// ���s�ړ��s����쐬
		/// </summary>
		/// <param name="x,y,z"> : ���s�ړ�</param>
		void MakeTranslation(float x, float y, float z);

		/// <summary>
		/// Y������̉�]�s����쐬
		/// </summary>
		/// <param name="angle"> : ��]�p�x(�P�ʁF���W�A��)</param>
		void MakeRotationY(float angle);

		/// <summary>
		/// Z������̉�]�s����쐬
		/// </summary>
		/// <param name="angle"> : ��]�p�x(�P�ʁF���W�A��)</param>
		void MakeRotationZ(float angle);

		/// <summary>
		/// X������̉�]�s����쐬
		/// </summary>
		/// <param name="angle"> : ��]�p�x(�P�ʁF���W�A��)</param>
		void MakeRotationX(float angle);

		/// <summary>
		/// X������̉�]�s����쐬
		/// </summary>
		/// <param name="Rotat"> : ��]�p�x(�P�ʁF���W�A��)</param>
		void MakeRotation(const Vector3& Rotat);

		/// <summary>
		/// X������̉�]�s����쐬
		/// </summary>
		/// <param name="x,y,z"> : ��]�p�x(�P�ʁF���W�A��)</param>
		void MakeRotation(float x, float y, float z);

		/// <summary>
		/// DirectX::XMMATRIX�^�ւ̈Öق̌^�ϊ��B
		/// </summary>
		operator DirectX::XMMATRIX() const;

		/// <summary>
		/// ������Z�q
		/// </summary>
		Matrix4& operator=(const Matrix4& _m);

		/// <summary>
		/// ���Z
		/// </summary>
		Matrix4& operator+=(const Matrix4& mat);

		/// <summary>
		/// ���Z
		/// </summary>
		Matrix4& operator-=(const Matrix4& mat);

		/// <summary>
		/// ��Z
		/// </summary>
		Matrix4& operator*=(const Matrix4& mat);

		/// <summary>
		/// ���Z
		/// </summary>
		Matrix4 operator+(const Matrix4& mat) const;

		/// <summary>
		/// ���Z
		/// </summary>
		Matrix4 operator-(const Matrix4& mat) const;

		/// <summary>
		/// ��Z
		/// </summary>
		Matrix4 operator*(const Matrix4& mat) const;

		/// <summary>
		/// �x�N�g���ƍs��̊|���Z
		/// </summary>
		/// <param name="mat"></param>
		/// <param name="vec"></param>
		/// <returns></returns>
		Vector3 Transform(const Matrix4& mat, const Vector3 vec);
	};

	/// <summary>
	/// �P�ʍs��
	/// </summary>
	Matrix4 MakeIdentity();

	/// <summary>
	/// �t�s������߂�
	/// </summary>
	/// <param name="mat">�t�s��ɂ������s��</param>
	/// <returns>�t�s��or�P�ʍs��</returns>
	Matrix4 MakeInverse(Matrix4& mat);
}