#include "myMath.h"
#include<cMath>
#include <random>

namespace myMath
{
	void MakeOrthogonalL(float left, float right, float bottom, float top, float near_, float far_, Matrix4& matrix)
	{

		float width = 1.0f / (right - left);
		float height = 1.0f / (top - bottom);
		float range = 1.0f / (far_ - near_);

		matrix.m[0][0] = width * 2;

		matrix.m[1][1] = height * 2;

		matrix.m[2][2] = range;

		matrix.m[3][0] = -(left + right) * width;
		matrix.m[3][1] = -(top + bottom) * height;
		matrix.m[3][2] = range * -near_;
		matrix.m[3][3] = 1.0f;

		matrix.m[0][1] = matrix.m[0][2] = matrix.m[0][3] =
			matrix.m[1][0] = matrix.m[1][2] = matrix.m[1][3] =
			matrix.m[2][0] = matrix.m[2][1] = matrix.m[2][3] = 0.0f;
	}

	void MakeOrthogonalR(float left, float right, float bottom, float top, float near_, float far_, Matrix4& matrix)
	{
		float width = 1.0f / (right - left);
		float height = 1.0f / (top - bottom);
		float range = 1.0f / (far_ - near_);

		matrix.m[0][0] = width * 2;

		matrix.m[1][1] = height * 2;

		matrix.m[2][2] = range;

		matrix.m[3][0] = -(left + right) * width;
		matrix.m[3][1] = -(top + bottom) * height;
		matrix.m[3][2] = range * -near_;
		matrix.m[3][3] = 1.0f;

		matrix.m[0][1] = matrix.m[0][2] = matrix.m[0][3] =
			matrix.m[1][0] = matrix.m[1][2] = matrix.m[1][3] =
			matrix.m[2][0] = matrix.m[2][1] = matrix.m[2][3] = 0.0f;

	}

	void MakePerspectiveL(float fovAngleY, float aspect, float near_, float far_, Matrix4& matrix)
	{

		float sinFov = 0.0f;
		float cosFov = 0.0f;
		SinCos(sinFov, cosFov, 0.5f * fovAngleY);

		float range = far_ / (far_ - near_);
		float height = cosFov / sinFov;

		matrix.m[0][0] = height / aspect;

		matrix.m[1][1] = cosFov / sinFov;

		matrix.m[2][2] = range;
		matrix.m[2][3] = 1.0f;

		matrix.m[3][2] = -range * near_;

		matrix.m[0][1] = matrix.m[0][2] = matrix.m[0][3] =
			matrix.m[1][0] = matrix.m[1][2] = matrix.m[1][3] =
			matrix.m[2][0] = matrix.m[2][1] =
			matrix.m[3][0] = matrix.m[3][1] = matrix.m[3][3] = 0.0f;
	}

	void MakePerspectiveR(float fovAngleY, float aspect, float near_, float far_, Matrix4& matrix)
	{
		float sinFov = 0.0f;
		float cosFov = 0.0f;
		SinCos(sinFov, cosFov, 0.5f * fovAngleY);

		float range = far_ / (far_ - near_);
		float height = cosFov / sinFov;

		matrix.m[0][0] = height / aspect;

		matrix.m[1][1] = cosFov / sinFov;

		matrix.m[2][2] = range;
		matrix.m[2][3] = 1.0f;

		matrix.m[3][2] = -range * near_;

		matrix.m[0][1] = matrix.m[0][2] = matrix.m[0][3] =
			matrix.m[1][0] = matrix.m[1][2] = matrix.m[1][3] =
			matrix.m[2][0] = matrix.m[2][1] =
			matrix.m[3][0] = matrix.m[3][1] = matrix.m[3][3] = 0.0f;


	}

	void SinCos(float& sin_, float& cos_, float angle)
	{
		sin_ = sin(angle);
		cos_ = cos(angle);
	}

	float ChangeRadians(const float& angle)
	{
		float radian = angle * AX_PIF / 180;
		return radian;
	}

	float ChangeDira(const float& angle)
	{
		float radian = angle * 180 / AX_PIF;
		return radian;
	}

	void CoordinateTransformation3D(float& x, float& y, float& z, Matrix4& mat)
	{
		Vector3 vec(x, y, z);

		x = vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat.m[2][0];

		y = vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat.m[2][1];

		z = vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat.m[2][2];
	}

