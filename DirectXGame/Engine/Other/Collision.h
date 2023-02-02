#pragma once
#include"myMath.h"

/// <summary>
/// 球
/// </summary>
struct Sphere
{
	//中心座標
	myMath::Vector4 center = { 0.0f,0.0f ,0.0f ,1.0f };
	//半径
	float radius = 1.0f;
};

/// <summary>
/// 平面
/// </summary>
struct Plane
{
	//法線ベクトル
	myMath::Vector4 normal = { 0.0f,1.0f,0.0f ,0.0f };
	//原点
	float destance = 0.0f;
};

class Triangle
{
public:
	//頂点座標3つ
	myMath::Vector4 p0;
	myMath::Vector4 p1;
	myMath::Vector4 p2;
	//法線ベクトル
	myMath::Vector4 normal;
};

class Collision
{
public:
	static bool SphereToPlane(const Sphere& sphere, const Plane& plane, myMath::Vector4* inter = nullptr);
	static bool SphereToTriangle(const Sphere& sphere, const Triangle& triangle, myMath::Vector4* inter = nullptr, myMath::Vector4* reject = nullptr);
private:
	static void ClosestPtPoint2Triangle(const myMath::Vector4& point, const Triangle& triangle, myMath::Vector4* closest);
};