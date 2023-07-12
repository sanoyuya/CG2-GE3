#include "PhysicsMath.h"
#include<cmath>

namespace PhysicsMath
{
	float Complement(float& x1, float& x2, float flame)
	{
		float distanceX = x2 - x1;//‹——£‚ðo‚·
		float dividedDistanceX = distanceX / flame;//‹——£‚ðflame‚ÅŠ„‚Á‚½’l

		x1 += dividedDistanceX;//‹——£‚ðflame‚ÅŠ„‚Á‚½’l‚ð‘«‚·

		return x1;
	}

	float SimpleHarmonicMotion(float time ,float amplitude, float period)
	{
		return amplitude * sinf(myMath::AX_2PIF * time / period);
	}

	myMath::Vector2 CircularMotion(myMath::Vector2 CenterPoint, float radius, float angle)
	{
		myMath::Vector2 position;

		position.x = CenterPoint.x + radius * cosf(angle);
		position.y = CenterPoint.y + radius * sinf(angle);

		return position;
	}

	float angle = 0.0f;
	myMath::Vector2 FigureOfEight(float radiusX, float radiusY, float flame, const float maxFlame)
	{
		myMath::Vector2 pos = { 0.0f,0.0f };
		
		if (flame >= maxFlame)
		{
			angle = 0.0f;
		}
		pos.x = radiusX * (cosf(angle) * 2.0f);
		pos.y = radiusY * (sinf(2 * angle) * 2.0f);

		angle += myMath::AX_2PIF / maxFlame;
		return pos;
	}
}