#include "Quaternion.h"
#include<cmath>
#include"Vector4.h"

namespace myMath
{
	float EPSILON = 2.2204460492503131E-16f;

	float AngleNormalize(float x)
	{
		return static_cast<float>(static_cast<int>((x > 0.0f ? x : 360.0f + x)) % 360);
	}

	Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
	{

	}

	Quaternion::Quaternion(const myMath::Vector3& u, const myMath::Vector3& v)
	{
		myMath::Vector3 vecU = u;
		myMath::Vector3 vecV = v;
		vecU.normalization();
		vecV.normalization();

		float dot = vecU.dot(vecV);

		myMath::Vector3 cross = vecU.cross(vecV);
		cross.normalization();

		myMath::Vector3 axis = cross;

		float theta = acos(dot);

		float sin = sinf(theta / 2.0f);

		myMath::Vector4 result = {
			result.x = sin * axis.x,
			result.y = sin * axis.y,
			result.z = sin * axis.z,
			result.w = cosf(theta / 2.0f)
		};
		result.normalization();

		x = result.x;
		y = result.y;
		z = result.z;
		w = result.w;
	}

	Quaternion::Quaternion(const myMath::Vector3& v, float angle)
	{
		float _sin = sinf(angle / 2.0f);

		x = _sin * v.x;
		y = _sin * v.y;
		z = _sin * v.z;
		w = cosf(angle / 2.0f);
	}

	Quaternion::Quaternion(const myMath::Matrix4& m)
	{
		float tr = m.m[0][0] + m.m[1][1] + m.m[2][2] + m.m[3][3];

		if (tr >= 1.0f)
		{
			float fourD = 2.0f * sqrt(tr);
			x = (m.m[1][2] - m.m[2][1]) / fourD;
			y = (m.m[2][0] - m.m[0][2]) / fourD;
			z = (m.m[0][1] - m.m[1][0]) / fourD;
			w = fourD / 4.0f;
		}
		else
		{
			size_t i = 0;
			if (m.m[0][0] <= m.m[1][1])
			{
				i = 1;
			}
			if (m.m[2][2] > m.m[i][i])
			{
				i = 2;
			}

			size_t j = (i + 1) % 3;
			size_t k = (j + 1) % 3;

			tr = m.m[i][i] - m.m[j][k] - m.m[k][k] + 1.0f;

			float fourD = 2.0f * sqrt(tr);
			float qa[4]{};

			qa[i] = fourD / 4.0f;
			qa[j] = (m.m[j][i] + m.m[i][j]) / fourD;
			qa[k] = (m.m[k][i] + m.m[i][k]) / fourD;
			qa[3] = (m.m[j][k] - m.m[k][j]) / fourD;

			x = qa[0];
			y = qa[1];
			z = qa[2];
			w = qa[3];

		}
	}

	float Quaternion::Dot(const Quaternion& q)const
	{
		return w * q.w + x * q.x + y * q.y + z * q.z;
	}

	float Quaternion::Norm()const
	{
		return sqrtf(x * x + y * y + z * z + w * w);
	}

	Quaternion Quaternion::Normalize()const
	{
		float len = Norm();

		if (len != 0)
		{
			Quaternion tmp = *this;
			tmp /= len;

			return tmp;
		}

		return *this;
	}

	Quaternion Quaternion::Identity() const
	{
		return { 0.0f, 0.0f, 0.0f, 1.0f };
	}

	Quaternion Quaternion::Conjugate() const
	{
		return { -x,-y,-z,w };
	}

	Quaternion Quaternion::Inverse() const
	{
		return Conjugate() / (Norm() * Norm());
	}

	Quaternion Quaternion::Slerp(const Quaternion& q, float t)
	{
		float cos = Dot(q);

		Quaternion t2 = *this;

		if (cos < 0.0f)
		{
			cos = -cos;
			t2 = -*this;
		}

		if (cos >= 1.0f - 0.0005f)
		{
			return (1.0f - t) * q + t * t2;
		}

		float k0 = t;
		float k1 = 1.0f - t;

		float  theta = acosf(cos);

		k0 = (sinf(theta * k0) / sinf(theta));
		k1 = (sinf(theta * k1) / sinf(theta));

		return  k0 * q + k1 * t2;
	}

	Quaternion Quaternion::Lerp(const Quaternion& q, float t)
	{
		float cos = this->Dot(q);
		Quaternion t2 = q;
		if (cos < 0.0f)
		{
			cos = -cos;
			t2 = -q;
		}

		float k0 = 1.0f - t;
		float k1 = t;

		return *this * k0 + t2 * k1;
	}

	myMath::Matrix4 Quaternion::Rotate()
	{
		float xx = x * x * 2.0f;
		float yy = y * y * 2.0f;
		float zz = z * z * 2.0f;
		float xy = x * y * 2.0f;
		float xz = x * z * 2.0f;
		float yz = y * z * 2.0f;
		float wx = w * x * 2.0f;
		float wy = w * y * 2.0f;
		float wz = w * z * 2.0f;

		myMath::Matrix4 result = {
			1.0f - yy - zz,xy + wz,xz - wy,0.0f,
			xy - wz, 1.0f - xx - zz,yz + wx,0.0f,
			xz + wy, yz - wx,1.0f - xx - yy,0.0f,
			0.0f,0.0f,0.0f,1.0f
		};

		return result;
	}

