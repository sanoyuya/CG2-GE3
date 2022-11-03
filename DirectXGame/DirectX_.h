#pragma once
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include<vector>
#include<string>
#include<wrl.h>
#include"WindowsApp.h"
#include"myMath.h"

class DirectX_
{
public:
	//エイリアステンプレート
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
	//スワップチェーンの設定
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	
	//デスクリプタヒープの設定
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	//バックバッファ
	std::vector<ComPtr<ID3D12Resource>>backBuffers;
	//フェンスの生成
	ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;
	//リソースバリアの設定
	D3D12_RESOURCE_BARRIER barrierDesc{};
	ComPtr<ID3D12Resource>depthBuff = nullptr;
	ComPtr<ID3D12DescriptorHeap> dsvHeap;

	//背景のクリアカラー
	FLOAT clearColor[4] = { 0.1f,0.25f,0.5f,0.0f };//背景の色(水色)設定

public:
	DirectX_();
	~DirectX_();
	void Initialize();
	void UpdateClear();
	void UpdateEnd();
	void Destroy();

private:

#pragma region 初期化関連

	void DeviceInitialize();
	void DebugInfo();
	void DebugLayer();
	void CommandInitialize();
	void SwapChainInitialize();
	void RenderTargetInitialize();
	void DepthInitialize();

#pragma endregion

public:

	//ゲッター
	ComPtr<ID3D12Device> GetDevice();
	ComPtr<ID3D12GraphicsCommandList> GetCommandList();
	ComPtr<ID3D12DescriptorHeap>GetRtvHeap();

	//セッター
	
	/// <summary>
	/// 背景の色をセット
	/// </summary>
	/// <param name="color">RGBA(初期値 { 0.1f , 0.25f , 0.5f , 0.0f } )</param>
	void SetClearColor(myMath::Vector4 color = { 0.1f,0.25f,0.5f,0.0f });

	//シングルトン
	static DirectX_* GetInstance();
};