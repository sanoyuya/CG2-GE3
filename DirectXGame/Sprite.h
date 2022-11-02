#pragma once
#include"myMath.h"
#include"DirectX_.h"
#include"WindowsApp.h"
#include"TextureManager.h"
#include"Camera.h"

struct PosUvColor
{
	myMath::Vector3 pos;//���W
	myMath::Vector2 uv;//uv���W
	myMath::Vector4 color;//�F
};

class Sprite
{
private:

	HRESULT result;
	char PADING[4];
	Microsoft::WRL::ComPtr<ID3D12Device>device;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>cmdList = nullptr;

	//���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource>vertBuff;
	//���_�}�b�v
	PosUvColor* vertMap;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//�C���f�b�N�X�o�b�t�@�̐���
	Microsoft::WRL::ComPtr<ID3D12Resource>indexBuff;
	//�C���f�b�N�X�o�b�t�@���}�b�s���O
	uint16_t* indexMap;
	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	D3D12_INDEX_BUFFER_VIEW ibView{};
	//�v���W�F�N�V�����s��
	myMath::Matrix4 matProjection;

	//�萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource>constBuff;
	//�萔�o�b�t�@�̃}�b�s���O�p�|�C���^
	myMath::Matrix4* constBuffMap = nullptr;

	Microsoft::WRL::ComPtr<ID3DBlob>vsBlob; // ���_�V�F�[�_�I�u�W�F�N�g
	Microsoft::WRL::ComPtr<ID3DBlob>psBlob; // �s�N�Z���V�F�[�_�I�u�W�F�N�g

	// ���[�g�V�O�l�`��
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
	// �p�C�v�����X�e�[�g�̐���
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;

public:
	Sprite(){}
	virtual ~Sprite(){}

	/// <summary>
	/// �X�v���C�g�̏���������
	/// </summary>
	void SpriteInitialize();

	/// <summary>
	/// �X�v���C�g�̕`��
	/// </summary>
	/// <param name="textureData">�e�N�X�`���f�[�^</param>
	/// <param name="camera">�J����</param>
	/// <param name="position">���W(x,y,z)</param>
	/// <param name="scale">�傫��(x,y,z)</param>
	/// <param name="rotation">��](x,y,z)</param>
	/// <param name="anchorpoint">���S�_(x,y,z)</param>
	void DrawSprite(TextureData& textureData, Camera* camera, myMath::Vector3 position, myMath::Vector3 scale = { 1.0f,1.0f,1.0f }, myMath::Vector3 rotation = { 0.0f,0.0f,0.0f }, myMath::Vector3 anchorpoint = { 0.5f,0.5f,0.5f });

private:
	void CreateVertexIndexBuffer();
	void CreateConstBuff();
	void CreatePipline();
	void LoadShader();
};