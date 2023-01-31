#pragma once
#include<wrl.h>
#include <d3d12.h>
#include <cstdint>

/// <summary>
/// �C���f�b�N�X�o�b�t�@
/// </summary>
class IndexBuffer
{
private:

	//�C���f�b�N�X�o�b�t�@����������������
	bool isValid = false;
	char PADING[7];

	// �C���f�b�N�X�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> buffer;

	// �C���f�b�N�X�o�b�t�@�r���[
	D3D12_INDEX_BUFFER_VIEW bufferView{};

	void* bufferMappedPtr = nullptr;

	size_t bufferLength = 0;

public:

	/// <summary>
	/// �C���f�b�N�X�o�b�t�@�𐶐�
	/// </summary>
	/// <param name="length">�C���f�b�N�X�o�b�t�@�̗v�f��</param>
	/// <param name="data">�C���f�b�N�X�z��̐擪�A�h���X(uint32_t)</param>
	void Create(size_t length, const uint32_t* data = nullptr);

	/// <summary>
	/// ����������
	/// </summary>
	bool IsValid();

	/// <summary>
	/// �C���f�b�N�X�o�b�t�@�r���[���擾
	/// </summary>
	D3D12_INDEX_BUFFER_VIEW GetView() const;

	/// <summary>
	/// �f�[�^�̍X�V
	/// </summary>
	/// <param name="data">�f�[�^</param>
	void Update(void* data);

	IndexBuffer() = default;
	~IndexBuffer() = default;

private:

	IndexBuffer(const IndexBuffer&) = delete;
	void operator = (const IndexBuffer&) = delete;
};