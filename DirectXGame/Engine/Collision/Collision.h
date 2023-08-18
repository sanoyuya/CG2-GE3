#pragma once
#include"myMath.h"

/// <summary>
/// 球
/// </summary>
struct Sphere
{
	//中心座標
	myMath::Vector3 center = { 0.0f,0.0f ,0.0f };
	//半径
	float radius = 1.0f;
};

/// <summary>
/// 平面
/// </summary>
struct Plane
{
	//法線ベクトル
	myMath::Vector3 normal = { 0.0f,1.0f,0.0f };
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
	myMath::Vector3 p0;
	myMath::Vector3 p1;
	myMath::Vector3 p2;
	//法線ベクトル
	myMath::Vector3 normal;
};

/// <summary>
/// レイ
/// </summary>
struct Ray
{
	//始点座標
	myMath::Vector3 start = { 0.0f,0.0f ,0.0f };
	//方向
	myMath::Vector3 dir = { 1.0f,0.0f,0.0f };
};

class Collision
{
public:
	static bool SphereToSphere(const myMath::Vector3& sphere1,float radius1, const myMath::Vector3& sphere2,float radius2);
	static bool SphereToSphere(const Sphere* sphere1, const Sphere* sphere2);

	static bool SphereToSphere(const Sphere& sphere1, const Sphere& sphere2);
	static bool SphereToPlane(const Sphere& sphere, const Plane& plane, myMath::Vector3* inter = nullptr);
	static bool SphereToTriangle(const Sphere& sphere, const Triangle& triangle, myMath::Vector3* inter = nullptr, myMath::Vector3* reject = nullptr);
	static bool RayToPlane(const Ray& ray, Plane& plane, float* distance = nullptr, myMath::Vector3* inter = nullptr);
	static bool RayToTriangle(const Ray& ray, const Triangle& triangle, float* distance = nullptr, myMath::Vector3* inter = nullptr);
	static bool RayToSphere(const Ray& ray, const Sphere& sphere, float* distance = nullptr, myMath::Vector3* inter = nullptr);
	static bool RayToSphere(const myMath::Vector3& rayStartPos, const myMath::Vector3& rayEndPos, const myMath::Vector3& spherePos,float radius, float* distance = nullptr);
private:
	static void ClosestPtPoint2Triangle(const myMath::Vector3& point, const Triangle& triangle, myMath::Vector3* closest);
};