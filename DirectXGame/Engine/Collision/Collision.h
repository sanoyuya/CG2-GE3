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

/// <summary>
/// �O�p�`
/// </summary>
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

/// <summary>
/// ���C
/// </summary>
struct Ray
{
	//�n�_���W
	myMath::Vector4 start = { 0.0f,0.0f ,0.0f ,1.0f };
	//����
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