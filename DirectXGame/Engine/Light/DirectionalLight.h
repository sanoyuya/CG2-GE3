#pragma once
#include"myMath.h"

/// <summary>
/// ライト
/// </summary>
class DirectionalLight
{
public://サブクラス
	//定数バッファ用データ構造体
	struct ConstBufferData
	{
		myMath::Vector4 lightv;//ライトへの方向を表すベクトル
		myMath::Vector3 lightcolor;//ライトの色
		bool active;
	};

private:

	//ライト光線方向(単位ベクトル)
	myMath::Vector4 lightdir = { 1,0,0,0 };
	//ライト色
	myMath::Vector3 lightcolor = { 1,1,1 };
	//ダーティフラグ
	bool dirty = false;
	//有効フラグ
	bool active = false;

public:

	/// <summary>
	/// ライト方向をセット
	/// </summary>
	/// <param name="light">ライト方向</param>
	inline void SetLightDir(const myMath::Vector4& lightdir_){ lightdir = lightdir_.normalization(); }
	inline const myMath::Vector4& GetLightDir() { return lightdir; }

	/// <summary>
	/// ライト色をセット
	/// </summary>
	/// <param name="lightcolor">ライト色</param>
	inline void SetLightColor(const myMath::Vector3& lightcolor_) { lightcolor = lightcolor_; }
	inline const myMath::Vector3& GetLightColor() { return lightcolor; }

	/// <summary>
	/// 有効フラグをセット
	/// </summary>
	/// <param name="active">有効フラグ</param>
	inline void SetActive(bool active_) { active = active_; }

	/// <summary>
	/// 有効チェック
	/// </summary>
	/// <returns>有効フラグ</returns>
	inline bool IsActive() { return active; }
};