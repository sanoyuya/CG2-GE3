#pragma once
#include<wrl.h>
#include <d3d12.h>

/// <summary>
/// �萔�o�b�t�@
/// </summary>
class ConstantBuffer
{
private:

	// �萔�o�b�t�@�����ɐ���������
	bool isValid_ = false;
	char PADING_[7] = {};

	// �萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> buffer_;

	// �萔�o�b�t�@�r���[�̐ݒ�
	D3D12_CONSTANT_BUFFER_VIEW_DESC constantBufferView_ = {};

	void* bufferMappedPtr_ = nullptr;

	size_t bufferSize_;

public:
	/// <summary>
	/// �萔�o�b�t�@�𐶐�
	/// </summary>
	/// <param name="size">�f�[�^�T�C�Y</param>
	void Create(size_t size);

	/// <summary>
	/// �o�b�t�@�����ɐ�����������Ԃ�
	/// </summary>
	/// <returns>�o�b�t�@�����ɐ���������</returns>
	bool IsValid();

	/// <summary>
	/// �o�b�t�@��GPU��̃A�h���X��Ԃ�
	/// </summary>
	/// <returns>�o�b�t�@��GPU��̃A�h���X</returns>
	D3D12_GPU_VIRTUAL_ADDRESS GetAddress() const;

	/// <summary>
	/// �萔�o�b�t�@�r���[��Ԃ�
	/// </summary>
	/// <returns>�萔�o�b�t�@�r���[</returns>
	D3D12_CONSTANT_BUFFER_VIEW_DESC GetViewDesc();

	/// <summary>
	/// �f�[�^�̍X�V
	/// </summary>
	/// <param name="data">�f�[�^</param>
	void Update(void* data);

	/// <summary>
	/// �o�b�t�@���擾
	/// </summary>
	ID3D12Resource* GetResource();

	/// <summary>
	/// �}�b�v�p�|�C���^���擾
	/// </summary>
	/// <returns></returns>
	void* GetPtr();

	~ConstantBuffer() = default;
	ConstantBuffer() = default;

private:

	ConstantBuffer(const ConstantBuffer&) = delete;
	void operator = (const ConstantBuffer&) = delete;
};