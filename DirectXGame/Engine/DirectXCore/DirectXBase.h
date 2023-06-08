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

	HRESULT result_ = S_OK;
	ComPtr<ID3D12Device> device_;
	ComPtr<IDXGIFactory7> dxgiFactory_;
	ComPtr<IDXGISwapChain4> swapChain_;
	ComPtr<ID3D12CommandAllocator> commandAllocator_;
	ComPtr<ID3D12GraphicsCommandList> commandList_;
	ComPtr<ID3D12CommandQueue> commandQueue_;
	ComPtr<ID3D12DescriptorHeap> rtvHeap_;
	//�X���b�v�`�F�[���̐ݒ�
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc_{};
	
	//�f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc_{};
	//�o�b�N�o�b�t�@
	std::vector<ComPtr<ID3D12Resource>>backBuffers_;
	//�t�F���X�̐���
	ComPtr<ID3D12Fence> fence_;
	uint64_t fenceVal_ = 0;
	//���\�[�X�o���A�̐ݒ�
	D3D12_RESOURCE_BARRIER barrierDesc_{};
	ComPtr<ID3D12Resource>depthBuff_;
	ComPtr<ID3D12DescriptorHeap> dsvHeap_;

	//�f�X�N�v���^�q�[�v
	std::unique_ptr<DescriptorHeap> descriptorHeap_;

	//�w�i�̃N���A�J���[
	FLOAT clearColor_[4] = { 0.1f,0.25f,0.5f,0.0f };//�w�i�̐F(���F)�ݒ�

public:
	
	void Initialize(WindowsApp* windowsApp);
	void UpdateClear(WindowsApp* windowsApp);
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
	void SwapChainInitialize(WindowsApp* windowsApp);

	/// <summary>
	/// �����_�[�^�[�Q�b�g�̏�����
	/// </summary>
	void RenderTargetInitialize();

	/// <summary>
	/// �[�x�e�X�g
	/// </summary>
	void DepthInitialize(WindowsApp* windowsApp);

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