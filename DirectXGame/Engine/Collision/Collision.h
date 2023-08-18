#pragma once
#include"myMath.h"

/// <summary>
/// ��
/// </summary>
struct Sphere
{
	//���S���W
	myMath::Vector3 center = { 0.0f,0.0f ,0.0f };
	//���a
	float radius = 1.0f;
};

/// <summary>
/// ����
/// </summary>
struct Plane
{
	//�@���x�N�g��
	myMath::Vector3 normal = { 0.0f,1.0f,0.0f };
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
	myMath::Vector3 p0;
	myMath::Vector3 p1;
	myMath::Vector3 p2;
	//�@���x�N�g��
	myMath::Vector3 normal;
};

/// <summary>
/// ���C
/// </summary>
struct Ray
{
	//�n�_���W
	myMath::Vector3 start = { 0.0f,0.0f ,0.0f };
	//����
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