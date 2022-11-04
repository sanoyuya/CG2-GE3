#include "PhysicsMath.h"
#include<cmath>

namespace PhysicsMath
{
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