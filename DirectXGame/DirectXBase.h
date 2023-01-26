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

	//デスクプリタヒープ
	std::unique_ptr<DescriptorHeap> descriptorHeap;

	//背景のクリアカラー
	FLOAT clearColor[4] = { 0.1f,0.25f,0.5f,0.0f };//背景の色(水色)設定

public:
	
	void Initialize();
	void UpdateClear();
	void UpdateEnd();
	void Destroy();

private:

#pragma region 初期化関連

	/// <summary>
	/// デバイスの初期化
	/// </summary>
	void DeviceInitialize();

	/// <summary>
	/// 
	/// </summary>
	void DebugInfo();

	/// <summary>
	/// デバッグレイヤーをオンに
	/// </summary>
	void DebugLayer();
	/// <summary>
	/// コマンドアロケータの初期化
	/// </summary>
	void CommandInitialize();

	/// <summary>
	/// スワップチェーンの初期化
	/// </summary>
	void SwapChainInitialize();

	/// <summary>
	/// レンダーターゲットの初期化
	/// </summary>
	void RenderTargetInitialize();

	/// <summary>
	/// 深度テスト
	/// </summary>
	void DepthInitialize();

#pragma endregion

public:

	//ゲッター
	ComPtr<ID3D12Device> GetDevice();
	ComPtr<ID3D12GraphicsCommandList> GetCommandList();
	ComPtr<ID3D12DescriptorHeap>GetRtvHeap();
	DescriptorHeap* GetDescriptorHeap();
	size_t GetBackBuffer()const;

	//セッター
	
	/// <summary>
	/// 背景の色をセット
	/// </summary>
	/// <param name="color">RGBA(初期値 { 0.1f , 0.25f , 0.5f , 0.0f } )</param>
	void SetClearColor(myMath::Vector4 color = { 0.1f,0.25f,0.5f,0.0f });

	//シングルトン
	static DirectXBase* GetInstance();

private:

	DirectXBase() = default;
	~DirectXBase() = default;

	//コピーコンストラクタ・代入演算子削除
	DirectXBase& operator=(const DirectXBase&) = delete;
	DirectXBase(const DirectXBase&) = delete;
};