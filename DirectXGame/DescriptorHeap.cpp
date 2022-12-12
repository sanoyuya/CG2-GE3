#include "DescriptorHeap.h"
#include"DirectX_.h"

void DescriptorHeap::Initialize()
{
	device = DirectX_::GetInstance()->GetDevice();

	// �f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//�V�F�[�_���猩����悤��
	srvHeapDesc.NumDescriptors = static_cast<UINT>(maxSRV + maxUAV + maxCBV);

	// �ݒ������SRV�p�f�X�N���v�^�q�[�v�𐶐�
	HRESULT result = device->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(descriptorHeap.ReleaseAndGetAddressOf()));
	assert(SUCCEEDED(result));
}

UINT64 DescriptorHeap::CreateSRV(D3D12_SHADER_RESOURCE_VIEW_DESC& desc, ID3D12Resource* resource)
{
	if (countSRV > maxSRV)
	{
		assert(0);
	}

	//SRV�q�[�v�̐擪�n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE	cpuHandle = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
	D3D12_GPU_DESCRIPTOR_HANDLE	gpuHandle = descriptorHeap->GetGPUDescriptorHandleForHeapStart();

	UINT incrementSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	//�n���h���̃|�C���^���炵
	cpuHandle.ptr += static_cast<UINT64>(countSRV) * incrementSize;
	gpuHandle.ptr += static_cast<UINT64>(countSRV) * incrementSize;

	// �n���h���̎w���ʒu�ɃV�F�[�_�[���\�[�X�r���[�쐬
	device->CreateShaderResourceView(resource, &desc, cpuHandle);
	countSRV++;

	return gpuHandle.ptr;
}

UINT64 DescriptorHeap::CreateUAV(D3D12_UNORDERED_ACCESS_VIEW_DESC& desc, ID3D12Resource* resource)
{
	if (countUAV > maxUAV)
	{
		assert(0);
	}

	//SRV�q�[�v�̐擪�n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE	cpuHandle = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
	D3D12_GPU_DESCRIPTOR_HANDLE	gpuHandle = descriptorHeap->GetGPUDescriptorHandleForHeapStart();

	UINT incrementSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	//�n���h���̃|�C���^���炵
	cpuHandle.ptr += static_cast<UINT64>(maxSRV + countUAV) * incrementSize;
	gpuHandle.ptr += static_cast<UINT64>(maxSRV + countUAV) * incrementSize;

	// �n���h���̎w���ʒu�ɃV�F�[�_�[���\�[�X�r���[�쐬
	device->CreateUnorderedAccessView(resource, nullptr, &desc, cpuHandle);

	countUAV++;
	return gpuHandle.ptr;
}

UINT64 DescriptorHeap::CreateCBV(D3D12_CONSTANT_BUFFER_VIEW_DESC& desc)
{
	if (countCBV > maxCBV)
	{
		assert(0);
	}

	//SRV�q�[�v�̐擪�n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE	cpuHandle = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
	D3D12_GPU_DESCRIPTOR_HANDLE	gpuHandle = descriptorHeap->GetGPUDescriptorHandleForHeapStart();

	UINT incrementSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	//�n���h���̃|�C���^���炵
	cpuHandle.ptr += static_cast<UINT64>(maxSRV + maxUAV + countCBV) * incrementSize;
	gpuHandle.ptr += static_cast<UINT64>(maxSRV + maxUAV + countCBV) * incrementSize;

	// �n���h���̎w���ʒu�ɃV�F�[�_�[���\�[�X�r���[�쐬
	device->CreateConstantBufferView(&desc, cpuHandle);

	countCBV++;

	return gpuHandle.ptr;
}

ID3D12DescriptorHeap* DescriptorHeap::GetHeap()
{
	return descriptorHeap.Get();
}