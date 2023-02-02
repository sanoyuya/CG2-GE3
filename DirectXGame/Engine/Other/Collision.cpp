#include "Collision.h"

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

	/*myMath::Vector4 p;

	ClosestPtPoint2Triangle(sphere.center, triangle, &p);

	myMath::Vector4 v = p - sphere.center;

	float vDot = v.dot(v);

	if (vDot > sphere.radius * sphere.radius)
	{
		return false;
	}

	if (inter)
	{
		*inter = p;
	}

	if (reject)
	{
		float ds = sphere.center.dot(triangle.normal);
		float dt = triangle.p0.dot(triangle.normal);
		float rejectLen = dt - ds + sphere.radius;
		*reject = triangle.normal * rejectLen;
	}

	return true;*/
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

	//// point��p0�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	//myMath::Vector4 p0_p1 = triangle.p1 - triangle.p0;
	//myMath::Vector4 p0_p2 = triangle.p2 - triangle.p0;
	//myMath::Vector4 p0_pt = point - triangle.p0;

	//float d1 = p0_p1.dot(p0_pt);
	//float d2 = p0_p2.dot(p0_pt);

	//if (d1 <= 0.0f && d2 <= 0.0f)
	//{
	//	// p0���ŋߖT
	//	*closest = triangle.p0;
	//	return;
	//}

	//// point��p1�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	//myMath::Vector4 p1_pt = point - triangle.p1;

	//float d3 = p0_p1.dot(p1_pt);
	//float d4 = p0_p2.dot(p1_pt);

	//if (d3 >= 0.0f && d4 <= d3)
	//{
	//	// p1���ŋߖT
	//	*closest = triangle.p1;
	//	return;
	//}

	//// point��p0_p1�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p0_p1��ɑ΂���ˉe��Ԃ�
	//float vc = d1 * d4 - d3 * d2;
	//if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
	//{
	//	float v = d1 / (d1 - d3);
	//	*closest = triangle.p0 + v * p0_p1;
	//	return;
	//}

	//// point��p2�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	//myMath::Vector4 p2_pt = point - triangle.p2;

	//float d5 = p0_p1.dot(p2_pt);
	//float d6 = p0_p2.dot(p2_pt);
	//if (d6 >= 0.0f && d5 <= d6)
	//{
	//	*closest = triangle.p2;
	//	return;
	//}

	//// point��p0_p2�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p0_p2��ɑ΂���ˉe��Ԃ�
	//float vb = d5 * d2 - d1 * d6;
	//if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f)
	//{
	//	float w = d2 / (d2 - d6);
	//	*closest = triangle.p0 + w * p0_p2;
	//	return;
	//}

	//// point��p1_p2�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p1_p2��ɑ΂���ˉe��Ԃ�
	//float va = d3 * d6 - d5 * d4;
	//if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f)
	//{
	//	float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
	//	*closest = triangle.p1 + w * (triangle.p2 - triangle.p1);
	//	return;
	//}

	//float denom = 1.0f / (va + vb + vc);
	//float v = vb * denom;
	//float w = vc * denom;
	//*closest = triangle.p0 + p0_p1 * v + p0_p2 * w;
}
