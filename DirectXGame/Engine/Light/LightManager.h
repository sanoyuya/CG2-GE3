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
public://�萔

	static const uint8_t DirLightNum = 3;
	static const uint8_t PointLightNum = 3;
	static const uint8_t SpotLightNum = 3;
	static const uint8_t CircleShadowNum = 1;

public://�T�u�N���X

	//�萔�o�b�t�@�p�\����
	struct ConstBufferData
	{
		//�����̐F
		myMath::Vector3 ambientColor;
		float pad1;
		//���s�����p
		DirectionalLight::ConstBufferData dirLights[DirLightNum];
		//�_�����p
		PointLight::ConstBufferData pointLights[PointLightNum];
		//�X�|�b�g���C�g�p
		SpotLight::ConstBufferData spotLights[SpotLightNum];
		//�ۉe�p
		CircleShadow::ConstBufferData circleShadows[CircleShadowNum];
	};

private://�ÓI�����o�ϐ�

	//�f�o�C�X
	static Microsoft::WRL::ComPtr<ID3D12Device> sDevice_;

public://�ÓI�����o�֐�

	static void StaticInitialize(ID3D12Device* device_);

	/// <summary>
	/// �C���X�^���X����
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static LightManager* Create();

private://�����o�ϐ�

	//�萔�o�b�t�@
	std::unique_ptr<ConstantBuffer> constBuff_;
	//�����̐F
	myMath::Vector3 ambientColor_ = { 1,1,1 };
	//���s�����̔z��
	DirectionalLight dirLights_[DirLightNum];
	//�_�����̔z��
	PointLight pointLights_[PointLightNum];
	//�X�|�b�g���C�g�̔z��
	SpotLight spotLights_[SpotLightNum];
	//�ۉe�̔z��
	CircleShadow circleShadows_[CircleShadowNum];
	//�_�[�e�B�t���O
	bool dirty_ = false;

public:
	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList, uint32_t rootParameterIndex);

	/// <summary>
	/// �萔�o�b�t�@�]��
	/// </summary>
	void TransferConstBuffer();

	/// <summary>
	/// �����̃��C�g���Z�b�g
	/// </summary>
	/// <param name="color">���C�g�̐F</param>
	void SetAmbientColor(const myMath::Vector3& color);

#pragma region DirLight

	/// <summary>
	/// ���s�����̗L���t���O���Z�b�g
	/// </summary>
	/// <param name="index">���C�g�ԍ�</param>
	/// <param name="active">�L���t���O</param>
	void SetDirLightActive(int8_t index, bool active);

	/// <summary>
	/// ���s�����̃��C�g�������Z�b�g
	/// </summary>
	/// <param name="index">���C�g�ԍ�</param>
	/// <param name="lightDer">���C�g����</param>
	void SetDirLightDir(int8_t index, const myMath::Vector4& lightDir);

	/// <summary>
	/// ���s�����̃��C�g�̐F���Z�b�g
	/// </summary>
	/// <param name="index">���C�g�ԍ�</param>
	/// <param name="lightColor">���C�g�̐F</param>
	void SetDirLightColor(int8_t index, const myMath::Vector3& lightColor);

#pragma endregion

#pragma region PointLight

	/// <summary>
	/// �_�����̗L���t���O���Z�b�g
	/// </summary>
	/// <param name="index">���C�g�ԍ�</param>
	/// <param name="active">�L���t���O</param>
	void SetPointLightActive(int8_t index, bool active);

	/// <summary>
	/// �_�����̍��W���Z�b�g
	/// </summary>
	/// <param name="index">���C�g�ԍ�</param>
	/// <param name="lightPos">���W</param>
	void SetPointLightPos(int8_t index, const myMath::Vector3& lightPos);

	/// <summary>
	/// �_�����̃��C�g�̐F���Z�b�g
	/// </summary>
	/// <param name="index">���C�g�ԍ�</param>
	/// <param name="lightColor">���C�g�̐F</param>
	void SetPointLightColor(int8_t index, const myMath::Vector3& lightColor);

	/// <summary>
	/// �_�����̋��������W�����Z�b�g
	/// </summary>
	/// <param name="index">���C�g�ԍ�</param>
	/// <param name="lightAtten">���������W��</param>
	void SetPointLightAtten(int8_t index, const myMath::Vector3& lightAtten);

#pragma endregion

#pragma region �X�|�b�g���C�g

	void SetSpotLightActive(int8_t index, bool active);
	void SetSpotLightDir(int8_t index, const myMath::Vector4& lightDir);
	void SetSpotLightPos(int8_t index, const myMath::Vector3& lightPos);
	void SetSpotLightColor(int8_t index, const myMath::Vector3& lightColor);
	void SetSpotLightAtten(int8_t index, const myMath::Vector3& lightAtten);
	void SetSpotLightFactorAngle(int8_t index, const myMath::Vector2& lightFactorAngle);

#pragma endregion

#pragma region �ۉe

	void SetCircleShadowActive(int8_t index, bool active);
	void SetCircleShadowCasterPos(int8_t index, const myMath::Vector3& casterPos);
	void SetCircleShadowDir(int8_t index, const myMath::Vector4& lightdir);
	void SetCircleShadowDistanceCasterLight(int8_t index, float distanceCasterLight);
	void SetCircleShadowAtten(int8_t index, const myMath::Vector3& lightAtten);
	void SetCircleShadowFactorAngle(int8_t index, const myMath::Vector2& lightFactorAngle);

#pragma endregion
};