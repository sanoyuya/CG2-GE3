#pragma once
#include"myMath.h"

/// <summary>
/// カメラ
/// </summary>
class Camera
{
private:

	float aspect = 0.0f;
	float nearClip = 0.0f;
	float farClip = 0.0f;
	float angle = 0.0f;				//カメラ角度
	float distance = 50.0f;			//カメラ距離
	myMath::Matrix4 matView;		//ビュー行列
	myMath::Matrix4 matViewInverse;	//逆ビュー行列	
	myMath::Matrix4 matProjection;	//射影行列
	myMath::Vector3 eye;			//視点座標
	myMath::Vector3 target;			//注視点座標
	myMath::Vector3 up;				//上方向ベクトル

	//bool projectionFlag = false;	//平行投影と透視投影を切り替えるフラグ

public:

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="projectionFlag">平行投影と透視投影を切り替えるフラグ</param>
	void Initialize(bool projectionFlag);

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="projectionFlag">平行投影と透視投影を切り替えるフラグ</param>
	void Update(bool projectionFlag);

	/// <summary>
	/// ビュー行列の計算
	/// </summary>
	void UpdateMatView();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="projectionFlag">平行投影と透視投影を切り替えるフラグ</param>
	void UpdateMatProjection(bool projectionFlag);

	//ゲッター
	const myMath::Matrix4& GetMatView();
	const myMath::Matrix4& GetMatViewInverse();
	const myMath::Matrix4& GetMatProjection();
	const myMath::Vector3& GetEye();
	const myMath::Vector3& GetTarget();
	const myMath::Vector3& GetUp();

	//セッター
	void SetEye(const myMath::Vector3& eye_);
	void SetTarget(const myMath::Vector3& target_);
	void SetUp(const myMath::Vector3& up_);
};