#pragma once
#include"myMath.h"

/// <summary>
/// スポットライト
/// </summary>
class SpotLight
{
public://サブクラス

	//定数バッファ用データ構造体
	struct ConstBufferData
	{
		myMath::Vector4 lightv;
		myMath::Vector3 lightPos;
		float pad1;
		myMath::Vector3 lightColor;
		float pad2;
		myMath::Vector3 lightAtten;
		float pad3;
		myMath::Vector2 lightActorAngleCos;
		bool active;
		float pad4;
	};

private://メンバ変数

	//ライト方向(単位ベクトル)
	myMath::Vector4 lightDir_ = { 1,0,0,0 };
	//ライト座標(ワールド座標系)
	myMath::Vector3 lightPos_ = { 0,0,0 };
	//ライトの色
	myMath::Vector3 lightColor_ = { 1,1,1 };
	//ライト距離減衰係数
	myMath::Vector3 lightAtten_ = { 1.0f,1.0f ,1.0f };
	//ライト減衰角度(開始角度、終了角度)
	myMath::Vector2 lightFactorAngleCos_ = { 0.5f,0.2f };
	//有効フラグ
	bool active_ = false;

public://メンバ関数

	inline void SetLightDir(const myMath::Vector4& lightDir) { lightDir_ = lightDir.normalization(); }
	inline const myMath::Vector4& GetLightDir() { return lightDir_; }
	inline void SetLightPos(const myMath::Vector3& lightPos) { lightPos_ = lightPos; }
	inline const myMath::Vector3& GetLightPos() { return lightPos_; }
	inline void SetLightColor(const myMath::Vector3& lightColor) { lightColor_ = lightColor; }
	inline const myMath::Vector3& GetLightColor() { return lightColor_; }
	inline void SetLightAtten(const myMath::Vector3& lightAtten) { lightAtten_ = lightAtten; }
	inline const myMath::Vector3& GetLightAtten() { return lightAtten_; }
	inline void SetLightFactorAngle(const myMath::Vector2& lightFactorAngle)
	{
		lightFactorAngleCos_.x = cosf(DirectX::XMConvertToRadians(lightFactorAngle.x));
		lightFactorAngleCos_.y = cosf(DirectX::XMConvertToRadians(lightFactorAngle.y));
	}
	inline const myMath::Vector2& GetLightFactorAngleCos() { return lightFactorAngleCos_; }
	inline void SetActive(bool active) { active_ = active; }
	inline bool IsActive() { return active_; }
};