#pragma once
#include"WindowsApp.h"
#include"DirectXBase.h"
#include "DrawCommon.h"
#include"Pipeline.h"
#include"IndexBuffer.h"
#include"VertexBuffer.h"
#include"ConstantBuffer.h"
#include"TextureManager.h"
#include"myMath.h"

struct VertexPosUV
{
	myMath::Vector3 pos;//���W
	myMath::Vector2 uv;//uv���W
};

class PostEffect
{
private:

	Microsoft::WRL::ComPtr<ID3D12Resource>texBuff_;

	DescriptorHeap::DescriptorHeapViewHandle handle_;

	//�[�x�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource>depthBuff_;
	//RTV�p�f�X�N���v�^�q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>descHeapRTV_;
	//DSV�p�f�X�N���v�^�q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>descHeapDSV_;

	//���_�o�b�t�@
	std::unique_ptr<VertexBuffer> vertexBuffer_ = {};
	//���_�}�b�v
	PosUvColor* vertMap_ = {};
	//�C���f�b�N�X�o�b�t�@
	std::unique_ptr<IndexBuffer> indexBuffer_ = {};
	// �萔�o�b�t�@
	std::unique_ptr<ConstantBuffer> constBuffMaterial_ = {};
	//�萔�o�b�t�@�̃}�b�s���O�p�|�C���^
	myMath::Matrix4 constBuffMap_ = {};
	//�v���W�F�N�V�����s��
	static myMath::Matrix4 matProjection_;

	//�V�F�[�_�I�u�W�F�N�g
	static std::array<Blob, 5> sBlob_;
	//�p�C�v���C��
	static std::array<PipelineSet, 5> sPip_;

	//��ʃN���A�J���[
	static const float sClearColor_[4];

	myMath::Vector2 position_ = { 0.0f,0.0f };
	myMath::Vector2 scale_ = { 0.0f,0.0f };
	float rotation_ = 0.0f;
	myMath::Vector4 color_ = { 0.0f,0.0f,0.0f,0.0f };
	myMath::Vector2 anchorpoint_ = { 0.0f,0.0f };
	bool flipX_ = false;
	bool flipY_ = false;

	uint32_t tex_ = 0;
	TextureData* texture_ = {};

public:

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize(WindowsApp* windowsApp);

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

	/// <summary>
	/// �V�[���`��O����
	/// </summary>
	void PreDrawScene(WindowsApp* windowsApp);

	/// <summary>
	/// �V�[���`�揈����
	/// </summary>
	void PostDrawScene();

private:

	void VertSetting();
	void CreateBuff();
	//texBuff_�̐���
	void CreateTexBuff(WindowsApp* windowsApp);
	//SRV�̍쐬
	void CreateDescHeap();
	//RTV�̍쐬
	void CreateRTV();
	//�[�x�o�b�t�@�̐���
	void CreateDepth(WindowsApp* windowsApp);
	//DSV�̍쐬
	void CreateDSV();

	void CreatePipline();

	void LoadShader();

	void DrawCommand();
};