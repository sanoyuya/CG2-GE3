#pragma once
#include"Vector3.h"
#include"Matrix4.h"

namespace myMath
{
	class Quaternion
	{
	private:

		double AX_PI = 3.14159265358979;

	public:

		float x;
		float y;
		float z;
		float w;

		//クオータニオンを作成
		//成分を指定して クォータニオンを作成
		Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);

		Quaternion(const myMath::Vector3& u, const myMath::Vector3& v);

		//任意軸まわりの回転の指定からクォータニオンを作成
		Quaternion(const myMath::Vector3& v, float angle);

		//回転行列からクォータニオンを作成
		Quaternion(const myMath::Matrix4& m);

		//内積を求める
		float Dot(const Quaternion& q)const;

		//ノルムを求める
		float Norm()const;

		//正規化する
		Quaternion Normalize() const;

		//単位クオータニオン
		Quaternion Identity() const;

		// 共役クオータニオン
		Quaternion Conjugate() const;

		// 逆クオータニオン
		Quaternion Inverse() const;

		//クオータニオン球面線形補間
		Quaternion Slerp(const Quaternion& q, float t);

		//クオータニオン線形補間
		Quaternion Lerp(const Quaternion& q, float t);

		//クオータニオンから回転行列を求める
		myMath::Matrix4 Rotate();

		//回転軸の算出
		myMath::Vector3 GetAxis();

		//オイラー角に変換
		myMath::Vector3 GetEulerAngles();

		//オイラー角からクオータニオンに変換
		void SeTEuler(const myMath::Vector3& rot);

		//単項演算子オーバーロード
		Quaternion operator + ();
		Quaternion operator - ()const;

		//代入演算子オーバーロード
		Quaternion& operator += (const Quaternion& q);
		Quaternion& operator -= (const Quaternion& q);
		Quaternion& operator *= (float s);
		Quaternion& operator /= (float s);
		Quaternion& operator *= (const Quaternion& q);
	};

	//2項演算子オーバーロード
	const Quaternion operator + (const Quaternion& q1, const Quaternion& q2);
	const Quaternion operator - (const Quaternion& q1, const Quaternion& q2);
	const Quaternion operator * (const Quaternion& q1, const Quaternion& q2);
	const Quaternion operator * (const Quaternion& q, float s);
	const Quaternion operator * (float s, const Quaternion& q);
	const Quaternion operator / (const Quaternion& q, float s);
	const myMath::Vector3 operator*(Quaternion q, myMath::Vector3 vec);
}