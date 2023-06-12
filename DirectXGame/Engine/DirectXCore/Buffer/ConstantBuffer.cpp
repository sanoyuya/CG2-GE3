#include "ConstantBuffer.h"
#include"DirectXBase.h"

void ConstantBuffer::Create(size_t size)
{
	bufferSize_ = size;

	//�萔�o�b�t�@�̐ݒ�
	D3D12_HEAP_PROPERTIES heapProp{};//�q�[�v�ݒ�
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;//GPU�ւ̓]���p
	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = (bufferSize_ + 0xff) & ~0xff;//���_�f�[�^�S�̂̃T�C�Y
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//�萔�o�b�t�@�̐���
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

	// ���_�f�[�^���}�b�s���O��ɐݒ�
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