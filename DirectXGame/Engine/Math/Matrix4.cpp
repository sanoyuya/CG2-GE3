#include "Matrix4.h"
#include<cMath>

namespace myMath
{
	Matrix4::Matrix4()
	{
		m[0][0] = 1.0f;
		m[0][1] = 0.0f;
		m[0][2] = 0.0f;
		m[0][3] = 0.0f;

		m[1][0] = 0.0f;
		m[1][1] = 1.0f;
		m[1][2] = 0.0f;
		m[1][3] = 0.0f;

		m[2][0] = 0.0f;
		m[2][1] = 0.0f;
		m[2][2] = 1.0f;
		m[2][3] = 0.0f;

		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = 1.0f;
	}

	Matrix4::Matrix4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33)
	{
		m[0][0] = m00;
		m[0][1] = m01;
		m[0][2] = m02;
		m[0][3] = m03;

		m[1][0] = m10;
		m[1][1] = m11;
		m[1][2] = m12;
		m[1][3] = m13;

		m[2][0] = m20;
		m[2][1] = m21;
		m[2][2] = m22;
		m[2][3] = m23;

		m[3][0] = m30;
		m[3][1] = m31;
		m[3][2] = m32;
		m[3][3] = m33;
	}

	Matrix4 MakeIdentity()
	{
		Matrix4 mat;
		return mat;
	}

	Matrix4 MakeInverse(Matrix4& mat)
	{
		//掃き出し法を行う行列
		float sweep[4][8]{};
		//定数倍用
		float constTimes = 0.0f;
		//許容する誤差
		float MAX_ERR = 1e-10f;
		//戻り値用
		Matrix4 retMat;

		for (int8_t i = 0; i < 4; i++)
		{
			for (int8_t j = 0; j < 4; j++)
			{
				//weepの左側に逆行列を求める行列をセット
				sweep[i][j] = mat.m[i][j];

				//sweepの右側に単位行列をセット
				sweep[i][4 + j] = MakeIdentity().m[i][j];
			}
		}

		//全ての列の対角成分に対する繰り返し
		for (int8_t i = 0; i < 4; i++)
		{
			//最大の絶対値を注目対角成分の絶対値と仮定
			float max = std::fabs(sweep[i][i]);
			int8_t maxIndex = i;

			//i列目が最大の絶対値となる行を探す
			for (int8_t j = i + 1; j < 4; j++)
			{
				if (std::fabs(sweep[j][i]) > max)
				{
					max = std::fabs(sweep[j][i]);
					maxIndex = j;
				}
			}

			if (fabs(sweep[maxIndex][i]) <= MAX_ERR)
			{
				//逆行列は求められない
				return MakeIdentity();
			}

			//操作(1):i行目とmaxIndex行目を入れ替える
			if (i != maxIndex)
			{
				for (int8_t j = 0; j < 8; j++)
				{
					float tmp = sweep[maxIndex][j];
					sweep[maxIndex][j] = sweep[i][j];
					sweep[i][j] = tmp;
				}
			}

			//sweep[i][i]に掛けると1になる値を求める
			constTimes = 1 / sweep[i][i];

			//操作(2):p行目をa倍する
			for (int8_t j = 0; j < 8; j++)
			{
				//これによりsweep[i][i]が1になる
				sweep[i][j] *= constTimes;
			}

			//操作(3)によりi行目以外の行のi列目を0にする
			for (int8_t j = 0; j < 4; j++)
			{
				if (j == i)
				{
					//i行目はそのまま
					continue;
				}

				//i行目に掛ける値を求める
				constTimes = -sweep[j][i];

				for (int8_t k = 0; k < 8; k++)
				{
					//j行目にi行目をa倍した行を足す
					//これによりsweep[j][i]が0になる
					sweep[j][k] += sweep[i][k] * constTimes;
				}
			}
		}

		//sweepの右半分がmatの逆行列
		for (int8_t i = 0; i < 4; i++)
		{
			for (int8_t j = 0; j < 4; j++)
			{
				retMat.m[i][j] = sweep[i][4 + j];
			}
		}

		return retMat;
	}

	Matrix4::Matrix4(const DirectX::XMMATRIX& Matrix4)
	{
		for (int8_t i = 0; i < 4; i++)
		{
			for (int8_t j = 0; j < 4; j++)
			{
				m[i][j] = Matrix4.r[i].m128_f32[j];
			}
		}
	}

	void Matrix4::MakeScaling(const Vector3& scale)
	{
		//スケーリング倍率を行列に設定する
		m[0][0] = scale.x;
		m[1][1] = scale.y;
		m[2][2] = scale.z;
	}

	void Matrix4::MakeScaling(float x, float y, float z)
	{
		MakeScaling(Vector3(x, y, z));
	}

	void Matrix4::MakeTranslation(const Vector3& trans)
	{
		m[3][0] = trans.x;
		m[3][1] = trans.y;
		m[3][2] = trans.z;
	}

	void Matrix4::MakeTranslation(float x, float y, float z)
	{
		MakeTranslation(Vector3(x, y, z));
	}

	void Matrix4::MakeRotationY(float angle)
	{
		m[0][0] = std::cos(angle);
		m[0][2] = -std::sin(angle);

		m[2][0] = std::sin(angle);
		m[2][2] = std::cos(angle);
	}

	void Matrix4::MakeRotationZ(float angle)
	{
		m[0][0] = std::cos(angle);
		m[0][1] = std::sin(angle);

		m[1][0] = -std::sin(angle);
		m[1][1] = std::cos(angle);
	}

	void Matrix4::MakeRotationX(float angle)
	{
		m[1][1] = std::cos(angle);
		m[1][2] = std::sin(angle);

		m[2][1] = -std::sin(angle);
		m[2][2] = std::cos(angle);
	}

	void Matrix4::MakeRotation(const Vector3& Rotat)
	{
		Matrix4 RotX;
		Matrix4 RotY;
		Matrix4 RotZ;

		RotZ.MakeRotationZ(Rotat.z);
		RotX.MakeRotationX(Rotat.x);
		RotY.MakeRotationY(Rotat.y);

		*this = RotZ * RotX * RotY;
	}

	void Matrix4::MakeRotation(float x, float y, float z)
	{
		MakeRotation(Vector3(x, y, z));
	}

	Matrix4::operator DirectX::XMMATRIX() const
	{
		DirectX::XMMATRIX mat{
		m[0][0], m[0][1], m[0][2], m[0][3],
		m[1][0], m[1][1], m[1][2], m[1][3],
		m[2][0], m[2][1], m[2][2], m[2][3],
		m[3][0], m[3][1], m[3][2], m[3][3] };

		return mat;
	}


	Matrix4& Matrix4::operator=(const Matrix4& _m)
	{
		for (int8_t i = 0; i < 4; i++)
		{
			for (int8_t j = 0; j < 4; j++)
			{
				m[i][j] = _m.m[i][j];
			}
		}

		return *this;
	}

	Matrix4& Matrix4::operator+=(const Matrix4& mat)
	{
		for (int8_t i = 0; i < 4; i++)
		{
			for (int8_t j = 0; j < 4; j++)
			{
				m[i][j] += mat.m[i][j];
			}
		}

		return *this;
	}

	Matrix4& Matrix4::operator-=(const Matrix4& mat)
	{
		for (int8_t i = 0; i < 4; i++)
		{
			for (int8_t j = 0; j < 4; j++)
			{
				m[i][j] -= mat.m[i][j];
			}
		}

		return *this;
	}

	Matrix4& Matrix4::operator*=(const Matrix4& mat)
	{
		Matrix4 temp(*this);

		for (int8_t i = 0; i < 4; i++)
		{
			for (int8_t j = 0; j < 4; j++)
			{
				float f = 0;
				for (int8_t k = 0; k < 4; k++)
				{
					f += temp.m[i][k] * mat.m[k][j];
				}
				m[i][j] = f;
			}
		}
		return *this;
	}

	Matrix4 Matrix4::operator+(const Matrix4& mat) const
	{
		Matrix4 temp(*this);
		temp += mat;
		return temp;
	}

	Matrix4 Matrix4::operator-(const Matrix4& mat) const
	{
		Matrix4 temp(*this);
		temp -= mat;
		return temp;
	}

	Matrix4 Matrix4::operator*(const Matrix4& mat) const
	{
		Matrix4 temp(*this);
		temp *= mat;
		return temp;
	}

	Vector3 Matrix4::Transform(const Matrix4& mat, const Vector3 vec)
	{
		float w = vec.x * mat.m[0][3] + vec.y * mat.m[1][3] + vec.z * mat.m[2][3] + mat.m[3][3];

		Vector3 tmp = { (vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat.m[2][0] + mat.m[3][0]) / w,
			(vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat.m[2][1] + mat.m[3][1]) / w,
			(vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat.m[2][2] + mat.m[3][2]) / w };

		return tmp;
	}
}