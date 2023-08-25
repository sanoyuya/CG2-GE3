#pragma once
#include<wrl.h>
#include <d3d12.h>
#include<stdint.h>

/// <summary>
/// �f�X�N�v���^�q�[�v
/// </summary>
class DescriptorHeap
{
private:

	//�f�o�C�X
	Microsoft::WRL::ComPtr <ID3D12Device> device_;
	//�f�X�N�v���^�q�[�v
	Microsoft::WRL::ComPtr <ID3D12DescriptorHeap> descriptorHeap_;
	//�f�X�N�v���^�����W
	D3D12_DESCRIPTOR_RANGE descriptorRange_{};

	char PADING_[4];

	D3D12_CPU_DESCRIPTOR_HANDLE	startCpuHandle_;
	D3D12_GPU_DESCRIPTOR_HANDLE	startGpuHandle_;

	uint32_t incrementSize_ = 0;

	size_t maxSRV_ = 2048;
	size_t maxUAV_ = 2048;
	size_t maxCBV_ = 4098;

	size_t countSRV_ = 0;
	size_t countUAV_ = 0;
	size_t countCBV_ = 0;

public:

	struct DescriptorHeapViewHandle
	{
		D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle;
		D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle;
	};

public:

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �V�F�[�_�[���\�[�X�r���[����
	/// </summary>
	/// <param name="desc">�V�F�[�_�[���\�[�X�r���[�f�X�N</param>
	/// <param name="resource">�o�b�t�@</param>
	/// <returns>GPU�n���h��(UINT64)</returns>
	UINT64 CreateSRV(D3D12_SHADER_RESOURCE_VIEW_DESC& desc, ID3D12Resource* resource);

	/// <summary>
	/// �A���I�[�_�[�A�N�Z�X�r���[����
	/// </summary>
	/// <param name="desc">�A���I�[�_�[�A�N�Z�X�r���[�f�X�N</param>
	/// <param name="resource">�o�b�t�@</param>
	/// <returns>GPU�n���h��(UINT64)</returns>
	UINT64 CreateUAV(D3D12_UNORDERED_ACCESS_VIEW_DESC& desc, ID3D12Resource* resource);

	/// <summary>
	/// �R���X�g�o�b�t�@�r���[����
	/// </summary>
	/// <param name="desc">�R���X�g�o�b�t�@�r���[�f�X�N</param>
	/// <returns>GPU�n���h��(UINT64)</returns>
	UINT64 CreateCBV(D3D12_CONSTANT_BUFFER_VIEW_DESC& desc);

	DescriptorHeapViewHandle AddSRV();

	/// <summary>
	/// �f�X�N�v���^�q�[�v���擾
	/// </summary>
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> GetHeap();
};