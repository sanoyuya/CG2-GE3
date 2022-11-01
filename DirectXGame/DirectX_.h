#pragma once
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include<vector>
#include<string>
#include<wrl.h>
#include"WindowsApp.h"

class DirectX_
{
public:
	//�G�C���A�X�e���v���[�g
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
private:

	WindowsApp* windowsApp = nullptr;

	const int window_width = 1280;//����
	const int window_height = 720;//�c��

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
	//1.���\�[�X�o���A�ŏ������݉\�ɕύX
	D3D12_RESOURCE_BARRIER barrierDesc{};
	ComPtr<ID3D12DescriptorHeap> dsvHeap;

public:
	DirectX_();
	~DirectX_();
	void Initialize();
	void UpdateClear();
	void UpdateEnd();
	void Destroy();

#pragma region �������֘A

	void DeviceInitialize();
	void DebugInfo();
	void DebugLayer();
	void CommandInitialize();
	void SwapChainInitialize();
	void RenderTargetInitialize();

#pragma endregion

	//�Q�b�^�[
	ComPtr<ID3D12Device> GetDevice();
	ComPtr<ID3D12GraphicsCommandList> GetCommandList();
	ComPtr<ID3D12DescriptorHeap>GetRtvHeap();
	const int GetWindow_width();
	const int GetWindow_height();

	//�V���O���g��
	static DirectX_* GetInstance();
};