#pragma once
#include<wrl.h>
#include <d3d12.h>
/// <summary>
/// ���_�o�b�t�@
/// </summary>
class VertexBuffer
{
private:
	// �o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexBuffer_ = nullptr;

	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_ = {};

	void* bufferMappedPtr_ = nullptr;

	// �o�b�t�@�̐����ɐ���������
	bool isValid_ = false;
	char PADING_[7];
public:

	/// <summary>
	/// �o�b�t�@�𐶐�
	/// </summary>
	/// <param name="length">�v�f��</param>
	/// <param name="singleSize">�P�̂̃T�C�Y</param>
	/// <param name="data">�z��̐擪�A�h���X</param>
	void Create(size_t length, size_t singleSize, const void* data = nullptr);

	/// <summary>
	/// ���_�o�b�t�@�r���[���擾
	/// </summary>
	/// <returns>���_�o�b�t�@�r���[</returns>
	D3D12_VERTEX_BUFFER_VIEW GetView() const;

	/// <summary>
	/// �o�b�t�@���擾
	/// </summary>
	/// <returns>�o�b�t�@</returns>
	ID3D12Resource* GetResource();

	/// <summary>
	/// �o�b�t�@�̐����ɐ������������擾
	/// </summary>
	/// <returns>����������</returns>
	bool IsValid();

	/// <summary>
	/// �f�[�^�̍X�V
	/// </summary>
	/// <param name="data">�f�[�^</param>
	void Update(void* data);

	~VertexBuffer() = default;
	VertexBuffer() = default;

private:

	VertexBuffer(const VertexBuffer&) = delete;

	void operator = (const VertexBuffer&) = delete;
};