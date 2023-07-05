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

/// <summary>
/// 三角形
/// </summary>
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

/// <summary>
/// レイ
/// </summary>
struct Ray
{
	//始点座標
	myMath::Vector4 start = { 0.0f,0.0f ,0.0f ,1.0f };
	//方向
	myMath::Vector4 dir = { 1.0f,0.0f,0.0f ,0.0f };
};

class Collision
{
public:
	static bool SphereToSphere(const myMath::Vector3& sphere1,float radius1, const myMath::Vector3& sphere2,float radius2);

	static bool SphereToSphere(const Sphere& sphere1, const Sphere& sphere2);
	static bool SphereToPlane(const Sphere& sphere, const Plane& plane, myMath::Vector4* inter = nullptr);
	static bool SphereToTriangle(const Sphere& sphere, const Triangle& triangle, myMath::Vector4* inter = nullptr, myMath::Vector4* reject = nullptr);
	static bool RayToPlane(const Ray& ray, Plane& plane, float* distance = nullptr, myMath::Vector4* inter = nullptr);
	static bool RayToTriangle(const Ray& ray, const Triangle& triangle, float* distance = nullptr, myMath::Vector4* inter = nullptr);
	static bool RayToSphere(const Ray& ray, const Sphere& sphere, float* distance = nullptr, myMath::Vector4* inter = nullptr);
private:
	static void ClosestPtPoint2Triangle(const myMath::Vector4& point, const Triangle& triangle, myMath::Vector4* closest);
};