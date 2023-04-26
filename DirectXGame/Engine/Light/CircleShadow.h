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
	myMath::Vector4 dir = { 1,0,0,0 };
	//キャスターとライトの距離
	float distanceCasterLight = 100.0f;
	//キャスター座標(ワールド座標系)
	myMath::Vector3 casterPos = { 0,0,0 };
	//距離減衰係数
	myMath::Vector3 atten = { 0.5f,0.6f,0.0f };
	//減衰角度
	myMath::Vector2 factorAngleCos = { 0.2f,0.5f };
	//有効フラグ
	bool active = false;

public://メンバ関数
	inline void SetDir(const myMath::Vector4& dir_) { dir = dir_.normalization(); }
	inline const myMath::Vector4& GetDir() { return dir; }
	inline void SetCasterPos(const myMath::Vector3& casterPos_) { casterPos = casterPos_; }
	inline const myMath::Vector3& GetCasterPos() { return casterPos; }
	inline void SetDistanceCasterLight(float distanceCasterlight_) { distanceCasterLight = distanceCasterlight_; }
	inline float GetDistanceCasterLight() { return distanceCasterLight; }
	inline void SetAtten(const myMath::Vector3& atten_) { atten = atten_; }
	inline const myMath::Vector3& GetAtten() { return atten; }
	inline void SetFactorAngle(const myMath::Vector2& factorAngleCos_)
	{
		factorAngleCos.x = cosf(DirectX::XMConvertToRadians(factorAngleCos_.x));
		factorAngleCos.y = cosf(DirectX::XMConvertToRadians(factorAngleCos_.y));
	}
	inline const myMath::Vector2& GetFactorAngleCos() { return factorAngleCos; }
	inline void SetActive(bool active_) { active = active_; }
	inline bool IsActive() { return active; }
};