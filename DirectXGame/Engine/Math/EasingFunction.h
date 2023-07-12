#pragma once
#include"myMath.h"

namespace Easing
{
#pragma region EaseIn
	/// <summary>
	/// EaseInSine
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="startPoint">�J�n�ʒu</param>
	/// <param name="endPoint">�I���ʒu</param>
	/// <param name="maxTime">���v����</param>
	/// <returns>double</returns>
	double EaseInSine(double time, const double startPoint, const double endPoint, const double maxTime);

	/// <summary>
	/// EaseInCubic
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="startPoint">�J�n�ʒu</param>
	/// <param name="endPoint">�I���ʒu</param>
	/// <param name="maxTime">���v����</param>
	/// <returns>double</returns>
	double EaseInCubic(double time, const double startPoint, const double endPoint, const double maxTime);

	/// <summary>
	/// EaseInQuint
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="startPoint">�J�n�ʒu</param>
	/// <param name="endPoint">�I���ʒu</param>
	/// <param name="maxTime">���v����</param>
	/// <returns>double</returns>
	double EaseInQuint(double time, const double startPoint, const double endPoint, const double maxTime);

	/// <summary>
	/// EaseInCirc
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="startPoint">�J�n�ʒu</param>
	/// <param name="endPoint">�I���ʒu</param>
	/// <param name="maxTime">���v����</param>
	/// <returns>double</returns>
	double EaseInCirc(double time, const double startPoint, const double endPoint, const double maxTime);

	/// <summary>
	/// EaseInElastic
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="startPoint">�J�n�ʒu</param>
	/// <param name="endPoint">�I���ʒu</param>
	/// <param name="maxTime">���v����</param>
	/// <returns>double</returns>
	double EaseInElastic(double time, const double startPoint, const double endPoint, const double maxTime);

	/// <summary>
	/// EaseInQuad
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="startPoint">�J�n�ʒu</param>
	/// <param name="endPoint">�I���ʒu</param>
	/// <param name="maxTime">���v����</param>
	/// <returns>double</returns>
	double EaseInQuad(double time, const double startPoint, const double endPoint, const double maxTime);

	/// <summary>
	/// EaseInQuart
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="startPoint">�J�n�ʒu</param>
	/// <param name="endPoint">�I���ʒu</param>
	/// <param name="maxTime">���v����</param>
	/// <returns>double</returns>
	double EaseInQuart(double time, const double startPoint, const double endPoint, const double maxTime);

	/// <summary>
	/// EaseInExpo
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="startPoint">�J�n�ʒu</param>
	/// <param name="endPoint">�I���ʒu</param>
	/// <param name="maxTime">���v����</param>
	/// <returns>double</returns>
	double EaseInExpo(double time, const double startPoint, const double endPoint, const double maxTime);

	/// <summary>
	/// EaseInBack
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="startPoint">�J�n�ʒu</param>
	/// <param name="endPoint">�I���ʒu</param>
	/// <param name="maxTime">���v����</param>
	/// <returns>double</returns>
	double EaseInBack(double time, const double startPoint, const double endPoint, const double maxTime);

	/// <summary>
	/// EaseInBounce
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="startPoint">�J�n�ʒu</param>
	/// <param name="endPoint">�I���ʒu</param>
	/// <param name="maxTime">���v����</param>
	/// <returns>double</returns>
	double EaseInBounce(double time, const double startPoint, const double endPoint, const double maxTime);

#pragma endregion EaseIn

#pragma region EaseOut
	/// <summary>
	/// EaseOutSine
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="startPoint">�J�n�ʒu</param>
	/// <param name="endPoint">�I���ʒu</param>
	/// <param name="maxTime">���v����</param>
	/// <returns>double</returns>
	double EaseOutSine(double time, const double startPoint, const double endPoint, const double maxTime);

	/// <summary>
	/// EaseOutCubic
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="startPoint">�J�n�ʒu</param>
	/// <param name="endPoint">�I���ʒu</param>
	/// <param name="maxTime">���v����</param>
	/// <returns>double</returns>
	double EaseOutCubic(double time, const double startPoint, const double endPoint, const double maxTime);

	/// <summary>
	/// EaseOutQuint
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="startPoint">�J�n�ʒu</param>
	/// <param name="endPoint">�I���ʒu</param>
	/// <param name="maxTime">���v����</param>
	/// <returns>double</returns>
	double EaseOutQuint(double time, const double startPoint, const double endPoint, const double maxTime);

	/// <summary>
	/// EaseOutCirc
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="startPoint">�J�n�ʒu</param>
	/// <param name="endPoint">�I���ʒu</param>
	/// <param name="maxTime">���v����</param>
	/// <returns>double</returns>
	double EaseOutCirc(double time, const double startPoint, const double endPoint, const double maxTime);

	/// <summary>
	/// EaseOutElastic
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="startPoint">�J�n�ʒu</param>
	/// <param name="endPoint">�I���ʒu</param>
	/// <param name="maxTime">���v����</param>
	/// <returns>double</returns>
	double EaseOutElastic(double time, const double startPoint, const double endPoint, const double maxTime);

