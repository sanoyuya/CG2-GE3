#include "LightManager.h"

/// <summary>
/// �ÓI�����o�ϐ��̎���
/// </summary>
Microsoft::WRL::ComPtr<ID3D12Device> LightManager::sDevice_ = nullptr;

void LightManager::StaticInitialize(ID3D12Device* device_)
{
	//�ď������`�F�b�N
	assert(!LightManager::sDevice_);

	//nullptr�`�F�b�N
	assert(device_);

	LightManager::sDevice_ = device_;
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
	assert(sDevice_);

	constBuff_ = std::make_unique<ConstantBuffer>();
	constBuff_->Create(sizeof(ConstBufferData));

	TransferConstBuffer();
}

void LightManager::Update()
{
	//�l�̍X�V���������������萔�o�b�t�@�ɓ]������
	if (dirty_)
	{
		TransferConstBuffer();
		dirty_ = false;
	}
}

void LightManager::Draw(ID3D12GraphicsCommandList* cmdList, uint32_t rootParameterIndex)
{
	//�萔�o�b�t�@�r���[���Z�b�g
	cmdList->SetGraphicsRootConstantBufferView(rootParameterIndex, constBuff_->GetAddress());
}

void LightManager::TransferConstBuffer()
{
	HRESULT result = FALSE;
	//�萔�o�b�t�@�փf�[�^�]��
	ConstBufferData constMap = {};
	//constMap = new ConstBufferData;
	
	if (SUCCEEDED(result)) {

		constMap.ambientColor = ambientColor_;

		//���s����
		for (int8_t i = 0; i < DirLightNum; i++)
		{
			//���C�g���L���̎��̂ݐݒ��]��
			if (dirLights_[i].IsActive())
			{
				constMap.dirLights[i].active = true;
				constMap.dirLights[i].lightv = -dirLights_[i].GetLightDir();
				constMap.dirLights[i].lightcolor = dirLights_[i].GetLightColor();
			}
			//���C�g�������Ȃ�]�����Ȃ�
			else
			{
				constMap.dirLights[i].active = false;
			}
		}

		//�_����
		for (int8_t i = 0; i < PointLightNum; i++)
		{
			//���C�g���L���Ȃ�ݒ��]��
			if (pointLights_[i].IsActive())
			{
				constMap.pointLights[i].active = 1;
				constMap.pointLights[i].lightPos = pointLights_[i].GetLightPos();
				constMap.pointLights[i].lightColor = pointLights_[i].GetLightColor();
				constMap.pointLights[i].lightAtten = pointLights_[i].GetLightAtten();
			}
			else
			{
				constMap.pointLights[i].active = 0;
			}
		}

		//�X�|�b�g���C�g
		for (int8_t i = 0; i < SpotLightNum; i++)
		{
			//���C�g���L���Ȃ�ݒ��]��
			if (spotLights_[i].IsActive())
			{
				constMap.spotLights[i].active = true;
				constMap.spotLights[i].lightv = -spotLights_[i].GetLightDir();
				constMap.spotLights[i].lightPos = spotLights_[i].GetLightPos();
				constMap.spotLights[i].lightColor = spotLights_[i].GetLightColor();
				constMap.spotLights[i].lightAtten = spotLights_[i].GetLightAtten();
				constMap.spotLights[i].lightActorAngleCos = spotLights_[i].GetLightFactorAngleCos();
			}
			//���C�g�������Ȃ烉�C�g�̐F��0��
			else
			{
				constMap.spotLights[i].active = false;
			}
		}

		//�ۉe
		for (int8_t i = 0; i < CircleShadowNum; i++)
		{
			//���C�g���L���Ȃ�ݒ��]��
			if (circleShadows_[i].IsActive())
			{
				constMap.circleShadows[i].dir = -circleShadows_[i].GetDir();
				constMap.circleShadows[i].active = true;
				constMap.circleShadows[i].casterPos = circleShadows_[i].GetCasterPos();
				constMap.circleShadows[i].distanceCasterLight = circleShadows_[i].GetDistanceCasterLight();
				constMap.circleShadows[i].atten = circleShadows_[i].GetAtten();
				constMap.circleShadows[i].factorAngleCos = circleShadows_[i].GetFactorAngleCos();
			}
			//���C�g�������Ȃ烉�C�g�̐F��0��
			else
			{
				constMap.circleShadows[i].active = false;
			}
		}

		constBuff_->Update(&constMap);
	}
}

