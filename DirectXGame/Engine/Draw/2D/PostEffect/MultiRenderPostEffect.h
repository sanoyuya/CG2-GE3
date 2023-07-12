#pragma once
#include"PostEffect.h"

class MultiRenderPostEffect
{
private:

	Microsoft::WRL::ComPtr<ID3D12Resource>texBuff_[2];

	DescriptorHeap::DescriptorHeapViewHandle handle_;
	DescriptorHeap::DescriptorHeapViewHandle handle2_;

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
	//RTV�̍쐬
	void CreateRTV();
	//�[�x�o�b�t�@�̐���
	void CreateDepth(WindowsApp* windowsApp);
	//DSV�̍쐬
	void CreateDSV();

	void CreatePipline();

	void LoadShader();

	void DrawCommand();
	//SRV�̍쐬
	void CreateSRV();
};