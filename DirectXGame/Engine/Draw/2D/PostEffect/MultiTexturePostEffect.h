#pragma once
#include"PostEffect.h"

enum class MultiTextureEffectMode
{
	None,//�������Ȃ�
	BrightnessUP,//���x��2�{�ŏo��
	Inverse,//�F���]
	Blur,//�ڂ���
	GaussianBlur,//�K�E�V�A���u���[	
	GrayScale,//���m�N��
	SepiaColor,//�Z�s�A�J���[
	UVShift,//UV���炵
	Bloom,//�u���[��
	MultiTexture,//�}���`�e�N�X�`�����
	HighLumi
};

class MultiTexturePostEffect
{
private:

	Microsoft::WRL::ComPtr<ID3D12Resource>texBuff_[2];

	std::array< DescriptorHeap::DescriptorHeapViewHandle,2> handle_;

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
	//�萔�o�b�t�@�̃}�b�s���O�p�|�C���^
	static PowerGrayScale powerGrayScale_;
	//�v���W�F�N�V�����s��
	static myMath::Matrix4 matProjection_;

	//�V�F�[�_�I�u�W�F�N�g
	static std::array<Blob, 11> sBlob_;
	//�p�C�v���C��
	static std::array<PipelineSet, 11> sPip_;

	//��ʃN���A�J���[
	static const float sClearColor_[4];

	static MultiTextureEffectMode sEffectMode_;

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

public:

	static void SetEffectMode(const MultiTextureEffectMode& mode);

	static void SetPower(const float power);
	static void SetGrayScale(const float grayScale);

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

	void SetPipline();
};