#include "DirectXBase.h"
#include"myMath.h"

#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include<vector>
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

DirectXBase* directX = nullptr;

void DirectXBase::Initialize(WindowsApp* windowsApp)
{
	//デバッグレイヤーをオンに設定
	DebugLayer();

	//デバイスの初期化
	DeviceInitialize();

	DebugInfo();

	//コマンド関連の初期化
	CommandInitialize();

	//スワップチェーンの初期化
	SwapChainInitialize(windowsApp);

	//レンダーターゲット生成
	RenderTargetInitialize();

	DepthInitialize(windowsApp);

	//フェンスの生成
	result_ = device_->CreateFence(fenceVal_, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence_));

	descriptorHeap_ = std::make_unique<DescriptorHeap>();
	descriptorHeap_->Initialize();
}

//DirectX毎フレーム処理
void DirectXBase::UpdateClear(WindowsApp* windowsApp)
{	
	//バックバッファの番号を取得(2つなので0か1番)
	uint32_t bbIndex = swapChain_->GetCurrentBackBufferIndex();

	//リソースバリアで書き込み可能に変更
	barrierDesc_.Transition.pResource = backBuffers_[bbIndex].Get();//バックバッファを指定
	barrierDesc_.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;//表示状態から
	barrierDesc_.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;//描画状態へ
	commandList_->ResourceBarrier(1, &barrierDesc_);

	//描画先の変更
	//レンダーターゲットビューのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtvHeap_->GetCPUDescriptorHandleForHeapStart();
	rtvHandle.ptr += static_cast<SIZE_T>(bbIndex * device_->GetDescriptorHandleIncrementSize(rtvHeapDesc_.Type));
	//深度ステンシルビュー用デスクリプタヒープのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = dsvHeap_->GetCPUDescriptorHandleForHeapStart();
	commandList_->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);

	//画面クリア
	commandList_->ClearRenderTargetView(rtvHandle, clearColor_, 0, nullptr);
	commandList_->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

	//描画コマンド
	D3D12_VIEWPORT viewport{};
	viewport.Width = static_cast<FLOAT>(windowsApp->GetWidth());
	viewport.Height = static_cast<FLOAT>(windowsApp->GetHeight());
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	//ビューポート設定のコマンドをコマンドリストに積む
	commandList_->RSSetViewports(1, &viewport);

	//シザー矩形
	D3D12_RECT scissorRect{};
	scissorRect.left = 0;
	scissorRect.right = static_cast<LONG>(scissorRect.left + windowsApp->GetWidth());
	scissorRect.top = 0;
	scissorRect.bottom = static_cast<LONG>(scissorRect.top + windowsApp->GetHeight());
	//シザー矩形設定コマンドをコマンドリストに積む
	commandList_->RSSetScissorRects(1, &scissorRect);
}

void DirectXBase::UpdateEnd()
{
	//5.リソースバリアを戻す
	barrierDesc_.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;//描画状態から
	barrierDesc_.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;		//表示状態へ
	commandList_->ResourceBarrier(1, &barrierDesc_);

	// 命令のクローズ
	result_ = commandList_->Close();
	assert(SUCCEEDED(result_));
	// コマンドリストの実行
	ID3D12CommandList* commandLists[] = { commandList_.Get() };
	commandQueue_->ExecuteCommandLists(1, commandLists);
	// 画面に表示するバッファをフリップ(裏表の入替え)
	result_ = swapChain_->Present(1, 0);
	assert(SUCCEEDED(result_));

	// コマンドの実行完了を待つ
	commandQueue_->Signal(fence_.Get(), ++fenceVal_);
	if (fence_->GetCompletedValue() != fenceVal_) {
		HANDLE event = CreateEvent(nullptr, false, false, nullptr);
		fence_->SetEventOnCompletion(fenceVal_, event);
		if (event != 0) {
			WaitForSingleObject(event, INFINITE);
			CloseHandle(event);
		}
	}
	// キューをクリア
	result_ = commandAllocator_->Reset();
	assert(SUCCEEDED(result_));
	// 再びコマンドリストを貯める準備
	result_ = commandList_->Reset(commandAllocator_.Get(), nullptr);
	assert(SUCCEEDED(result_));
}

void DirectXBase::Destroy()
{
	delete directX;
}

