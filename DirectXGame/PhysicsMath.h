#pragma once
#include"myMath.h"

namespace PhysicsMath
{
	/// <summary>
	/// 単振動をした値を返す
	/// </summary>
	/// <param name="time">時間</param>
	/// <param name="amplitude">振幅</param>
	/// <param name="timeSpeed">時間の増える速度</param>
	/// <param name="period">周期</param>
	/// <returns></returns>
	float SimpleHarmonicMotion(float& time,float amplitude = 10.0f, float timeSpeed = 1.0f, float period = 100.0f);

	/// <summary>
	/// 円運動をした値を返す(複素数版)
	/// </summary>
	/// <param name="CenterPoint">中心点</param>
	/// <param name="radius">中心点からの半径</param>
	/// <param name="angle">角度</param>
	/// <returns></returns>
	myMath::Vector2 CircularMotion(myMath::Vector2 CenterPoint, float radius, float angle);
}