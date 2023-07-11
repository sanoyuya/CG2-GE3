#include "EasingFunction.h"

double Easing::EaseInSine(double time, const double startPoint, const double endPoint, const double maxTime)
{
	double x = time / maxTime;
	double v = 1.0f - cos((x * myMath::AX_PI) / 2.0f);
	double ret = (endPoint - startPoint) * v + startPoint;
	return ret;
}

double Easing::EaseInCubic(double time, const double startPoint, const double endPoint, const double maxTime)
{
	double x = time / maxTime;
	double v = x * x * x;
	double ret = (endPoint - startPoint) * v + startPoint;
	return ret;
}

double Easing::EaseInQuint(double time, const double startPoint, const double endPoint, const double maxTime)
{
	double x = time / maxTime;
	double v = x * x * x * x * x;
	double ret = (endPoint - startPoint) * v + startPoint;
	return ret;
}

double Easing::EaseInCirc(double time, const double startPoint, const double endPoint, const double maxTime)
{
	double x = time / maxTime;
	double v = 1.0f - sqrt(1.0f - pow(x, 2.0f));
	double ret = (endPoint - startPoint) * v + startPoint;
	return ret;
}

double Easing::EaseInElastic(double time, const double startPoint, const double endPoint, const double maxTime)
{
	double x = time / maxTime;
	const double c4 = (2.0f * myMath::AX_PI) / 3.0f;
	double v = x == 0.0f
		? 0.0f
		: x == 1.0f
		? 1.0f
		: -pow(2.0f, 10.0f * x - 10.0f) * sin((x * 10.0f - 10.75f) * c4);
	double ret = (endPoint - startPoint) * v + startPoint;
	return ret;
}

double Easing::EaseInQuad(double time, const double startPoint, const double endPoint, const double maxTime)
{
	double x = time / maxTime;
	double v = x * x;
	double ret = (endPoint - startPoint) * v + startPoint;
	return ret;
}

double Easing::EaseInQuart(double time, const double startPoint, const double endPoint, const double maxTime)
{
	double x = time / maxTime;
	double v = x * x * x * x;
	double ret = (endPoint - startPoint) * v + startPoint;
	return ret;
}

double Easing::EaseInExpo(double time, const double startPoint, const double endPoint, const double maxTime)
{
	double x = time / maxTime;
	double v = x == 0.0f ? 0.0f : pow(2.0f, 10.0f * x - 10.0f);
	double ret = (endPoint - startPoint) * v + startPoint;
	return ret;
}

double Easing::EaseInBack(double time, const double startPoint, const double endPoint, const double maxTime)
{
	double x = time / maxTime;
	const double c1 = 1.70158f;
	const double c3 = c1 + 1.0f;
	double v = c3 * x * x * x - c1 * x * x;
	double ret = (endPoint - startPoint) * v + startPoint;
	return ret;
}

double Easing::EaseInBounce(double time, const double startPoint, const double endPoint, const double maxTime)
{
	double x = 1.0f - time / maxTime;
	double v = 1.0f - EaseOutBounce(x, startPoint, endPoint, maxTime);
	double ret = (endPoint - startPoint) * v + startPoint;
	return ret;
}

double Easing::EaseOutSine(double time, const double startPoint, const double endPoint, const double maxTime)
{
	double x = time / maxTime;
	double v = sin((x * myMath::AX_PI) / 2.0f);
	double ret = (endPoint - startPoint) * v + startPoint;
	return ret;
}

double Easing::EaseOutCubic(double time, const double startPoint, const double endPoint, const double maxTime)
{
	double x = time / maxTime;
	double v = 1.0f - pow(1.0f - x, 3.0f);
	double ret = (endPoint - startPoint) * v + startPoint;
	return ret;
}

double Easing::EaseOutQuint(double time, const double startPoint, const double endPoint, const double maxTime)
{
	double x = time / maxTime;
	double v = 1.0f - pow(1.0f - x, 5.0f);
	double ret = (endPoint - startPoint) * v + startPoint;
	return ret;
}

double Easing::EaseOutCirc(double time, const double startPoint, const double endPoint, const double maxTime)
{
	double x = time / maxTime;
	double v = sqrt(1.0f - pow(x - 1.0f, 2.0f));
	double ret = (endPoint - startPoint) * v + startPoint;
	return ret;
}

double Easing::EaseOutElastic(double time, const double startPoint, const double endPoint, const double maxTime)
{
	double x = time / maxTime;
	const double c4 = (2.0f * myMath::AX_PI) / 3.0f;
	double v = x == 0.0f
		? 0.0f
		: x == 1.0f
		? 1.0f
		: pow(2.0f, -10.0f * x) * sin((x * 10.0f - 0.75f) * c4) + 1.0f;
	double ret = (endPoint - startPoint) * v + startPoint;
	return ret;
}

double Easing::EaseOutQuad(double time, const double startPoint, const double endPoint, const double maxTime)
{
	double x = time / maxTime;
	double v = 1.0f - (1.0f - x) * (1.0f - x);
	double ret = (endPoint - startPoint) * v + startPoint;
	return ret;
}

double Easing::EaseOutQuart(double time, const double startPoint, const double endPoint, const double maxTime)
{
	double x = time / maxTime;
	double v = 1.0f - pow(1.0f - x, 4.0f);
	double ret = (endPoint - startPoint) * v + startPoint;
	return ret;
}

double Easing::easeOutExpo(double time, const double startPoint, const double endPoint, const double maxTime)
{
	double x = time / maxTime;
	double v = x == 1.0f ? 1.0f : 1.0f - pow(2.0f, -10.0f * x);
	double ret = (endPoint - startPoint) * v + startPoint;
	return ret;
}

