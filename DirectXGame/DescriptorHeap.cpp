#include "DescriptorHeap.h"
#include"DirectX_.h"

void DescriptorHeap::Initialize()
{
	device = DirectX_::GetInstance()->GetDevice();

	// デスクリプタヒープの設定
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//シェーダから見えるように
	srvHeapDesc.NumDescriptors = static_cast<UINT>(maxSRV + maxUAV + maxCBV);

	// 設定を元にSRV用デスクリプタヒープを生成
	HRESULT result = device->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(descriptorHeap.ReleaseAndGetAddressOf()));
	assert(SUCCEEDED(result));
}

UINT64 DescriptorHeap::CreateSRV(D3D12_SHADER_RESOURCE_VIEW_DESC& desc, ID3D12Resource* resource)
{
	if (countSRV > maxSRV)
	{
		assert(0);
	}

	//SRVヒープの先頭ハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE	cpuHandle = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
	D3D12_GPU_DESCRIPTOR_HANDLE	gpuHandle = descriptorHeap->GetGPUDescriptorHandleForHeapStart();

	UINT incrementSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	//ハンドルのポインタずらし
	cpuHandle.ptr += static_cast<UINT64>(countSRV) * incrementSize;
	gpuHandle.ptr += static_cast<UINT64>(countSRV) * incrementSize;

	// ハンドルの指す位置にシェーダーリソースビュー作成
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

	//SRVヒープの先頭ハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE	cpuHandle = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
	D3D12_GPU_DESCRIPTOR_HANDLE	gpuHandle = descriptorHeap->GetGPUDescriptorHandleForHeapStart();

	UINT incrementSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	//ハンドルのポインタずらし
	cpuHandle.ptr += static_cast<UINT64>(maxSRV + countUAV) * incrementSize;
	gpuHandle.ptr += static_cast<UINT64>(maxSRV + countUAV) * incrementSize;

	// ハンドルの指す位置にシェーダーリソースビュー作成
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

	//SRVヒープの先頭ハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE	cpuHandle = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
	D3D12_GPU_DESCRIPTOR_HANDLE	gpuHandle = descriptorHeap->GetGPUDescriptorHandleForHeapStart();

	UINT incrementSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	//ハンドルのポインタずらし
	cpuHandle.ptr += static_cast<UINT64>(maxSRV + maxUAV + countCBV) * incrementSize;
	gpuHandle.ptr += static_cast<UINT64>(maxSRV + maxUAV + countCBV) * incrementSize;

	// ハンドルの指す位置にシェーダーリソースビュー作成
	device->CreateConstantBufferView(&desc, cpuHandle);

	countCBV++;

	return gpuHandle.ptr;
}

ID3D12DescriptorHeap* DescriptorHeap::GetHeap()
{
	return descriptorHeap.Get();
}