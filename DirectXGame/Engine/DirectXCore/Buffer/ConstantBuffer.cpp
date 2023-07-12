#include "ConstantBuffer.h"
#include"DirectXBase.h"

void ConstantBuffer::Create(size_t size)
{
	bufferSize_ = size;

	//定数バッファの設定
	D3D12_HEAP_PROPERTIES heapProp{};//ヒープ設定
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;//GPUへの転送用
	//リソース設定
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = (bufferSize_ + 0xff) & ~0xff;//頂点データ全体のサイズ
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//定数バッファの生成
	HRESULT result = DirectXBase::GetInstance()->GetDevice()->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(buffer_.ReleaseAndGetAddressOf()));

	result = buffer_->Map(0, nullptr, &bufferMappedPtr_);

	constantBufferView_ = {};
	constantBufferView_.BufferLocation = buffer_->GetGPUVirtualAddress();
	constantBufferView_.SizeInBytes = static_cast<uint32_t>(resDesc.Width);

	DirectXBase::GetInstance()->GetDescriptorHeap()->CreateCBV(constantBufferView_);

	isValid_ = true;
}

bool ConstantBuffer::IsValid()
{
	return isValid_;
}

D3D12_GPU_VIRTUAL_ADDRESS ConstantBuffer::GetAddress() const
{
	return constantBufferView_.BufferLocation;
}

D3D12_CONSTANT_BUFFER_VIEW_DESC ConstantBuffer::GetViewDesc()
{
	return constantBufferView_;
}

void ConstantBuffer::Update(void* data)
{
	if (data == nullptr)
	{
		return;
	}

	// 頂点データをマッピング先に設定
	memcpy(bufferMappedPtr_, data, bufferSize_);
}

ID3D12Resource* ConstantBuffer::GetResource()
{
	return buffer_.Get();
}

void* ConstantBuffer::GetPtr()
{
	return bufferMappedPtr_;
}