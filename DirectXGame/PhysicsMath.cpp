#include "PhysicsMath.h"
#include<cmath>

namespace PhysicsMath
{
	float Complement(float& x1, float& x2, float flame)
	{
		float distanceX = x2 - x1;//�������o��
		float dividedDistanceX = distanceX / flame;//������flame�Ŋ������l

		x1 += dividedDistanceX;//������flame�Ŋ������l�𑫂�

		return x1;
	}

	float SimpleHarmonicMotion(float time ,float amplitude, float period)
	{
		return amplitude * sinf(myMath::AX_2PI * time / period);
	}

	myMath::Vector2 CircularMotion(myMath::Vector2 CenterPoint, float radius, float angle)
	{
		myMath::Vector2 position;

		position.x = radius * cosf(angle);
		position.y = radius * sinf(angle);

		return position;
	}
}