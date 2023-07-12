#include "Collision.h"
#include<cmath>

bool Collision::SphereToSphere(const myMath::Vector3& sphere1, float radius1, const myMath::Vector3& sphere2, float radius2)
{
	/*return false;

	if (std::pow((sphere2.x - sphere1.x), 2)
		+ std::pow((sphere2.y - sphere1.y), 2)
		+ std::pow((sphere2.z - sphere1.z), 2) <= std::pow((radius1 + radius2), 2))
	{
		return true;
	}*/

	if (std::pow((sphere2.x - sphere1.x), 2)
		+ std::pow((sphere2.y - sphere1.y), 2)
		+ std::pow((sphere2.z - sphere1.z), 2) <= std::pow((radius1 + radius2), 2))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Collision::SphereToSphere(const Sphere* sphere1, const Sphere* sphere2)
{
	if (std::pow((sphere2->center.x - sphere1->center.x), 2)
		+ std::pow((sphere2->center.y - sphere1->center.y), 2)
		+ std::pow((sphere2->center.z - sphere1->center.z), 2) <= std::pow((sphere1->radius + sphere2->radius), 2))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Collision::SphereToSphere(const Sphere& sphere1, const Sphere& sphere2)
{
	/*return false;

	if (std::pow((sphere2.center.x - sphere1.center.x), 2)
		+ std::pow((sphere2.center.y - sphere1.center.y), 2)
		+ std::pow((sphere2.center.z - sphere1.center.z), 2) <= std::pow((sphere1.radius + sphere2.radius), 2))
	{
		return true;
	}*/

	if (std::pow((sphere2.center.x - sphere1.center.x), 2)
		+ std::pow((sphere2.center.y - sphere1.center.y), 2)
		+ std::pow((sphere2.center.z - sphere1.center.z), 2) <= std::pow((sphere1.radius + sphere2.radius), 2))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Collision::SphereToPlane(const Sphere& sphere, const Plane& plane, myMath::Vector4* inter)
{
	// ���W�n�̌��_���狅�̒��S���W�ւ̋�������
	// ���ʂ̌��_���������Z���邱�ƂŁA���ʂƋ��̒��S�Ƃ̋������o��
	float dist = sphere.center.dot(plane.normal) - plane.destance;
	// �����̐�Βl�����a���傫����Γ������Ă��Ȃ�
	if (fabsf(dist) > sphere.radius) return false;

	// �[����_���v�Z
	if (inter)
	{
		// ���ʏ�̍Đڋߓ_���A�^����_�Ƃ���
		*inter = -dist * plane.normal + sphere.center + sphere.center;
	}

	return true;
}

bool Collision::SphereToTriangle(const Sphere& sphere, const Triangle& triangle, myMath::Vector4* inter, myMath::Vector4* reject)
{
	myMath::Vector4 p;
	// ���̒��S�ɑ΂���ŋߐړ_�ł���O�p�`��ɂ���_p��������
	myMath::Vector4 tmp = sphere.center;
	ClosestPtPoint2Triangle(tmp, triangle, &p);
	// �_p�Ƌ��̒��S�̍����x�N�g��
	myMath::Vector4 v = p - sphere.center;
	// �����̓������߂�
	//�i�����x�N�g�����m�̓��ς͎O�����̒藝�̃��[�g�����̎��ƈ�v����j
	float distanceSquare = v.dot(v);
	// ���ƎO�p�`�̋��������a�ȉ��Ȃ瓖�����Ă��Ȃ�
	if (distanceSquare > sphere.radius * sphere.radius)
	{
		return false;
	}

	// �[����_���v�Z
	if (inter)
	{
		// �O�p�`��̍ŋߐړ_p���^����_�Ƃ���
		*inter = p;
	}
	// �����o���x�N�g�����v�Z
	if (reject)
	{
		float ds = sphere.center.dot(triangle.normal);
		float dt = triangle.p0.dot(triangle.normal);
		float rejectLen = dt - ds + sphere.radius;
		*reject = triangle.normal * rejectLen;
	}
	return true;
}

bool Collision::RayToPlane(const Ray& ray, Plane& plane, float* distance, myMath::Vector4* inter)
{
	const float epsilon = 1.0e-5f;	// �덷�z���p�̔����Ȓl

	float d1 = plane.normal.dot(ray.dir);
	// ���ʂɂ͓�����Ȃ�
	if (d1 > -epsilon)
	{
		return false;
	}

	float d2 = plane.normal.dot(ray.start);
	float t = (plane.destance - d2) / d1;

	if (t < 0) return false;

	// ��������������
	if (distance)
	{
		*distance = t;
	}

	// ��_���v�Z
	if (inter)
	{
		*inter = ray.start + t * ray.dir;
	}

	return true;
}

bool Collision::RayToTriangle(const Ray& ray, const Triangle& triangle, float* distance, myMath::Vector4* inter)
{
	// �O�p�`������Ă��镽�ʂ��Z�o
	Plane plane;
	myMath::Vector4 interPlane;
	myMath::Vector4 tmp = triangle.normal;
	plane.normal = tmp;
	plane.destance = triangle.normal.dot(triangle.p0);
	// ���C�ƕ��ʂ��������Ă��Ȃ���΁A�������Ă��Ȃ�	
	if (!RayToPlane(ray, plane, distance, &interPlane))
	{
		return false;
	}
	// ���C�ƕ��ʂ��������Ă����̂ŁA�����ƌ�_���������܂ꂽ

	// ���C�ƕ��ʂ̌�_���O�p�`�̓����ɂ��邩����
	const float epsilon = 1.0e-5f;	// �덷�z���p�̔����Ȓl
	myMath::Vector4 m;
	// ��p0_p1�ɂ���
	myMath::Vector4 pt_p0 = triangle.p0 - interPlane;
	myMath::Vector4 p0_p1 = triangle.p1 - triangle.p0;
	m = pt_p0.cross(p0_p1);
	// �ӂ̊O��
	if (m.dot(triangle.normal) < -epsilon)
	{
		return false;
	}

	// ��p1_p2�ɂ���
	myMath::Vector4 pt_p1 = triangle.p1 - interPlane;
	myMath::Vector4 p1_p2 = triangle.p2 - triangle.p1;
	m = pt_p1.cross(p1_p2);
	// �ӂ̊O��
	if (m.dot(triangle.normal) < -epsilon)
	{
		return false;
	}

	// ��p2_p0�ɂ���
	myMath::Vector4 pt_p2 = triangle.p2 - interPlane;
	myMath::Vector4 p2_p0 = triangle.p0 - triangle.p2;
	m = pt_p2.cross(p2_p0);
	// �ӂ̊O��
	if (m.dot(triangle.normal) < -epsilon)
	{
		return false;
	}

	if (inter)
	{
		*inter = interPlane;
	}

	// �����Ȃ̂ŁA�������Ă���
	return true;
}

bool Collision::RayToSphere(const Ray& ray, const Sphere& sphere, float* distance, myMath::Vector4* inter)
{
	myMath::Vector4 m = ray.start - sphere.center;
	float b = m.dot(ray.dir);
	float c = m.dot(m) - sphere.radius * sphere.radius;
	// lay�̎n�_��sphere�̊O���ɂ���(c > 0)�Alay��sphere���痣��Ă���������
	// �����Ă���ꍇ(b > 0)�A������Ȃ�
	if (c > 0.0f && b > 0.0f)
	{
		return false;
	}

	float discr = b * b - c;
	// ���̔��ʎ��̓��C�������O��Ă��邱�ƂɈ�v
	if (discr < 0.0f)
	{
		return false;
	}

	// ���C�͋��ƌ������Ă���B
	// ��������ŏ��̒lt���v�Z
	float t = -b - sqrtf(discr);
	// t�����ł���ꍇ�A���C�͋��̓�������J�n���Ă���̂�t���[���ɃN�����v
	if (t < 0) t = 0.0f;

	if (distance)
	{
		*distance = t;
	}

	if (inter)
	{
		*inter = ray.start + t * ray.dir;
	}

	return true;
}

void Collision::ClosestPtPoint2Triangle(const myMath::Vector4& point, const Triangle& triangle, myMath::Vector4* closest)
{
	// point��p0�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	myMath::Vector4 p0_p1 = triangle.p1 - triangle.p0;
	myMath::Vector4 p0_p2 = triangle.p2 - triangle.p0;
	myMath::Vector4 p0_pt = point - triangle.p0;

	float d1 = p0_pt.dot(p0_p1);
	float d2 = p0_pt.dot(p0_p2);

	if (d1 <= 0.0f && d2 <= 0.0f)
	{
		// p0���ŋߖT
		*closest = triangle.p0;
		return;
	}

	// point��p1�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	myMath::Vector4 p1_pt = point - triangle.p1;

	float d3 = p1_pt.dot(p0_p1);
	float d4 = p1_pt.dot(p0_p2);

	if (d3 >= 0.0f && d4 <= d3)
	{
		// p1���ŋߖT
		*closest = triangle.p1;
		return;
	}

	// point��p0_p1�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p0_p1��ɑ΂���ˉe��Ԃ�
	float vc = d1 * d4 - d3 * d2;
	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
	{
		float v = d1 / (d1 - d3);
		*closest = triangle.p0 + v * p0_p1;
		return;
	}

	// point��p2�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	myMath::Vector4 p2_pt = point - triangle.p2;

	float d5 = p2_pt.dot(p0_p1);
	float d6 = p2_pt.dot(p0_p2);
	if (d6 >= 0.0f && d5 <= d6)
	{
		*closest = triangle.p2;
		return;
	}

	// point��p0_p2�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p0_p2��ɑ΂���ˉe��Ԃ�
	float vb = d5 * d2 - d1 * d6;
	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f)
	{
		float w = d2 / (d2 - d6);
		*closest = triangle.p0 + w * p0_p2;
		return;
	}

	// point��p1_p2�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p1_p2��ɑ΂���ˉe��Ԃ�
	float va = d3 * d6 - d5 * d4;
	if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f)
	{
		float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		*closest = triangle.p1 + w * (triangle.p2 - triangle.p1);
		return;
	}

	// point�͖ʗ̈�̒��ɂ���Bclosest���d�S���W��p���Čv�Z����
	float denom = 1.0f / (va + vb + vc);
	float v = vb * denom;
	float w = vc * denom;
	*closest = triangle.p0 + p0_p1 * v + p0_p2 * w;
}
