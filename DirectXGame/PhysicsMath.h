#pragma once
#include"myMath.h"

namespace PhysicsMath
{
	/// <summary>
	/// �P�U���������l��Ԃ�
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="amplitude">�U��</param>
	/// <param name="timeSpeed">���Ԃ̑����鑬�x</param>
	/// <param name="period">����</param>
	/// <returns></returns>
	float SimpleHarmonicMotion(float& time,float amplitude = 10.0f, float timeSpeed = 1.0f, float period = 100.0f);

	/// <summary>
	/// �~�^���������l��Ԃ�(���f����)
	/// </summary>
	/// <param name="CenterPoint">���S�_</param>
	/// <param name="radius">���S�_����̔��a</param>
	/// <param name="angle">�p�x</param>
	/// <returns></returns>
	myMath::Vector2 CircularMotion(myMath::Vector2 CenterPoint, float radius, float angle);
}