void DirectXBase::DebugLayer()
{
#ifdef _DEBUG
	//デバッグレイヤーをオンに
	ComPtr<ID3D12Debug1> debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(debugController.ReleaseAndGetAddressOf())))) {
		debugController->EnableDebugLayer();
		debugController->SetEnableGPUBasedValidation(TRUE);
	}
#endif
}

void DirectXBase::DeviceInitialize()
{
	//DXGIファクトリーの作成
	result_ = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory_));
	assert(SUCCEEDED(result_));

	//アダプターの列挙用
	std::vector<ComPtr<IDXGIAdapter4>>adapters;
	//ここに特定の名前を持つアダプターオブジェクトが入る
	ComPtr<IDXGIAdapter4> tmpAdapter;

	//パフォーマンスが高いものから順に、全てのアダプターを列挙する
	for (uint32_t i = 0; dxgiFactory_->EnumAdapterByGpuPreference(i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&tmpAdapter)) != DXGI_ERROR_NOT_FOUND; i++) {
		//動的配列に追加する
		adapters.push_back(tmpAdapter);
	}

	//妥当なアダプタを選別する
	for (size_t i = 0; i < adapters.size(); i++) {
		DXGI_ADAPTER_DESC3 adapterDesc;
		//アダプターの情報を取得する
		adapters[i]->GetDesc3(&adapterDesc);

		//ソフトウェアデバイスを回避
		if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE)) {
			//デバイスを採用してループを抜ける
			tmpAdapter = adapters[i].Get();
			break;
		}
	}

	//対応レベルの配列
	D3D_FEATURE_LEVEL levels[] = {
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	D3D_FEATURE_LEVEL featureLevel;

	for (size_t i = 0; i < _countof(levels); i++) {
		//採用したアダプターでデバイスを生成
		result_ = D3D12CreateDevice(tmpAdapter.Get(), levels[i], IID_PPV_ARGS(device_.ReleaseAndGetAddressOf()));
		if (result_ == S_OK) {
			//デバイスを生成できた時点でループを抜ける
			featureLevel = levels[i];
			break;
		}
	}
}

void DirectXBase::DebugInfo()
{
#ifdef _DEBUG
	ComPtr<ID3D12InfoQueue> infoQueue;
	if (SUCCEEDED(device_->QueryInterface(IID_PPV_ARGS(infoQueue.ReleaseAndGetAddressOf())))) {
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);//重大なエラー時に止まる
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);//エラー時に止まる
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);//エラー時に止まる
	}

	//抑制するエラー
	D3D12_MESSAGE_ID denyIds[] = {
		/*
		* windows11でのDXGIデバッグレイヤーの相互作用バグによるエラーメッセージ
		* https://stackoverflow.com/questions/69805245/dirctx-12-application-is-crashing-in-windows-11
		*/
		D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_COMMAND_LIST_TYPE
	};
	//抑制する表示レベル
	D3D12_MESSAGE_SEVERITY severities[] = {
		D3D12_MESSAGE_SEVERITY_INFO
	};
	D3D12_INFO_QUEUE_FILTER filter{};
	filter.DenyList.NumIDs = _countof(denyIds);
	filter.DenyList.pIDList = denyIds;
	filter.DenyList.NumSeverities = _countof(severities);
	filter.DenyList.pSeverityList = severities;
	//指定したエラーの表示を抑制する
	infoQueue->PushStorageFilter(&filter);
#endif
}

void DirectXBase::CommandInitialize()
{
	//コマンドアロケータを生成
	result_ = device_->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator_));
	assert(SUCCEEDED(result_));

	//コマンドリストを生成
	result_ = device_->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator_.Get(), nullptr, IID_PPV_ARGS(&commandList_));
	assert(SUCCEEDED(result_));

	//コマンドキューの設定
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
	//コマンドキューを生成
	result_ = device_->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&commandQueue_));
	assert(SUCCEEDED(result_));
}

void DirectXBase::SwapChainInitialize(WindowsApp* windowsApp)
{
	//IDXGISwapChain1のComPtrを用意
	ComPtr<IDXGISwapChain1>swapChain1;

	//スワップチェーンの設定
	swapChainDesc_.Width = static_cast<UINT64>(windowsApp->GetWidth());
	swapChainDesc_.Height = static_cast<UINT64>(windowsApp->GetHeight());
	swapChainDesc_.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//色情報の書式
	swapChainDesc_.SampleDesc.Count = 1;//マルチサンプルしない
	swapChainDesc_.BufferUsage = DXGI_USAGE_BACK_BUFFER;//バックバッファ用
	swapChainDesc_.BufferCount = 2;//バッファ数を2つに設定
	swapChainDesc_.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;//フリップ後は破棄
	swapChainDesc_.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	//スワップチェーンの生成
	result_ = dxgiFactory_->CreateSwapChainForHwnd(commandQueue_.Get(), windowsApp->GetHwnd(), &swapChainDesc_, nullptr, nullptr, swapChain1.GetAddressOf());

	//生成したIDXGISwapChain1のオブジェクトをIDXGISwapChain4に変換する
	swapChain1.As(&swapChain_);
	assert(SUCCEEDED(result_));
}

