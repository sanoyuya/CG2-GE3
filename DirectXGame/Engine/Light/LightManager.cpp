#include "LightManager.h"

/// <summary>
/// �ÓI�����o�ϐ��̎���
/// </summary>
ID3D12Device* LightManager::device = nullptr;

void LightManager::StaticInitialize(ID3D12Device* device_)
{
	//�ď������`�F�b�N
	assert(!LightManager::device);

	//nullptr�`�F�b�N
	assert(device_);

	LightManager::device = device_;
}

LightManager* LightManager::Create()
{
	//3D�I�u�W�F�N�g�̃C���X�^���X�𐶐�
	LightManager* instance = new LightManager();

	//������
	instance->Initialize();

	return instance;
}

void LightManager::Initialize()
{
	// nullptr�`�F�b�N
	assert(device);

	constBuff = std::make_unique<ConstantBuffer>();
	constBuff->Create(sizeof(ConstBufferData));

	TransferConstBuffer();
}

void LightManager::Update()
{
	//�l�̍X�V���������������萔�o�b�t�@�ɓ]������
	if (dirty)
	{
		TransferConstBuffer();
		dirty = false;
	}
}

void LightManager::Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex)
{
	//�萔�o�b�t�@�r���[���Z�b�g
	cmdList->SetGraphicsRootConstantBufferView(rootParameterIndex, constBuff->GetAddress());
}

void LightManager::TransferConstBuffer()
{
	HRESULT result = FALSE;
	//�萔�o�b�t�@�փf�[�^�]��
	ConstBufferData constMap = {};
	//constMap = new ConstBufferData;
	
	if (SUCCEEDED(result)) {

		constMap.ambientColor = ambientColor;

		//���s����
		for (int i = 0; i < DirLightNum; i++)
		{
			//���C�g���L���̎��̂ݐݒ��]��
			if (dirLights[i].IsActive())
			{
				constMap.dirLights[i].active = true;
				constMap.dirLights[i].lightv = -dirLights[i].GetLightDir();
				constMap.dirLights[i].lightcolor = dirLights[i].GetLightColor();
			}
			//���C�g�������Ȃ�]�����Ȃ�
			else
			{
				constMap.dirLights[i].active = false;
			}
		}

		//�_����
		for (int i = 0; i < PointLightNum; i++)
		{
			//���C�g���L���Ȃ�ݒ��]��
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

		//�X�|�b�g���C�g
		for (int i = 0; i < SpotLightNum; i++)
		{
			//���C�g���L���Ȃ�ݒ��]��
			if (spotLights[i].IsActive())
			{
				constMap.spotLights[i].active = true;
				constMap.spotLights[i].lightv = -spotLights[i].GetLightDir();
				constMap.spotLights[i].lightPos = spotLights[i].GetLightPos();
				constMap.spotLights[i].lightColor = spotLights[i].GetLightColor();
				constMap.spotLights[i].lightAtten = spotLights[i].GetLightAtten();
				constMap.spotLights[i].lightActorAngleCos = spotLights[i].GetLightFactorAngleCos();
			}
			//���C�g�������Ȃ烉�C�g�̐F��0��
			else
			{
				constMap.spotLights[i].active = false;
			}
		}

		//�ۉe
		for (int i = 0; i < CircleShadowNum; i++)
		{
			//���C�g���L���Ȃ�ݒ��]��
			if (circleShadows[i].IsActive())
			{
				constMap.circleShadows[i].dir = -circleShadows[i].GetDir();
				constMap.circleShadows[i].active = true;
				constMap.circleShadows[i].casterPos = circleShadows[i].GetCasterPos();
				constMap.circleShadows[i].distanceCasterLight = circleShadows[i].GetDistanceCasterLight();
				constMap.circleShadows[i].atten = circleShadows[i].GetAtten();
				constMap.circleShadows[i].factorAngleCos = circleShadows[i].GetFactorAngleCos();
			}
			//���C�g�������Ȃ烉�C�g�̐F��0��
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