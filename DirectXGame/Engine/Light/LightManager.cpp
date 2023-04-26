#include "LightManager.h"

/// <summary>
/// 静的メンバ変数の実態
/// </summary>
ID3D12Device* LightManager::device = nullptr;

void LightManager::StaticInitialize(ID3D12Device* device_)
{
	//再初期化チェック
	assert(!LightManager::device);

	//nullptrチェック
	assert(device_);

	LightManager::device = device_;
}

LightManager* LightManager::Create()
{
	//3Dオブジェクトのインスタンスを生成
	LightManager* instance = new LightManager();

	//初期化
	instance->Initialize();

	return instance;
}

void LightManager::Initialize()
{
	// nullptrチェック
	assert(device);

	constBuff = std::make_unique<ConstantBuffer>();
	constBuff->Create(sizeof(ConstBufferData));

	TransferConstBuffer();
}

void LightManager::Update()
{
	//値の更新があった時だけ定数バッファに転送する
	if (dirty)
	{
		TransferConstBuffer();
		dirty = false;
	}
}

void LightManager::Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex)
{
	//定数バッファビューをセット
	cmdList->SetGraphicsRootConstantBufferView(rootParameterIndex, constBuff->GetAddress());
}

void LightManager::TransferConstBuffer()
{
	HRESULT result = FALSE;
	//定数バッファへデータ転送
	ConstBufferData constMap = {};
	//constMap = new ConstBufferData;
	
	if (SUCCEEDED(result)) {

		constMap.ambientColor = ambientColor;

		//平行光源
		for (int i = 0; i < DirLightNum; i++)
		{
			//ライトが有効の時のみ設定を転送
			if (dirLights[i].IsActive())
			{
				constMap.dirLights[i].active = true;
				constMap.dirLights[i].lightv = -dirLights[i].GetLightDir();
				constMap.dirLights[i].lightcolor = dirLights[i].GetLightColor();
			}
			//ライトが無効なら転送しない
			else
			{
				constMap.dirLights[i].active = false;
			}
		}

		//点光源
		for (int i = 0; i < PointLightNum; i++)
		{
			//ライトが有効なら設定を転送
			if (pointLights[i].IsActive())
			{
				constMap.pointLights[i].active = 1;
				constMap.pointLights[i].lightPos = pointLights[i].GetLightPos();
				constMap.pointLights[i].lightColor = pointLights[i].GetLightColor();
				constMap.pointLights[i].lightAtten = pointLights[i].GetLightAtten();
			}
			else
			{
				constMap.pointLights[i].active = 0;
			}
		}

		//スポットライト
		for (int i = 0; i < SpotLightNum; i++)
		{
			//ライトが有効なら設定を転送
			if (spotLights[i].IsActive())
			{
				constMap.spotLights[i].active = true;
				constMap.spotLights[i].lightv = -spotLights[i].GetLightDir();
				constMap.spotLights[i].lightPos = spotLights[i].GetLightPos();
				constMap.spotLights[i].lightColor = spotLights[i].GetLightColor();
				constMap.spotLights[i].lightAtten = spotLights[i].GetLightAtten();
				constMap.spotLights[i].lightActorAngleCos = spotLights[i].GetLightFactorAngleCos();
			}
			//ライトが無効ならライトの色を0に
			else
			{
				constMap.spotLights[i].active = false;
			}
		}

		//丸影
		for (int i = 0; i < CircleShadowNum; i++)
		{
			//ライトが有効なら設定を転送
			if (circleShadows[i].IsActive())
			{
				constMap.circleShadows[i].dir = -circleShadows[i].GetDir();
				constMap.circleShadows[i].active = true;
				constMap.circleShadows[i].casterPos = circleShadows[i].GetCasterPos();
				constMap.circleShadows[i].distanceCasterLight = circleShadows[i].GetDistanceCasterLight();
				constMap.circleShadows[i].atten = circleShadows[i].GetAtten();
				constMap.circleShadows[i].factorAngleCos = circleShadows[i].GetFactorAngleCos();
			}
			//ライトが無効ならライトの色を0に
			else
			{
				constMap.circleShadows[i].active = false;
			}
		}

		constBuff->Update(&constMap);
	}
}

