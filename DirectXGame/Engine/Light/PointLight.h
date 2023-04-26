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
		unsigned int active;
	};

private://メンバ変数
	//ライト座標(ワールド座標系)
	myMath::Vector3 lightPos = { 0,0,0 };
	//ライトの色
	myMath::Vector3 lightColor = { 1,1,1 };
	//ライト距離減衰係数
	myMath::Vector3 lightAtten = { 1.0f,1.0f ,1.0f };
	//有効フラグ
	bool active = false;

public://メンバ関数

	inline void SetLightPos(const myMath::Vector3& lightPos_) { lightPos = lightPos_; }
	inline const myMath::Vector3& GetLightPos() { return lightPos; }
	inline void SetLightColor(const myMath::Vector3& lightColor_) { lightColor = lightColor_; }
	inline const myMath::Vector3& GetLightColor() { return lightColor; }
	inline void SetLightAtten(const myMath::Vector3& lightAtten_) { lightAtten = lightAtten_; }
	inline const myMath::Vector3& GetLightAtten() { return lightAtten; }
	inline void SetActive(bool active_) { active = active_; }
	inline bool IsActive() { return active; }
};