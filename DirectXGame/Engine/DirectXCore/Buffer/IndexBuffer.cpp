#include "IndexBuffer.h"
#include"DirectXBase.h"

void IndexBuffer::Create(size_t length, const uint32_t* data)
{
	bufferLength_ = length;

	//ヒープ設定
	D3D12_HEAP_PROPERTIES heapProp{};
	//リソース設定
	D3D12_RESOURCE_DESC resDesc{};

	//インデックスデータのサイズ
	uint32_t sizeIB = static_cast<uint32_t>(sizeof(uint32_t) * length);
	//頂点バッファの設定
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;//GPUへの転送用
	//リソース設定　
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeIB;
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// リソースを生成
	HRESULT result = DirectXBase::GetInstance()->GetDevice()->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(buffer_.ReleaseAndGetAddressOf()));

	// インデックスバッファビューの設定
	bufferView_ = {};
	bufferView_.BufferLocation = buffer_->GetGPUVirtualAddress();
	bufferView_.Format = DXGI_FORMAT_R32_UINT;
	bufferView_.SizeInBytes = static_cast<uint32_t>(length * sizeof(uint32_t));

	result = buffer_->Map(0, nullptr, &bufferMappedPtr_);

	// マッピングする
	if (data != nullptr)
	{
		// インデックスデータをマッピング先に設定
		memcpy(bufferMappedPtr_, data, length * sizeof(uint32_t));

		// マッピング解除
		buffer_->Unmap(0, nullptr);
	}

	isValid_ = true;
}

bool IndexBuffer::IsValid()
{
	return isValid_;
}

D3D12_INDEX_BUFFER_VIEW IndexBuffer::GetView() const
{
	return bufferView_;
}

void IndexBuffer::Update(void* data)
{
	memcpy(bufferMappedPtr_, data, bufferLength_ * sizeof(uint32_t));
}