void DirectXBase::RenderTargetInitialize()
{
	//デスクリプタヒープの設定
	rtvHeapDesc_.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;//レンダーターゲットビュー
	rtvHeapDesc_.NumDescriptors = swapChainDesc_.BufferCount;//裏表の2つ

	//デスクリプタヒープの生成
	device_->CreateDescriptorHeap(&rtvHeapDesc_, IID_PPV_ARGS(&rtvHeap_));

	//バックバッファ
	backBuffers_.resize(swapChainDesc_.BufferCount);

	//スワップチェーンの全てのバッファについて処理する
	for (size_t i = 0; i < backBuffers_.size(); i++) {
		//スワップチェーンからバッファを取得
		swapChain_->GetBuffer((uint32_t)i, IID_PPV_ARGS(&backBuffers_[i]));
		//デスクリプタヒープのハンドル取得
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtvHeap_->GetCPUDescriptorHandleForHeapStart();
		//表か裏かでアドレスがずれる
		rtvHandle.ptr += i * device_->GetDescriptorHandleIncrementSize(rtvHeapDesc_.Type);
		//レンダーターゲットビューの設定
		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
		//シェーダーの計算結果をSRGBに変換して書き込む
		rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		//レンダーターゲットビューの生成
		device_->CreateRenderTargetView(backBuffers_[i].Get(), &rtvDesc, rtvHandle);
	}
}

void DirectXBase::DepthInitialize(WindowsApp* windowsApp)
{
	D3D12_RESOURCE_DESC depthResourceDesc{};
	depthResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthResourceDesc.Width = static_cast<UINT64>(windowsApp->GetWidth());//レンダーターゲットに合わせる
	depthResourceDesc.Height = static_cast<UINT64>(windowsApp->GetHeight());//レンダーターゲットに合わせる
	depthResourceDesc.DepthOrArraySize = 1;
	depthResourceDesc.Format = DXGI_FORMAT_D32_FLOAT;//深度値フォーマット
	depthResourceDesc.SampleDesc.Count = 1;
	depthResourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;//デプスステンシル

	//深度値用ヒーププロパティ
	D3D12_HEAP_PROPERTIES depthHeapProp{};
	depthHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
	//深度値のクリア設定
	D3D12_CLEAR_VALUE depthClearValue{};
	depthClearValue.DepthStencil.Depth = 1.0f;
	depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;

	//リソース生成
	result_ = device_->CreateCommittedResource(
		&depthHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&depthResourceDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,//深度値書き込みに使用
		&depthClearValue,
		IID_PPV_ARGS(&depthBuff_));

	//深度ビュー用デスクリプタヒープ作成
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	dsvHeapDesc.NumDescriptors = 1;
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	result_ = device_->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap_));

	//深度ビュー作成
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;//深度値フォーマット
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	device_->CreateDepthStencilView(
		depthBuff_.Get(),
		&dsvDesc,
		dsvHeap_->GetCPUDescriptorHandleForHeapStart());
}

Microsoft::WRL::ComPtr<ID3D12Device> DirectXBase::GetDevice()
{
	return device_;
}

Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> DirectXBase::GetCommandList()
{
	return commandList_;
}

Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> DirectXBase::GetRtvHeap()
{
	return rtvHeap_;
}

DescriptorHeap* DirectXBase::GetDescriptorHeap()
{
	return descriptorHeap_.get();
}

size_t DirectXBase::GetBackBuffer() const
{
	return backBuffers_.size();
}

void DirectXBase::SetClearColor(myMath::Vector4 color)
{
	clearColor_[0] = color.x;
	clearColor_[1] = color.y;
	clearColor_[2] = color.z;
	clearColor_[3] = color.w;
}

DirectXBase* DirectXBase::GetInstance()
{
	static DirectXBase instance;
	return &instance;
}