void LightManager::SetAmbientColor(const myMath::Vector3& color)
{
	ambientColor = color;
	dirty = true;
}

void LightManager::SetDirLightActive(int index, bool active)
{
	assert(0 <= index && index < DirLightNum);
	dirLights[index].SetActive(active);
}

void LightManager::SetDirLightDir(int index, const myMath::Vector4& lightDir)
{
	assert(0 <= index && index < DirLightNum);
	dirLights[index].SetLightDir(lightDir);
	dirty = true;
}

void LightManager::SetDirLightColor(int index, const myMath::Vector3& lightColor)
{
	assert(0 <= index && index < DirLightNum);
	dirLights[index].SetLightColor(lightColor);
	dirty = true;
}

void LightManager::SetPointLightActive(int index, bool active)
{
	assert(0 <= index && index < PointLightNum);

	pointLights[index].SetActive(active);
}

void LightManager::SetPointLightPos(int index, const myMath::Vector3& lightPos)
{
	assert(0 <= index && index < PointLightNum);

	pointLights[index].SetLightPos(lightPos);
	dirty = true;
}

void LightManager::SetPointLightColor(int index, const myMath::Vector3& lightColor)
{
	assert(0 <= index && index < PointLightNum);

	pointLights[index].SetLightColor(lightColor);
	dirty = true;
}

void LightManager::SetPointLightAtten(int index, const myMath::Vector3& lightAtten)
{
	assert(0 <= index && index < PointLightNum);

	pointLights[index].SetLightAtten(lightAtten);
	dirty = true;
}

void LightManager::SetSpotLightActive(int index, bool active)
{
	assert(0 <= index && index < SpotLightNum);

	spotLights[index].SetActive(active);
}

void LightManager::SetSpotLightDir(int index, const myMath::Vector4& lightDir)
{
	assert(0 <= index && index < SpotLightNum);

	spotLights[index].SetLightDir(lightDir);
	dirty = true;
}

void LightManager::SetSpotLightPos(int index, const myMath::Vector3& lightPos)
{
	assert(0 <= index && index < SpotLightNum);

	spotLights[index].SetLightPos(lightPos);
	dirty = true;
}

void LightManager::SetSpotLightColor(int index, const myMath::Vector3& lightColor)
{
	assert(0 <= index && index < SpotLightNum);

	spotLights[index].SetLightColor(lightColor);
	dirty = true;
}

void LightManager::SetSpotLightAtten(int index, const myMath::Vector3& lightAtten)
{
	assert(0 <= index && index < SpotLightNum);

	spotLights[index].SetLightAtten(lightAtten);
	dirty = true;
}

void LightManager::SetSpotLightFactorAngle(int index, const myMath::Vector2& lightFactorAngle)
{
	assert(0 <= index && index < SpotLightNum);

	spotLights[index].SetLightFactorAngle(lightFactorAngle);
	dirty = true;
}

void LightManager::SetCircleShadowActive(int index, bool active)
{
	assert(0 <= index && index < CircleShadowNum);

	circleShadows[index].SetActive(active);
}

void LightManager::SetCircleShadowCasterPos(int index, const myMath::Vector3& casterPos)
{
	assert(0 <= index && index < CircleShadowNum);

	circleShadows[index].SetCasterPos(casterPos);
	dirty = true;
}

void LightManager::SetCircleShadowDir(int index, const myMath::Vector4& lightdir)
{
	assert(0 <= index && index < CircleShadowNum);

	circleShadows[index].SetDir(lightdir);
	dirty = true;
}

void LightManager::SetCircleShadowDistanceCasterLight(int index, float distanceCasterLight)
{
	assert(0 <= index && index < CircleShadowNum);

	circleShadows[index].SetDistanceCasterLight(distanceCasterLight);
	dirty = true;
}

void LightManager::SetCircleShadowAtten(int index, const myMath::Vector3& lightAtten)
{
	assert(0 <= index && index < CircleShadowNum);

	circleShadows[index].SetAtten(lightAtten);
	dirty = true;
}

void LightManager::SetCircleShadowFactorAngle(int index, const myMath::Vector2& lightFactorAngle)
{
	assert(0 <= index && index < CircleShadowNum);

	circleShadows[index].SetFactorAngle(lightFactorAngle);
	dirty = true;
}