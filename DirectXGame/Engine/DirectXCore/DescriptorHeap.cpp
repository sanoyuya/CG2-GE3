#include "DescriptorHeap.h"
#include"DirectXBase.h"

void DescriptorHeap::Initialize()
{
	device = DirectXBase::GetInstance()->GetDevice();

	// デスクリプタヒープの設定
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//シェーダから見えるように
	srvHeapDesc.NumDescriptors = static_cast<UINT>(maxSRV + maxUAV + maxCBV);

	// 設定を元にSRV用デスクリプタヒープを生成
	HRESULT result = device->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(descriptorHeap.ReleaseAndGetAddressOf()));
	assert(SUCCEEDED(result));

    startCpuHandle = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
	startGpuHandle = descriptorHeap->GetGPUDescriptorHandleForHeapStart();

	incrementSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

UINT64 DescriptorHeap::CreateSRV(D3D12_SHADER_RESOURCE_VIEW_DESC& desc, ID3D12Resource* resource)
{
	if (countSRV > maxSRV)
	{
		assert(0);
	}

	//SRVヒープの先頭ハンドルを取得
	DescriptorHeapViewHandle handle{};

	//ハンドルのポインタずらし
	handle.cpuHandle.ptr = startCpuHandle.ptr + (static_cast<UINT64>(countSRV) * incrementSize);
	handle.gpuHandle.ptr = startGpuHandle.ptr + (static_cast<UINT64>(countSRV) * incrementSize);

	// ハンドルの指す位置にシェーダーリソースビュー作成
	device->CreateShaderResourceView(resource, &desc, handle.cpuHandle);
	countSRV++;

	return handle.gpuHandle.ptr;
}

UINT64 DescriptorHeap::CreateUAV(D3D12_UNORDERED_ACCESS_VIEW_DESC& desc, ID3D12Resource* resource)
{
	if (countUAV > maxUAV)
	{
		assert(0);
	}

	//SRVヒープの先頭ハンドルを取得
	DescriptorHeapViewHandle handle{};

	//ハンドルのポインタずらし
	handle.cpuHandle.ptr = startCpuHandle.ptr + (static_cast<UINT64>(maxSRV + countUAV) * incrementSize);
	handle.gpuHandle.ptr = startGpuHandle.ptr + (static_cast<UINT64>(maxSRV + countUAV) * incrementSize);

	// ハンドルの指す位置にシェーダーリソースビュー作成
	device->CreateUnorderedAccessView(resource, nullptr, &desc, handle.cpuHandle);

	countUAV++;
	return handle.gpuHandle.ptr;
}

UINT64 DescriptorHeap::CreateCBV(D3D12_CONSTANT_BUFFER_VIEW_DESC& desc)
{
	if (countCBV > maxCBV)
	{
		assert(0);
	}

	//SRVヒープの先頭ハンドルを取得
	DescriptorHeapViewHandle handle{};

	//ハンドルのポインタずらし
	handle.cpuHandle.ptr = startCpuHandle.ptr + (static_cast<UINT64>(maxSRV + maxUAV +countCBV) * incrementSize);
	handle.gpuHandle.ptr = startGpuHandle.ptr + (static_cast<UINT64>(maxSRV + maxUAV + countCBV) * incrementSize);

	// ハンドルの指す位置にシェーダーリソースビュー作成
	device->CreateConstantBufferView(&desc, handle.cpuHandle);

	countCBV++;

	return handle.gpuHandle.ptr;
}

DescriptorHeap::DescriptorHeapViewHandle DescriptorHeap::AddSRV()
{
	if (countSRV > maxSRV)
	{
		assert(0);
	}

	DescriptorHeapViewHandle handle{};

	//ハンドルのポインタずらし
	handle.cpuHandle.ptr = startCpuHandle.ptr + (static_cast<UINT64>(countSRV) * incrementSize);
	handle.gpuHandle.ptr = startGpuHandle.ptr + (static_cast<UINT64>(countSRV) * incrementSize);

	countSRV++;

	return handle;
}

Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> DescriptorHeap::GetHeap()
{
	return descriptorHeap;
}