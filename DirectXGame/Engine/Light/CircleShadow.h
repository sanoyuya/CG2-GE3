#pragma once
#include"myMath.h"

/// <summary>
/// 丸影
/// </summary>
class CircleShadow
{
public://サブクラス

	//定数バッファ用データ構造体
	struct ConstBufferData
	{
		myMath::Vector4 dir;
		myMath::Vector3 casterPos;
		float distanceCasterLight;
		myMath::Vector3 atten;
		float pad3;
		myMath::Vector2 factorAngleCos;
		bool active;
		float pad4;
	};

private://メンバ変数

	//方向(単位ベクトル)
	myMath::Vector4 dir_ = { 1,0,0,0 };
	//キャスターとライトの距離
	float distanceCasterLight_ = 100.0f;
	//キャスター座標(ワールド座標系)
	myMath::Vector3 casterPos_ = { 0,0,0 };
	//距離減衰係数
	myMath::Vector3 atten_ = { 0.5f,0.6f,0.0f };
	//減衰角度
	myMath::Vector2 factorAngleCos_ = { 0.2f,0.5f };
	//有効フラグ
	bool active_ = false;

public://メンバ関数

	inline void SetDir(const myMath::Vector4& dir) { dir_ = dir.normalization(); }
	inline const myMath::Vector4& GetDir() { return dir_; }
	inline void SetCasterPos(const myMath::Vector3& casterPos) { casterPos_ = casterPos; }
	inline const myMath::Vector3& GetCasterPos() { return casterPos_; }
	inline void SetDistanceCasterLight(float distanceCasterlight) { distanceCasterLight_ = distanceCasterlight; }
	inline float GetDistanceCasterLight() { return distanceCasterLight_; }
	inline void SetAtten(const myMath::Vector3& atten) { atten_ = atten; }
	inline const myMath::Vector3& GetAtten() { return atten_; }
	inline void SetFactorAngle(const myMath::Vector2& factorAngleCos)
	{
		factorAngleCos_.x = cosf(DirectX::XMConvertToRadians(factorAngleCos.x));
		factorAngleCos_.y = cosf(DirectX::XMConvertToRadians(factorAngleCos.y));
	}
	inline const myMath::Vector2& GetFactorAngleCos() { return factorAngleCos_; }
	inline void SetActive(bool active) { active_ = active; }
	inline bool IsActive() { return active_; }
};