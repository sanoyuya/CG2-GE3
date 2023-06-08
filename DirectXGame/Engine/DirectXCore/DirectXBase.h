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

	HRESULT result_ = S_OK;
	ComPtr<ID3D12Device> device_;
	ComPtr<IDXGIFactory7> dxgiFactory_;
	ComPtr<IDXGISwapChain4> swapChain_;
	ComPtr<ID3D12CommandAllocator> commandAllocator_;
	ComPtr<ID3D12GraphicsCommandList> commandList_;
	ComPtr<ID3D12CommandQueue> commandQueue_;
	ComPtr<ID3D12DescriptorHeap> rtvHeap_;
	//スワップチェーンの設定
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc_{};
	
	//デスクリプタヒープの設定
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc_{};
	//バックバッファ
	std::vector<ComPtr<ID3D12Resource>>backBuffers_;
	//フェンスの生成
	ComPtr<ID3D12Fence> fence_;
	uint64_t fenceVal_ = 0;
	//リソースバリアの設定
	D3D12_RESOURCE_BARRIER barrierDesc_{};
	ComPtr<ID3D12Resource>depthBuff_;
	ComPtr<ID3D12DescriptorHeap> dsvHeap_;

	//デスクプリタヒープ
	std::unique_ptr<DescriptorHeap> descriptorHeap_;

	//背景のクリアカラー
	FLOAT clearColor_[4] = { 0.1f,0.25f,0.5f,0.0f };//背景の色(水色)設定

public:
	
	void Initialize(WindowsApp* windowsApp);
	void UpdateClear(WindowsApp* windowsApp);
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
	void SwapChainInitialize(WindowsApp* windowsApp);

	/// <summary>
	/// レンダーターゲットの初期化
	/// </summary>
	void RenderTargetInitialize();

	/// <summary>
	/// 深度テスト
	/// </summary>
	void DepthInitialize(WindowsApp* windowsApp);

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