#pragma once
#include <unordered_map>
#include"DrawCommon.h"
#include"TextureManager.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"ConstantBuffer.h"
#include"Transform.h"
#include"Pipeline.h"
#include"LightManager.h"

struct ModelData
{
	ModelData() = default;
	~ModelData() = default;

	std::string filePath;
	uint32_t modelHandle;

private:

	char PADING1[4] = {};

public:

	TextureData* textureData;

	//���_�o�b�t�@
	std::unique_ptr<VertexBuffer> vertexBuffer;
	//�C���f�b�N�X�o�b�t�@
	std::unique_ptr<IndexBuffer> indexBuffer;

private:

	char PADING2[4] = {};

public:

	//�C���f�b�N�X�̐�
	uint32_t maxIndex = 0;

private:

	char PADING3[4] = {};

public:

	//���_�̐�
	uint32_t maxVert = 0;
	//���[���h�s��
	myMath::Matrix4 matWorld;
	//���_�f�[�^
	std::vector<PosNormalUv>vertices;
	//���_�C���f�b�N�X
	std::vector<uint32_t> indices;
	//���_�@���X���[�W���O�p�f�[�^
	std::unordered_map<uint32_t, std::vector<uint32_t>>smoothData;
	//�}�e���A��
	ModelMaterial modelMaterial{};
	// �萔�o�b�t�@
	std::unique_ptr<ConstantBuffer> constBuffMaterial;

	// �萔�o�b�t�@�r���[�̐ݒ�
	D3D12_CONSTANT_BUFFER_VIEW_DESC constantBufferView = {};

private:

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	ModelData& operator=(const ModelData&) = delete;
	ModelData(const ModelData&) = delete;
};

class Model
{
protected:

	static Microsoft::WRL::ComPtr<ID3D12Device> sDevice_;
	static Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> sCmdList_;

	static std::vector<std::string>sFilePaths_;

	static std::unordered_map<std::string, std::unique_ptr<ModelData>> sModelDatas_;

	static uint32_t sModelCount_;

	static const uint32_t sMaxModel_ = 1024;

	ModelData* modelData_ = nullptr;

private:

	static std::array<Blob,6> sBlob_;//�V�F�[�_�I�u�W�F�N�g

	static std::array<std::array<PipelineSet, 6>,6> sPip_;

	BlendMode blendMode_ = BlendMode::Alpha;//�����l����������

	static ShaderMode sShaderMode_;

	ShaderMode shaderMode_ = sShaderMode_;//�W��

	std::unique_ptr<ConstantBuffer> constantBuff_;

	myMath::Vector4 tmp_;

	//���C�g
	static LightManager* sLightManager_;

public:

	/// <summary>
	/// ���[���h�s��̎擾
	/// </summary>
	/// <returns>���[���h�s��</returns>
	const myMath::Matrix4& GetMatWorld();

	/// <summary>
	/// ���_���W���擾
	/// </summary>
	/// <returns>���_���W�z��</returns>
	const std::vector<PosNormalUv>GetVertices();

	/// <summary>
	/// �C���f�b�N�X���擾
	/// </summary>
	/// <returns>�C���f�b�N�X���W�z��</returns>
	const std::vector<uint32_t>GetIndices();

	/// <summary>
	/// ���f���f�[�^�̃Z�b�g
	/// </summary>
	/// <param name="modelHandle">���f���̃n���h��</param>
	void SetModel(const uint32_t modelHandle);

	/// <summary>
	/// �u�����h���[�h�̃Z�b�g
	/// </summary>
	/// <param name="mode">�u�����h���[�h</param>
	void SetModelBlendMode(const BlendMode& mode);

	/// <summary>
	/// ���f���P�̂̃V�F�[�_�[���[�h�̃Z�b�g
	/// </summary>
	/// <param name="mode">�V�F�[�_�[���[�h</param>
	void SetShaderMode(const ShaderMode& mode);

	static void SetStaticShaderMode(const ShaderMode& mode);

	Model();
	virtual ~Model();

	/// <summary>
	/// ���f���̕`��
	/// </summary>
	/// <param name="transform">Transform�̃f�[�^</param>
	/// <param name="color">�F(�����l:{ 1.0f,1.0f ,1.0f ,1.0f })</param>
	void DrawModel(Transform* transform, myMath::Vector4 color = { 1.0f,1.0f ,1.0f ,1.0f });

	/// <summary>
	/// ���f���̐���
	/// </summary>
	/// <param name="filePath">�t�@�C����</param>
	/// <param name="smoothing">�X���[�W���O���邩�ǂ���(�����l:false)</param>
	/// <returns></returns>
	static uint32_t CreateObjModel(const std::string& filePath, bool smoothing = false);

	static uint32_t CreateAssimpModel(const std::string& filePath);

	/// <summary>
	/// ���C�g�̃Z�b�g
	/// </summary>
	/// <param name="light">���C�g</param>
	static void SetLight(LightManager* lightManager_);

	/// <summary>
	/// �ÓI����������
	/// </summary>
	static void StaticInitialize();

	/// <summary>
	/// �ÓI�������
	/// </summary>
	static void StaticDestory();

private:

	static void LoadShader();

	/// <summary>
	/// �p�C�v���C���ݒ��K�p
	/// </summary>
	/// <param name="bMode">�u�����h���[�h</param>
	/// <param name="sMode">�V�F�[�_�[���[�h</param>
	void PiplineSet(BlendMode bMode, ShaderMode sMode);
};