	/// <summary>
	/// EaseOutQuad
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="startPoint">�J�n�ʒu</param>
	/// <param name="endPoint">�I���ʒu</param>
	/// <param name="maxTime">���v����</param>
	/// <returns>double</returns>
	double EaseOutQuad(double time, const double startPoint, const double endPoint, const double maxTime);

	/// <summary>
	/// EaseOutQuart
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="startPoint">�J�n�ʒu</param>
	/// <param name="endPoint">�I���ʒu</param>
	/// <param name="maxTime">���v����</param>
	/// <returns>double</returns>
	double EaseOutQuart(double time, const double startPoint, const double endPoint, const double maxTime);

	/// <summary>
	/// easeOutExpo
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="startPoint">�J�n�ʒu</param>
	/// <param name="endPoint">�I���ʒu</param>
	/// <param name="maxTime">���v����</param>
	/// <returns>double</returns>
	double easeOutExpo(double time, const double startPoint, const double endPoint, const double maxTime);

	/// <summary>
	/// EaseOutBack
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="startPoint">�J�n�ʒu</param>
	/// <param name="endPoint">�I���ʒu</param>
	/// <param name="maxTime">���v����</param>
	/// <returns>double</returns>
	double EaseOutBack(double time, const double startPoint, const double endPoint, const double maxTime);

	/// <summary>
	/// EaseOutBounce
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="startPoint">�J�n�ʒu</param>
	/// <param name="endPoint">�I���ʒu</param>
	/// <param name="maxTime">���v����</param>
	/// <returns>double</returns>
	double EaseOutBounce(double time, const double startPoint, const double endPoint, const double maxTime);
#pragma endregion EaseOut

#pragma region EaseInOut
	/// <summary>
	/// EaseInOutSine
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="startPoint">�J�n�ʒu</param>
	/// <param name="endPoint">�I���ʒu</param>
	/// <param name="maxTime">���v����</param>
	/// <returns>double</returns>
	double EaseInOutSine(double time, const double startPoint, const double endPoint, const double maxTime);

	/// <summary>
	/// EaseInOutCubic
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="startPoint">�J�n�ʒu</param>
	/// <param name="endPoint">�I���ʒu</param>
	/// <param name="maxTime">���v����</param>
	/// <returns>double</returns>
	double EaseInOutCubic(double time, const double startPoint, const double endPoint, const double maxTime);

	/// <summary>
	/// EaseInOutQuint
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="startPoint">�J�n�ʒu</param>
	/// <param name="endPoint">�I���ʒu</param>
	/// <param name="maxTime">���v����</param>
	/// <returns>double</returns>
	double EaseInOutQuint(double time, const double startPoint, const double endPoint, const double maxTime);

	/// <summary>
	/// EaseInOutCirc
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="startPoint">�J�n�ʒu</param>
	/// <param name="endPoint">�I���ʒu</param>
	/// <param name="maxTime">���v����</param>
	/// <returns>double</returns>
	double EaseInOutCirc(double time, const double startPoint, const double endPoint, const double maxTime);

	/// <summary>
	/// EaseInOutElastic
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="startPoint">�J�n�ʒu</param>
	/// <param name="endPoint">�I���ʒu</param>
	/// <param name="maxTime">���v����</param>
	/// <returns>double</returns>
	double EaseInOutElastic(double time, const double startPoint, const double endPoint, const double maxTime);

	/// <summary>
	/// EaseInOutQuad
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="startPoint">�J�n�ʒu</param>
	/// <param name="endPoint">�I���ʒu</param>
	/// <param name="maxTime">���v����</param>
	/// <returns>double</returns>
	double EaseInOutQuad(double time, const double startPoint, const double endPoint, const double maxTime);

	/// <summary>
	/// EaseInOutQuart
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="startPoint">�J�n�ʒu</param>
	/// <param name="endPoint">�I���ʒu</param>
	/// <param name="maxTime">���v����</param>
	/// <returns>double</returns>
	double EaseInOutQuart(double time, const double startPoint, const double endPoint, const double maxTime);

	/// <summary>
	/// EaseInOutExpo
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="startPoint">�J�n�ʒu</param>
	/// <param name="endPoint">�I���ʒu</param>
	/// <param name="maxTime">���v����</param>
	/// <returns>double</returns>
	double EaseInOutExpo(double time, const double startPoint, const double endPoint, const double maxTime);

	/// <summary>
	/// EaseInOutBack
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="startPoint">�J�n�ʒu</param>
	/// <param name="endPoint">�I���ʒu</param>
	/// <param name="maxTime">���v����</param>
	/// <returns>double</returns>
	double EaseInOutBack(double time, const double startPoint, const double endPoint, const double maxTime);

	/// <summary>
	/// EaseInOutBounce
	/// </summary>
	/// <param name="time">����</param>
	/// <param name="startPoint">�J�n�ʒu</param>
	/// <param name="endPoint">�I���ʒu</param>
	/// <param name="maxTime">���v����</param>
	/// <returns>double</returns>
	double EaseInOutBounce(double time, const double startPoint, const double endPoint, const double maxTime);
#pragma endregion EaseInOut
}