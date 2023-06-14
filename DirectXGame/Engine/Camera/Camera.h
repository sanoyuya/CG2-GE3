#pragma once
#include"myMath.h"
#include"WindowsApp.h"

/// <summary>
/// カメラ
/// </summary>
class Camera
{
private:

	static float sWidth_;
	static float sHeight_;

	float aspect_ = 0.0f;
	float nearClip_ = 0.0f;
	float farClip_ = 0.0f;
	float angle_ = 0.0f;				//カメラ角度
	float distance_ = 50.0f;			//カメラ距離
	myMath::Matrix4 matView_;		//ビュー行列
	myMath::Matrix4 matViewInverse_;	//逆ビュー行列	
	myMath::Matrix4 matProjection_;	//射影行列
	myMath::Vector3 eye_;			//視点座標
	myMath::Vector3 target_;			//注視点座標
	myMath::Vector3 up_;				//上方向ベクトル

	//bool projectionFlag = false;	//平行投影と透視投影を切り替えるフラグ

public:

	static void StaticInitialize(WindowsApp* windowsApp);

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
	/// 投影計算
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
	void SetEye(const myMath::Vector3& eye);
	void SetTarget(const myMath::Vector3& target);
	void SetUp(const myMath::Vector3& up);
	void SetNearClip(const float nearClip);
	void SetFarClip(const float farClip);
};