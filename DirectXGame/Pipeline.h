#pragma once
#include <d3d12.h>
#include<wrl.h>
#include<memory>
#include<array>

enum class BlendMode
{
	None,//�m�[�u�����h
	Alpha,//����������
	Add,//���Z����
	Sub,//���Z����
	Mul,//��Z����
	Inv//�F���]
};

struct PipelineSet
{
	//���[�g�V�O�l�`��
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
	//�p�C�v�����X�e�[�g�̐���
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
};

struct Blob
{
	//���_�V�F�[�_�I�u�W�F�N�g
	Microsoft::WRL::ComPtr<ID3DBlob>vs;
	//�s�N�Z���V�F�[�_�I�u�W�F�N�g
	Microsoft::WRL::ComPtr<ID3DBlob>ps;
};

class Pipeline
{
public:

	static void CreateSpritePipline(Blob& blob, BlendMode blend, ID3D12Device* device, std::array<PipelineSet, 6>& pip);
	static void CreateModelPipline(Blob& blob, BlendMode blend, ID3D12Device* device, std::array<PipelineSet, 6>& pip);
};