	void MakeLookL(Vector3& eye, Vector3& target, Vector3& up, Matrix4& mat)
	{
		Vector3 zVec = target - eye;
		zVec.normalization();

		Vector3 xVec = up.cross(zVec);
		xVec.normalization();

		Vector3 yVec = zVec.cross(xVec);
		yVec.normalization();

		mat.m[0][0] = xVec.x;
		mat.m[0][1] = xVec.y;
		mat.m[0][2] = xVec.z;
		mat.m[1][0] = yVec.x;
		mat.m[1][1] = yVec.y;
		mat.m[1][2] = yVec.z;
		mat.m[2][0] = zVec.x;
		mat.m[2][1] = zVec.y;
		mat.m[2][2] = zVec.z;
		mat.m[3][0] = eye.x;
		mat.m[3][1] = eye.y;
		mat.m[3][2] = eye.z;
	}

	// ランダムな値を取得
	double GetRand(double min, double max)
	{
		// 乱数生成器
		static std::random_device rand;
		static std::default_random_engine engine(rand());

		// 分布生成器
		std::uniform_real_distribution<double> get_rand_uni_real(min, max);

		// 乱数を生成
		return get_rand_uni_real(engine);
	}

	int8_t GetRandPlusOrMinus()
	{
		// 乱数生成器
		static std::random_device rand;
		static std::default_random_engine engine(rand());

		// 分布生成器
		std::uniform_real_distribution<double> get_rand_uni_real(0, 1);

		// 乱数を生成
		if (get_rand_uni_real(engine) <= 0.5f)
		{
			return -1;
		}
		else
		{
			return 1;
		}
	}

	// 二つの値がほぼ等しいか
	bool Approximately(float a, float b)
	{
		float tmp = 1e-06f * std::max(abs(a), abs(b));

		float tmp2 = EPSILON * 8.0f;

		if (abs(b - a) < std::max(tmp, tmp2))
		{
			return true;
		}

		return false;
	}

	Vector3 HermiteGetPoint(Vector3 p0, Vector3 p1, Vector3 v0, Vector3 v1, float t)
	{
		Vector3 c0 = 2.0f * p0 + -2.0f * p1 + v0 + v1;
		Vector3 c1 = -3.0f * p0 + 3.0f * p1 + -2.0f * v0 - v1;
		Vector3 c2 = v0;
		Vector3 c3 = p0;

		float t2 = t * t;
		float t3 = t2 * t;
		return c0 * t3 + c1 * t2 + c2 * t + c3;
	}

	Vector3 CatmullRomSpline(std::vector<Vector3>& points, float t)
	{
		float length = static_cast<float>(points.size());
		float progress = (length - 1) * t;
		float index = std::floor(progress);
		float weight = progress - index;

		if (Approximately(weight, 0.0f) && index >= length - 1)
		{
			index = length - 2;
			weight = 1;
		}

		Vector3 p0 = points[static_cast<size_t>(index)];
		Vector3 p1 = points[static_cast<size_t>(index + 1.0f)];
		Vector3 p2;
		Vector3 p3;

		if (index > 0.0f)
		{
			p2 = 0.5f * (points[static_cast<size_t>(index + 1.0f)] - points[static_cast<size_t>(index - 1.0f)]);
		}
		else
		{
			p2 = points[static_cast<size_t>(index + 1.0f)] - points[static_cast<size_t>(index)];
		}

		if (index < length - 2.0f)
		{
			p3 = 0.5f * (points[static_cast<size_t>(index + 2.0f)] - points[static_cast<size_t>(index)]);
		}
		else
		{
			p3 = points[static_cast<size_t>(index + 1.0f)] - points[static_cast<size_t>(index)];
		}

		return HermiteGetPoint(p0, p1, p2, p3, weight);
	}

	const Vector3 lerp(const Vector3& start, const Vector3& end, const float t)
	{
		return start * (1.0f - t) + end * t;
	}

	Vector3 Beziers(Vector3 startPos, Vector3 endPos, Vector3 controlPoint, float t)
	{
		float timeRate = std::min(t / 1.0f, 1.0f);

		Vector3 a = lerp(startPos, controlPoint, timeRate);
		Vector3 b = lerp(controlPoint, endPos, timeRate);
		Vector3 position = lerp(a, b, timeRate);

		return position;
	}
}