double Easing::EaseOutBack(double time, const double startPoint, const double endPoint, const double maxTime)
{
	double x = time / maxTime;
	const double c1 = 1.70158f;
	const double c3 = c1 + 1.0f;
	double v = 1.0f + c3 * pow(x - 1.0f, 3.0f) + c1 * pow(x - 1.0f, 2.0f);
	double ret = (endPoint - startPoint) * v + startPoint;
	return ret;
}

double Easing::EaseOutBounce(double time, const double startPoint, const double endPoint, const double maxTime)
{
	double x = time / maxTime;
	const double n1 = 7.5625f;
	const double d1 = 2.75f;
	double v = 0.0f;
	if (x < 1.0f / d1) {
		v = n1 * x * x;
	}
	else if (x < 2.0f / d1) {
		v = n1 * (x -= 1.5f / d1) * x + 0.75f;
	}
	else if (x < 2.5f / d1) {
		v = n1 * (x -= 2.25f / d1) * x + 0.9375f;
	}
	else {
		v = n1 * (x -= 2.625f / d1) * x + 0.984375f;
	}
	double ret = (endPoint - startPoint) * v + startPoint;
	return ret;
}

double Easing::EaseInOutSine(double time, const double startPoint, const double endPoint, const double maxTime)
{
	double x = time / maxTime;
	double v = -(cos(myMath::AX_PI * x) - 1.0f) / 2.0f;
	double ret = (endPoint - startPoint) * v + startPoint;
	return ret;
}

double Easing::EaseInOutCubic(double time, const double startPoint, const double endPoint, const double maxTime)
{
	double x = time / maxTime;
	double v = x < 0.5f ? 4.0f * x * x * x : 1.0f - pow(-2.0f * x + 2.0f, 3.0f) / 2.0f;
	double ret = (endPoint - startPoint) * v + startPoint;
	return ret;
}

double Easing::EaseInOutQuint(double time, const double startPoint, const double endPoint, const double maxTime)
{
	double x = time / maxTime;
	double v = x < 0.5f ? 16.0f * x * x * x * x * x : 1.0f - pow(-2.0f * x + 2.0f, 5.0f) / 2.0f;
	double ret = (endPoint - startPoint) * v + startPoint;
	return ret;
}

double Easing::EaseInOutCirc(double time, const double startPoint, const double endPoint, const double maxTime)
{
	double x = time / maxTime;
	double v = x < 0.5f
		? (1.0f - sqrt(1.0f - pow(2.0f * x, 2.0f))) / 2.0f
		: (sqrt(1.0f - pow(-2.0f * x + 2.0f, 2.0f)) + 1.0f) / 2.0f;
	double ret = (endPoint - startPoint) * v + startPoint;
	return ret;
}

double Easing::EaseInOutElastic(double time, const double startPoint, const double endPoint, const double maxTime)
{
	double x = time / maxTime;
	const double c5 = (2.0f * myMath::AX_PI) / 4.5f;
	double v = x == 0.0f
		? 0.0f
		: x == 1.0f
		? 1.0f
		: x < 0.5f
		? -(pow(2.0f, 20.0f * x - 10.0f) * sin((20.0f * x - 11.125f) * c5)) / 2.0f
		: (pow(2.0f, -20.0f * x + 10.0f) * sin((20.0f * x - 11.125f) * c5)) / 2.0f + 1.0f;
	double ret = (endPoint - startPoint) * v + startPoint;
	return ret;
}

double Easing::EaseInOutQuad(double time, const double startPoint, const double endPoint, const double maxTime)
{
	double x = time / maxTime;
	double v = x < 0.5f ? 2.0f * x * x : 1.0f - pow(-2.0f * x + 2.0f, 2.0f) / 2.0f;
	double ret = (endPoint - startPoint) * v + startPoint;
	return ret;
}

double Easing::EaseInOutQuart(double time, const double startPoint, const double endPoint, const double maxTime)
{
	double x = time / maxTime;
	double v = x < 0.5f ? 8.0f * x * x * x * x : 1.0f - pow(-2.0f * x + 2.0f, 4.0f) / 2.0f;
	double ret = (endPoint - startPoint) * v + startPoint;
	return ret;
}

double Easing::EaseInOutExpo(double time, const double startPoint, const double endPoint, const double maxTime)
{
	double x = time / maxTime;
	double v = x == 0.0f
		? 0.0f
		: x == 1.0f
		? 1.0f
		: x < 0.5f ? pow(2.0f, 20.0f * x - 10.0f) / 2.0f
		: (2.0f - pow(2.0f, -20.0f * x + 10.0f)) / 2.0f;
	double ret = (endPoint - startPoint) * v + startPoint;
	return ret;
}

double Easing::EaseInOutBack(double time, const double startPoint, const double endPoint, const double maxTime)
{
	double x = time / maxTime;
	const double c1 = 1.70158f;
	const double c2 = c1 * 1.525f;
	double v = x < 0.5f
		? (pow(2.0f * x, 2.0f) * ((c2 + 1.0f) * 2.0f * x - c2)) / 2.0f
		: (pow(2.0f * x - 2.0f, 2.0f) * ((c2 + 1.0f) * (x * 2.0f - 2.0f) + c2) + 2.0f) / 2.0f;
	double ret = (endPoint - startPoint) * v + startPoint;
	return ret;
}

double Easing::EaseInOutBounce(double time, const double startPoint, const double endPoint, const double maxTime)
{
	double x = time / maxTime;
	double v = x < 0.5f
		? (1.0f - EaseOutBounce(1.0f - 2.0f * x, startPoint, endPoint, maxTime)) / 2.0f
		: (1.0f + EaseOutBounce(2.0f * x - 1.0f, startPoint, endPoint, maxTime)) / 2.0f;
	double ret = (endPoint - startPoint) * v + startPoint;
	return ret;
}