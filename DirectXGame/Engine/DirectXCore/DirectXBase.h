#pragma once
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include<vector>
#include<string>
#include<wrl.h>
#include"WindowsApp.h"
#include"myMath.h"
#include<memory>
#include"DescriptorHeap.h"

class DirectXBase
{
public:
	//�G�C���A�X�e���v���[�g
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
private:

	WindowsApp* windowsApp = nullptr;

	HRESULT result;
	ComPtr<ID3D12Device> device;
	ComPtr<IDXGIFactory7> dxgiFactory;
	ComPtr<IDXGISwapChain4> swapChain;
	ComPtr<ID3D12CommandAllocator> commandAllocator;
	ComPtr<ID3D12GraphicsCommandList> commandList;
	ComPtr<ID3D12CommandQueue> commandQueue;
	ComPtr<ID3D12DescriptorHeap> rtvHeap;
	//�X���b�v�`�F�[���̐ݒ�
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	
	//�f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	//�o�b�N�o�b�t�@
	std::vector<ComPtr<ID3D12Resource>>backBuffers;
	//�t�F���X�̐���
	ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;
	//���\�[�X�o���A�̐ݒ�
	D3D12_RESOURCE_BARRIER barrierDesc{};
	ComPtr<ID3D12Resource>depthBuff = nullptr;
	ComPtr<ID3D12DescriptorHeap> dsvHeap;

	//�f�X�N�v���^�q�[�v
	std::unique_ptr<DescriptorHeap> descriptorHeap;

	//�w�i�̃N���A�J���[
	FLOAT clearColor[4] = { 0.1f,0.25f,0.5f,0.0f };//�w�i�̐F(���F)�ݒ�

public:
	
	void Initialize();
	void UpdateClear();
	void UpdateEnd();
	void Destroy();

private:

#pragma region �������֘A

	/// <summary>
	/// �f�o�C�X�̏�����
	/// </summary>
	void DeviceInitialize();

	/// <summary>
	/// 
	/// </summary>
	void DebugInfo();

	/// <summary>
	/// �f�o�b�O���C���[���I����
	/// </summary>
	void DebugLayer();
	/// <summary>
	/// �R�}���h�A���P�[�^�̏�����
	/// </summary>
	void CommandInitialize();

	/// <summary>
	/// �X���b�v�`�F�[���̏�����
	/// </summary>
	void SwapChainInitialize();

	/// <summary>
	/// �����_�[�^�[�Q�b�g�̏�����
	/// </summary>
	void RenderTargetInitialize();

	/// <summary>
	/// �[�x�e�X�g
	/// </summary>
	void DepthInitialize();

#pragma endregion

public:

	//�Q�b�^�[
	ComPtr<ID3D12Device> GetDevice();
	ComPtr<ID3D12GraphicsCommandList> GetCommandList();
	ComPtr<ID3D12DescriptorHeap>GetRtvHeap();
	DescriptorHeap* GetDescriptorHeap();
	size_t GetBackBuffer()const;

	//�Z�b�^�[
	
	/// <summary>
	/// �w�i�̐F���Z�b�g
	/// </summary>
	/// <param name="color">RGBA(�����l { 0.1f , 0.25f , 0.5f , 0.0f } )</param>
	void SetClearColor(myMath::Vector4 color = { 0.1f,0.25f,0.5f,0.0f });

	//�V���O���g��
	static DirectXBase* GetInstance();

private:

	DirectXBase() = default;
	~DirectXBase() = default;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	DirectXBase& operator=(const DirectXBase&) = delete;
	DirectXBase(const DirectXBase&) = delete;
};