#pragma once
#include"myMath.h"

namespace PhysicsMath
{
	/// <summary>
	/// �⊮(����)
	/// </summary>
	/// <param name="x1">�ړ��������ϐ�</param>
	/// <param name="x2">�ړ�����������</param>
	/// <param name="flame">����</param>
	/// <returns>�⊮��̒l</returns>
	float Complement(float& x1, float& x2, float flame);

	/// <summary>
	/// �P�U���������l��Ԃ�
	/// </summary>
	/// <param name="time">�o�ߎ���</param>
	/// <param name="amplitude">�U��</param>
	/// <param name="period">����</param>
	/// <returns></returns>
	float SimpleHarmonicMotion(float time,float amplitude = 10.0f, float period = 60.0f);

	/// <summary>
	/// �~�^���������l��Ԃ�(���f����)
	/// </summary>
	/// <param name="CenterPoint">���S�_</param>
	/// <param name="radius">���S�_����̔��a</param>
	/// <param name="angle">�p�x</param>
	/// <returns></returns>
	myMath::Vector2 CircularMotion(myMath::Vector2 CenterPoint, float radius, float angle);

	myMath::Vector2 FigureOfEight(float radiusX, float radiusY, float flame, const float maxFlame);
}