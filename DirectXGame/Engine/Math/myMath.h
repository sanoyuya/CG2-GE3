#pragma once
#include"Vector2.h"
#include"Vector3.h"
#include"Vector4.h"
#include"Matrix4.h"
#include"Quaternion.h"
#include<vector>

class Camera;

//2D変換行列(定数バッファ)
struct ConstBufferDataTransform
{
	DirectX::XMMATRIX mat;//3D変換行列
};

namespace myMath
{
	//π
	constexpr float AX_PIF = 3.141592654f;
	constexpr float AX_2PIF = 6.283185307f;
	constexpr double AX_PI = 3.141592654;
	constexpr double AX_2PI = 6.283185307;

	//ε
	constexpr float EPSILON = 2.2204460492503131E-16f;

	/// <summary>
	/// 平行投影変換行列を生成(左手系)
	/// </summary>
	/// <param name="left"> : 左側</param>
	/// <param name="right"> : 右側</param>
	/// <param name="bottom"> : 下側</param>
	/// <param name="top"> : 上側</param>
	/// <param name="near_"> : ニアクリップ距離</param>
	/// <param name="far_"> : ファークリップ距離</param>
	/// <param name="matrix"> : 代入する行列</param>
	void MakeOrthogonalL(float left, float right, float bottom, float top, float near_, float far_, Matrix4& matrix);

	/// <summary>
	/// 平行投影変換行列を生成(右手系)
	/// </summary>
	/// <param name="left"> : 左側</param>
	/// <param name="right"> : 右側</param>
	/// <param name="bottom"> : 下側</param>
	/// <param name="top"> : 上側</param>
	/// <param name="near_"> : ニアクリップ距離</param>
	/// <param name="far_"> : ファークリップ距離</param>
	/// <param name="matrix"> : 代入する行列</param>
	void MakeOrthogonalR(float left, float right, float bottom, float top, float near_, float far_, Matrix4& matrix);

	/// <summary>
	/// 透視投影変換行列を生成(左手系)
	/// </summary>
	/// <param name="fovAngleY"> : 上下画角</param>
	/// <param name="aspect"> : アスペクト比(画面横幅/画面縦幅)</param>
	/// <param name="near_"> : ニアクリップ距離</param>
	/// <param name="far_"> : ファークリップ距離</param>
	/// <param name="matrix"> : 代入する行列</param>
	void MakePerspectiveL(float fovAngleY, float aspect, float near_, float far_, Matrix4& matrix);

	/// <summary>
	/// 透視投影変換行列を生成(右手系)
	/// </summary>
	/// <param name="fovAngleY"> : 上下画角</param>
	/// <param name="aspect"> : アスペクト比(画面横幅/画面縦幅)</param>
	/// <param name="near_"> : ニアクリップ距離</param>
	/// <param name="far_"> : ファークリップ距離</param>
	/// <param name="matrix"> : 代入する行列</param>
	void MakePerspectiveR(float fovAngleY, float aspect, float near_, float far_, Matrix4& matrix);

	/// <summary>
	/// Sin、Cosを両方出す
	/// </summary>
	/// <param name="sin_"> : sinの結果を代入する</param>
	/// <param name="cos_"> : cosの結果を代入する</param>
	/// <param name="angle"> : ラジアン角</param>
	void SinCos(float& sin_, float& cos_, float angle);

	/// <summary>
	/// 度数法からラジアン変換
	/// </summary>
	/// <param name="angle"> : 角度</param>
	float ChangeRadians(const float& angle);

	/// <summary>
	/// ラジアンから度数法変換
	/// </summary>
	/// <param name="angle"> : 角度</param>
	float ChangeDira(const float& angle);

	/// <summary>
	/// ベクトルと行列の掛け算
	/// </summary>
	/// <param name="x">掛けられるベクトルのX座標</param>
	/// <param name="y">掛けられるベクトルのY座標</param>
	/// <param name="z">掛けられるベクトルのZ座標</param>
	/// <param name="mat">掛ける行列</param>
	void CoordinateTransformation3D(float& x, float& y, float& z, Matrix4& mat);

	/// <summary>
	/// ビュー変換行列を生成
	/// </summary>
	/// <param name="eye"></param>
	/// <param name="target"></param>
	/// <param name="up"></param>
	void MakeLookL(Vector3& eye, Vector3& target, Vector3& up, Matrix4& mat);

	/// <summary>
	/// ランダムな値を取得
	/// </summary>
	/// <param name="min">最小値</param>
	/// <param name="max">最大値</param>
	double GetRand(double min, double max);

	int8_t GetRandPlusOrMinus();

	/// <summary>
	/// 二つの値がほぼ等しいか
	/// </summary>
	bool Approximately(float a, float b);

	/// <summary>
	/// エルミート曲線
	/// </summary>
	/// <param name="p0">制御点</param>
	/// <param name="p1">制御点</param>
	/// <param name="v0">制御点</param>
	/// <param name="v1">制御点</param>
	/// <param name="t">時間(0.0～1.0)</param>
	/// <returns></returns>
	Vector3 HermiteGetPoint(Vector3 p0, Vector3 p1, Vector3 v0, Vector3 v1, float t);

	/// <summary>
	/// キャットムルーロムスプライン 
	/// </summary>
	/// <param name="points">制御点</param>
	/// <param name="t">時間(0.0～1.0)</param>
	Vector3 CatmullRomSpline(std::vector<Vector3>& points, float t);

	//線形補完(1次関数補完)
	const Vector3 lerp(const Vector3& start, const Vector3& end, const float t);

	/// <summary>
	/// ベクトルと行列の掛け算(W除算)
	/// </summary>
	/// <param name="vec">ベクトル</param>
	/// <param name="mat">行列</param>
	/// <returns>計算された値</returns>
	Vector3& Vec3Mat4MulWdiv(Vector3& vec, Matrix4& mat);

	Vector3 Beziers(Vector3 startPos, Vector3 endPos,Vector3 controlPoint, float t);

	Vector3 ScreenCoordinateTransformation(Camera* camera, Vector3 WorldPos, myMath::Vector2 windowsSize = { 1280.0f,720.0f });
}