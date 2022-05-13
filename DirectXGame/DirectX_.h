#pragma once
#include "Input.h"
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include<vector>
#include<string>
#include <d3dcompiler.h>

class DirectX_
{
private:
	const int window_width = 1280;//横幅
	const int window_height = 720;//縦幅

	HRESULT result;
	ID3D12Device* device = nullptr;
	IDXGIFactory7* dxgiFactory = nullptr;
	IDXGISwapChain4* swapChain = nullptr;
	ID3D12CommandAllocator* commandAllocator = nullptr;
	ID3D12GraphicsCommandList* commandList = nullptr;
	ID3D12CommandQueue* commandQueue = nullptr;
	ID3D12DescriptorHeap* rtvHeap = nullptr;
	//スワップチェーンの設定
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	//デスクリプタヒープの設定
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	//バックバッファ
	std::vector<ID3D12Resource*>backBuffers;
	//フェンスの生成
	ID3D12Fence* fence = nullptr;
	UINT64 fenceVal = 0;



	//描画初期化処理
	//ヒープ設定
	D3D12_HEAP_PROPERTIES cbHeapProp{};

	//リソース設定
	D3D12_RESOURCE_DESC cbResourceDesc{};

	ID3D12Resource* constBuffMaterial = nullptr;

	// 頂点バッファの設定
	D3D12_HEAP_PROPERTIES heapProp{}; // ヒープ設定

	// リソース設定
	D3D12_RESOURCE_DESC resDesc{};

	// 頂点バッファの生成
	ID3D12Resource* vertBuff = nullptr;

	// GPU上のバッファに対応した仮想メモリ(メインメモリ上)を取得
	XMFLOAT3* vertMap = nullptr;

	// 頂点バッファビューの作成
	D3D12_VERTEX_BUFFER_VIEW vbView{};

	ID3DBlob* vsBlob = nullptr; // 頂点シェーダオブジェクト
	ID3DBlob* psBlob = nullptr; // ピクセルシェーダオブジェクト
	ID3DBlob* errorBlob = nullptr; // エラーオブジェクト

	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};

	//インデックスバッファの生成
	ID3D12Resource* indexBuff = nullptr;

	//インデックスバッファをマッピング
	uint16_t* indexMap = nullptr;

	//インデックスバッファビューの作成
	D3D12_INDEX_BUFFER_VIEW ibView{};

	// ブレンドステート
	D3D12_RENDER_TARGET_BLEND_DESC& blenddesc = pipelineDesc.BlendState.RenderTarget[0];// RBGA全てのチャンネルを描画

	// ルートシグネチャ
	ID3D12RootSignature* rootSignature;

	// ルートシグネチャの設定
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};

	// ルートシグネチャのシリアライズ
	ID3DBlob* rootSigBlob = nullptr;

	// パイプランステートの生成
	ID3D12PipelineState* pipelineState = nullptr;









	//ルートパラメータの設定
	D3D12_ROOT_PARAMETER rootParam = {};





	//定数バッファ用データ構造体(マテリアル)
	struct ConstBufferDataMaterial {
		XMFLOAT4 color;//色(RGBA)
	};
	
	// ビューポート設定コマンド
	D3D12_VIEWPORT viewport{};
	// シザー矩形
	D3D12_RECT scissorRect{};



	//1.リソースバリアで書き込み可能に変更
	D3D12_RESOURCE_BARRIER barrierDesc{};

	Input input;//Inputクラス読み込み
public:
	DirectX_(HWND hwnd, WNDCLASSEX w);
	void DrawInitiaize();
	void Update();
	void DrawUpdate();
	void SetHwnd();
};

