#include "VertexBuffer.h"
#include "DirectX_.h"

void VertexBuffer::Create(size_t length, size_t singleSize, const void* data)
{
	//�q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES heapProp{};
	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};

	//���_�f�[�^�S�̂̃T�C�Y = ���_�f�[�^�T�C�Y����̃T�C�Y * ���_�f�[�^�̗v�f��
	UINT sizeVB = static_cast<UINT>(singleSize * length);
	
	//���_�o�b�t�@�̐ݒ�
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;//GPU�ւ̓]���p
	//���\�[�X�ݒ�
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeVB;
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// ���\�[�X�𐶐�
	HRESULT result = DirectX_::GetInstance()->GetDevice()->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(vertexBuffer.ReleaseAndGetAddressOf()));

	// ���_�o�b�t�@�r���[�̐ݒ�
	vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
	vertexBufferView.SizeInBytes = static_cast<UINT>(length * singleSize);
	vertexBufferView.StrideInBytes = static_cast<UINT>(singleSize);

	result = vertexBuffer->Map(0, nullptr, &bufferMappedPtr);

	// �}�b�s���O����
	if (data != nullptr)
	{
		// ���_�f�[�^���}�b�s���O��ɐݒ�
		memcpy(bufferMappedPtr, data, length * singleSize);
	}

	isValid = true;
}

void VertexBuffer::Update(void* data)
{
	if (data == nullptr)
	{
		return;
	}

	// ���_�f�[�^���}�b�s���O��ɐݒ�
	memcpy(bufferMappedPtr, data, vertexBufferView.SizeInBytes);
}

D3D12_VERTEX_BUFFER_VIEW VertexBuffer::GetView() const
{
	return vertexBufferView;
}

bool VertexBuffer::IsValid()
{
	return isValid;
}

ID3D12Resource* VertexBuffer::GetResource()
{
	return vertexBuffer.Get();
}