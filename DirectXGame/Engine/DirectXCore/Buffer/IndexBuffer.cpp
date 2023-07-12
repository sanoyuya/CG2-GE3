#include "IndexBuffer.h"
#include"DirectXBase.h"

void IndexBuffer::Create(size_t length, const uint32_t* data)
{
	bufferLength_ = length;

	//�q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES heapProp{};
	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};

	//�C���f�b�N�X�f�[�^�̃T�C�Y
	uint32_t sizeIB = static_cast<uint32_t>(sizeof(uint32_t) * length);
	//���_�o�b�t�@�̐ݒ�
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;//GPU�ւ̓]���p
	//���\�[�X�ݒ�@
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeIB;
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// ���\�[�X�𐶐�
	HRESULT result = DirectXBase::GetInstance()->GetDevice()->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(buffer_.ReleaseAndGetAddressOf()));

	// �C���f�b�N�X�o�b�t�@�r���[�̐ݒ�
	bufferView_ = {};
	bufferView_.BufferLocation = buffer_->GetGPUVirtualAddress();
	bufferView_.Format = DXGI_FORMAT_R32_UINT;
	bufferView_.SizeInBytes = static_cast<uint32_t>(length * sizeof(uint32_t));

	result = buffer_->Map(0, nullptr, &bufferMappedPtr_);

	// �}�b�s���O����
	if (data != nullptr)
	{
		// �C���f�b�N�X�f�[�^���}�b�s���O��ɐݒ�
		memcpy(bufferMappedPtr_, data, length * sizeof(uint32_t));

		// �}�b�s���O����
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