void LightManager::SetAmbientColor(const myMath::Vector3& color)
{
	ambientColor_ = color;
	dirty_ = true;
}

void LightManager::SetDirLightActive(int8_t index, bool active)
{
	assert(0 <= index && index < DirLightNum);
	dirLights_[index].SetActive(active);
}

void LightManager::SetDirLightDir(int8_t index, const myMath::Vector4& lightDir)
{
	assert(0 <= index && index < DirLightNum);
	dirLights_[index].SetLightDir(lightDir);
	dirty_ = true;
}

void LightManager::SetDirLightColor(int8_t index, const myMath::Vector3& lightColor)
{
	assert(0 <= index && index < DirLightNum);
	dirLights_[index].SetLightColor(lightColor);
	dirty_ = true;
}

void LightManager::SetPointLightActive(int8_t index, bool active)
{
	assert(0 <= index && index < PointLightNum);

	pointLights_[index].SetActive(active);
}

void LightManager::SetPointLightPos(int8_t index, const myMath::Vector3& lightPos)
{
	assert(0 <= index && index < PointLightNum);

	pointLights_[index].SetLightPos(lightPos);
	dirty_ = true;
}

void LightManager::SetPointLightColor(int8_t index, const myMath::Vector3& lightColor)
{
	assert(0 <= index && index < PointLightNum);

	pointLights_[index].SetLightColor(lightColor);
	dirty_ = true;
}

void LightManager::SetPointLightAtten(int8_t index, const myMath::Vector3& lightAtten)
{
	assert(0 <= index && index < PointLightNum);

	pointLights_[index].SetLightAtten(lightAtten);
	dirty_ = true;
}

void LightManager::SetSpotLightActive(int8_t index, bool active)
{
	assert(0 <= index && index < SpotLightNum);

	spotLights_[index].SetActive(active);
}

void LightManager::SetSpotLightDir(int8_t index, const myMath::Vector4& lightDir)
{
	assert(0 <= index && index < SpotLightNum);

	spotLights_[index].SetLightDir(lightDir);
	dirty_ = true;
}

void LightManager::SetSpotLightPos(int8_t index, const myMath::Vector3& lightPos)
{
	assert(0 <= index && index < SpotLightNum);

	spotLights_[index].SetLightPos(lightPos);
	dirty_ = true;
}

void LightManager::SetSpotLightColor(int8_t index, const myMath::Vector3& lightColor)
{
	assert(0 <= index && index < SpotLightNum);

	spotLights_[index].SetLightColor(lightColor);
	dirty_ = true;
}

void LightManager::SetSpotLightAtten(int8_t index, const myMath::Vector3& lightAtten)
{
	assert(0 <= index && index < SpotLightNum);

	spotLights_[index].SetLightAtten(lightAtten);
	dirty_ = true;
}

void LightManager::SetSpotLightFactorAngle(int8_t index, const myMath::Vector2& lightFactorAngle)
{
	assert(0 <= index && index < SpotLightNum);

	spotLights_[index].SetLightFactorAngle(lightFactorAngle);
	dirty_ = true;
}

void LightManager::SetCircleShadowActive(int8_t index, bool active)
{
	assert(0 <= index && index < CircleShadowNum);

	circleShadows_[index].SetActive(active);
}

void LightManager::SetCircleShadowCasterPos(int8_t index, const myMath::Vector3& casterPos)
{
	assert(0 <= index && index < CircleShadowNum);

	circleShadows_[index].SetCasterPos(casterPos);
	dirty_ = true;
}

void LightManager::SetCircleShadowDir(int8_t index, const myMath::Vector4& lightdir)
{
	assert(0 <= index && index < CircleShadowNum);

	circleShadows_[index].SetDir(lightdir);
	dirty_ = true;
}

void LightManager::SetCircleShadowDistanceCasterLight(int8_t index, float distanceCasterLight)
{
	assert(0 <= index && index < CircleShadowNum);

	circleShadows_[index].SetDistanceCasterLight(distanceCasterLight);
	dirty_ = true;
}

void LightManager::SetCircleShadowAtten(int8_t index, const myMath::Vector3& lightAtten)
{
	assert(0 <= index && index < CircleShadowNum);

	circleShadows_[index].SetAtten(lightAtten);
	dirty_ = true;
}

void LightManager::SetCircleShadowFactorAngle(int8_t index, const myMath::Vector2& lightFactorAngle)
{
	assert(0 <= index && index < CircleShadowNum);

	circleShadows_[index].SetFactorAngle(lightFactorAngle);
	dirty_ = true;
}