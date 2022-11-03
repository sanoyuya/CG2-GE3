#pragma once
#include"DirectX_.h"

struct TextureData
{
	//�e�N�X�`���o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource>texBuff;

	//�f�X�N���v�^�q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>srvHeap;

	//GPU�f�X�N���v�^�n���h��
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle{};

	//�f�X�N���v�^�����W
	D3D12_DESCRIPTOR_RANGE descriptorRange{};

	char PADING[4];
	//����
	size_t width = 0;
	//�c��
	size_t height = 0;
};

class TextureManager
{
public:
	//�G�C���A�X�e���v���[�g
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
	ComPtr<ID3D12Device> device;
	ComPtr<ID3D12DescriptorHeap> dsvHeap;
	D3D12_DESCRIPTOR_RANGE dsvRange;
	D3D12_HEAP_PROPERTIES prop;

	UINT texCount;

	static TextureManager* textureManager;

public:
	void Initialize();

	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	TextureData LoadTexture(const std::string& filePath);

	/// <summary>
	/// �C���X�^���X�����
	/// </summary>
	void Destroy();

	static TextureManager* GetInstance();
};