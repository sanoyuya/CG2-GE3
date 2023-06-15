#pragma once
#include"WindowsApp.h"
#include"DirectXBase.h"
#include "Sprite2D.h"
#include"myMath.h"

class PostEffect : public Sprite2D
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
};