#pragma once
#include"myMath.h"

/// <summary>
/// ��
/// </summary>
struct Sphere
{
	//���S���W
	myMath::Vector4 center = { 0.0f,0.0f ,0.0f ,1.0f };
	//���a
	float radius = 1.0f;
};

/// <summary>
/// ����
/// </summary>
struct Plane
{
	//�@���x�N�g��
	myMath::Vector4 normal = { 0.0f,1.0f,0.0f ,0.0f };
	//���_
	float destance = 0.0f;
};

class Triangle
{
public:
	//���_���W3��
	myMath::Vector4 p0;
	myMath::Vector4 p1;
	myMath::Vector4 p2;
	//�@���x�N�g��
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