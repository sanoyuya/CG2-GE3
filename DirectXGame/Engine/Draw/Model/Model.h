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
	UINT maxIndex = 0u;

private:

	char PADING3[4] = {};

public:

	//���_�̐�
	UINT maxVert = 0u;
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

	static Microsoft::WRL::ComPtr<ID3D12Device> device;
	static Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList;

	static std::vector<std::string>filePaths;

	static std::unordered_map<std::string, std::unique_ptr<ModelData>> modelDatas;

	static uint32_t modelCount;

	static const uint32_t maxModel = 1024;

	ModelData* modelData;

private:

	static std::array<Blob,5> blob;//�V�F�[�_�I�u�W�F�N�g

	static std::array<std::array<PipelineSet, 6>,5> pip;

	BlendMode blendMode = BlendMode::Alpha;//�����l����������

	ShaderMode shaderMode = ShaderMode::Basic;//�W��

	std::unique_ptr<ConstantBuffer> col;

	myMath::Vector4 tmp;

	//���C�g
	static LightManager* lightManager;

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
	void SetModel(const uint32_t& modelHandle);

	/// <summary>
	/// �u�����h���[�h�̃Z�b�g
	/// </summary>
	/// <param name="mode">�u�����h���[�h</param>
	void SetModelBlendMode(const BlendMode& mode);

	/// <summary>
	/// �V�F�[�_�[���[�h�̃Z�b�g
	/// </summary>
	/// <param name="mode">�V�F�[�_�[���[�h</param>
	void SetShaderMode(const ShaderMode& mode);

	Model();
	~Model() = default;

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

	static void StaticInitialize();

	/// <summary>
	/// ���C�g�̃Z�b�g
	/// </summary>
	/// <param name="light">���C�g</param>
	static void SetLight(LightManager* lightManager_);

private:

	static void LoadShader();
	void PiplineSet(BlendMode bMode, ShaderMode sMode);

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	/*Model& operator=(const Model&) = delete;
	Model(const Model&) = delete;*/
};