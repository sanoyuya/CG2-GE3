#pragma once
#include"myMath.h"

/// <summary>
/// 点光源
/// </summary>
class PointLight
{
public://サブクラス

	//定数バッファ用データ構造体
	struct ConstBufferData
	{
		myMath::Vector3 lightPos;
		float pad1;
		myMath::Vector3 lightColor;
		float pad2;
		myMath::Vector3 lightAtten;
		uint8_t active;
	};

private://メンバ変数

	//ライト座標(ワールド座標系)
	myMath::Vector3 lightPos_ = { 0,0,0 };
	//ライトの色
	myMath::Vector3 lightColor_ = { 1,1,1 };
	//ライト距離減衰係数
	myMath::Vector3 lightAtten_ = { 1.0f,1.0f ,1.0f };
	//有効フラグ
	bool active_ = false;

public://メンバ関数

	inline void SetLightPos(const myMath::Vector3& lightPos) { lightPos_ = lightPos; }
	inline const myMath::Vector3& GetLightPos() { return lightPos_; }
	inline void SetLightColor(const myMath::Vector3& lightColor) { lightColor_ = lightColor; }
	inline const myMath::Vector3& GetLightColor() { return lightColor_; }
	inline void SetLightAtten(const myMath::Vector3& lightAtten) { lightAtten_ = lightAtten; }
	inline const myMath::Vector3& GetLightAtten() { return lightAtten_; }
	inline void SetActive(bool active) { active_ = active; }
	inline bool IsActive() { return active_; }
};