	myMath::Vector3 Quaternion::GetAxis()
	{
		myMath::Vector3 result;

		float x_ = x;
		float y_ = y;
		float z_ = z;
		float len_ = Norm();

		result.x = x_ / len_;
		result.y = y_ / len_;
		result.z = z_ / len_;

		return result;
	}

	myMath::Vector3 Quaternion::GetEulerAngles()
	{
		myMath::Vector3 result;

		float q0q0 = x * x;
		float q0q1 = x * y;
		float q0q2 = x * z;
		float q0q3 = x * w;
		float q1q1 = y * y;
		float q1q2 = y * z;
		float q1q3 = y * w;
		float q2q2 = z * z;
		float q2q3 = z * w;
		float q3q3 = w * w;
		result.x = static_cast<float>(atan2(2.0 * (q2q3 + q0q1), q0q0 - q1q1 - q2q2 + q3q3));//roll
		result.y = static_cast<float>(asin(2.0 * (q0q2 - q1q3)));//pitch
		result.z = static_cast<float>(atan2(2.0 * (q1q2 + q0q3), q0q0 + q1q1 - q2q2 - q3q3));//yaw

		return result;
	}

	void Quaternion::SeTEuler(const myMath::Vector3& rot)
	{
		float cosR = cosf(rot.x / 2.f);
		float sinR = sinf(rot.x / 2.f);
		float cosP = cosf(rot.y / 2.f);
		float sinP = sinf(rot.y / 2.f);
		float cosY = cosf(rot.z / 2.f);
		float sinY = sinf(rot.z / 2.f);


		y = cosR * sinP * cosY + sinR * cosP * sinY;
		z = cosR * cosP * sinY - sinR * sinP * cosY;
		x = sinR * cosP * cosY - cosR * sinP * sinY;
		w = cosR * cosP * cosY + sinR * sinP * sinY;
	}

	Quaternion Quaternion::operator+()
	{
		return *this;
	}

	Quaternion Quaternion::operator-()const
	{
		return Quaternion(-x, -y, -z, -w);
	}

	Quaternion& Quaternion::operator+=(const Quaternion& q)
	{
		x += q.x;
		y += q.y;
		z += q.z;
		w += q.w;

		return *this;
	}

	Quaternion& Quaternion::operator-=(const Quaternion& q)
	{

		x -= q.x;
		y -= q.y;
		z -= q.z;
		w -= q.w;

		return *this;
	}

	Quaternion& Quaternion::operator*=(float s)
	{
		x *= s;
		y *= s;
		z *= s;
		w *= s;

		return *this;
	}

	Quaternion& Quaternion::operator/=(float s)
	{
		return *this *= 1.0f / s;
	}

	Quaternion& Quaternion::operator*=(const Quaternion& q)
	{
		float rx, ry, rz, rw;

		rx = w * q.x + q.w * x + y * q.z + -z * q.y;
		ry = w * q.y + q.w * y + z * q.x + -x * q.z;
		rz = w * q.z + q.w * z + x * q.y + -y * q.x;
		rw = w * q.w + -x * q.x + -y * q.y + -z * q.z;

		x = rx;
		y = ry;
		z = rz;
		w = rw;

		return *this;
	}

	const Quaternion operator+(const Quaternion& q1, const Quaternion& q2)
	{
		Quaternion temp = q1;

		return temp += q2;
	}

	const Quaternion operator-(const Quaternion& q1, const Quaternion& q2)
	{
		Quaternion result = q1;
		return result -= q2;
	}

	const Quaternion operator*(const Quaternion& q1, const Quaternion& q2)
	{
		Quaternion temp = q1;

		return temp *= q2;
	}

	const Quaternion operator*(const Quaternion& q, float s)
	{
		Quaternion temp = q;

		return temp *= s;
	}

	const Quaternion operator*(float s, const Quaternion& q)
	{
		Quaternion temp = q;

		return temp *= s;
	}

	const Quaternion operator/(const Quaternion& q, float s)
	{
		Quaternion result = q;
		result /= s;
		return result;
	}

	const myMath::Vector3 operator*(Quaternion q, myMath::Vector3 vec)
	{
		float x = q.x * 2.0f;
		float y = q.y * 2.0f;
		float z = q.z * 2.0f;
		float xx = q.x * x;
		float yy = q.y * y;
		float zz = q.z * z;
		float xy = q.x * y;
		float xz = q.x * z;
		float yz = q.y * z;
		float wx = q.w * x;
		float wy = q.w * y;
		float wz = q.w * z;

		myMath::Vector3 temp;

		temp.x = (1.0f - (yy + zz)) * vec.x + (xy - wz) * vec.y + (xz + wy) * vec.z;
		temp.y = (xy + wz) * vec.x + (1.0f - (xx + zz)) * vec.y + (yz - wx) * vec.z;
		temp.z = (xz - wy) * vec.x + (yz + wx) * vec.y + (1.0f - (xx + yy)) * vec.z;

		return temp;
	}
}