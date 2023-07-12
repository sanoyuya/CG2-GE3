#pragma once
#include"myMath.h"
#include<wrl.h>
#include <d3d12.h>
#include"DirectionalLight.h"
#include"PointLight.h"
#include"SpotLight.h"
#include"CircleShadow.h"
#include"ConstantBuffer.h"
#include"memory"

class LightManager
{
public://定数

	static const uint8_t DirLightNum = 3;
	static const uint8_t PointLightNum = 3;
	static const uint8_t SpotLightNum = 3;
	static const uint8_t CircleShadowNum = 1;

public://サブクラス

	//定数バッファ用構造体
	struct ConstBufferData
	{
		//環境光の色
		myMath::Vector3 ambientColor;
		float pad1;
		//平行光源用
		DirectionalLight::ConstBufferData dirLights[DirLightNum];
		//点光源用
		PointLight::ConstBufferData pointLights[PointLightNum];
		//スポットライト用
		SpotLight::ConstBufferData spotLights[SpotLightNum];
		//丸影用
		CircleShadow::ConstBufferData circleShadows[CircleShadowNum];
	};

private://静的メンバ変数

	//デバイス
	static Microsoft::WRL::ComPtr<ID3D12Device> sDevice_;

public://静的メンバ関数

	static void StaticInitialize(ID3D12Device* device_);

	/// <summary>
	/// インスタンス生成
	/// </summary>
	/// <returns>インスタンス</returns>
	static LightManager* Create();

private://メンバ変数

	//定数バッファ
	std::unique_ptr<ConstantBuffer> constBuff_;
	//環境光の色
	myMath::Vector3 ambientColor_ = { 1,1,1 };
	//平行光源の配列
	DirectionalLight dirLights_[DirLightNum];
	//点光源の配列
	PointLight pointLights_[PointLightNum];
	//スポットライトの配列
	SpotLight spotLights_[SpotLightNum];
	//丸影の配列
	CircleShadow circleShadows_[CircleShadowNum];
	//ダーティフラグ
	bool dirty_ = false;

public:
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList, uint32_t rootParameterIndex);

	/// <summary>
	/// 定数バッファ転送
	/// </summary>
	void TransferConstBuffer();

	/// <summary>
	/// 環境光のライトをセット
	/// </summary>
	/// <param name="color">ライトの色</param>
	void SetAmbientColor(const myMath::Vector3& color);

#pragma region DirLight

	/// <summary>
	/// 平行光源の有効フラグをセット
	/// </summary>
	/// <param name="index">ライト番号</param>
	/// <param name="active">有効フラグ</param>
	void SetDirLightActive(int8_t index, bool active);

	/// <summary>
	/// 平行光源のライト方向をセット
	/// </summary>
	/// <param name="index">ライト番号</param>
	/// <param name="lightDer">ライト方向</param>
	void SetDirLightDir(int8_t index, const myMath::Vector4& lightDir);

	/// <summary>
	/// 平行光源のライトの色をセット
	/// </summary>
	/// <param name="index">ライト番号</param>
	/// <param name="lightColor">ライトの色</param>
	void SetDirLightColor(int8_t index, const myMath::Vector3& lightColor);

#pragma endregion

#pragma region PointLight

	/// <summary>
	/// 点光源の有効フラグをセット
	/// </summary>
	/// <param name="index">ライト番号</param>
	/// <param name="active">有効フラグ</param>
	void SetPointLightActive(int8_t index, bool active);

	/// <summary>
	/// 点光源の座標をセット
	/// </summary>
	/// <param name="index">ライト番号</param>
	/// <param name="lightPos">座標</param>
	void SetPointLightPos(int8_t index, const myMath::Vector3& lightPos);

	/// <summary>
	/// 点光源のライトの色をセット
	/// </summary>
	/// <param name="index">ライト番号</param>
	/// <param name="lightColor">ライトの色</param>
	void SetPointLightColor(int8_t index, const myMath::Vector3& lightColor);

	/// <summary>
	/// 点光源の距離減衰係数をセット
	/// </summary>
	/// <param name="index">ライト番号</param>
	/// <param name="lightAtten">距離減衰係数</param>
	void SetPointLightAtten(int8_t index, const myMath::Vector3& lightAtten);

#pragma endregion

#pragma region スポットライト

	void SetSpotLightActive(int8_t index, bool active);
	void SetSpotLightDir(int8_t index, const myMath::Vector4& lightDir);
	void SetSpotLightPos(int8_t index, const myMath::Vector3& lightPos);
	void SetSpotLightColor(int8_t index, const myMath::Vector3& lightColor);
	void SetSpotLightAtten(int8_t index, const myMath::Vector3& lightAtten);
	void SetSpotLightFactorAngle(int8_t index, const myMath::Vector2& lightFactorAngle);

#pragma endregion

#pragma region 丸影

	void SetCircleShadowActive(int8_t index, bool active);
	void SetCircleShadowCasterPos(int8_t index, const myMath::Vector3& casterPos);
	void SetCircleShadowDir(int8_t index, const myMath::Vector4& lightdir);
	void SetCircleShadowDistanceCasterLight(int8_t index, float distanceCasterLight);
	void SetCircleShadowAtten(int8_t index, const myMath::Vector3& lightAtten);
	void SetCircleShadowFactorAngle(int8_t index, const myMath::Vector2& lightFactorAngle);

#pragma endregion
};