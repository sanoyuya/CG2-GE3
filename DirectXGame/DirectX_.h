#pragma once
#include "Input.h"
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include<vector>
#include<string>
#include <d3dcompiler.h>
#include<DirectXTex.h>

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

	//テクスチャサンプラーの設定
	D3D12_STATIC_SAMPLER_DESC samplerDesc{};

	// ルートシグネチャ
	ID3D12RootSignature* rootSignature;

	// ルートシグネチャの設定
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};

	// ルートシグネチャのシリアライズ
	ID3DBlob* rootSigBlob = nullptr;

	// パイプランステートの生成
	ID3D12PipelineState* pipelineState = nullptr;




	//定数バッファ用データ構造体(3D変換行列)
	struct ConstBufferDataTransform {
		XMMATRIX mat;//3D変換行列
	};

	//定数バッファの生成
	ID3D12Resource* constBuffTransform = nullptr;
	ConstBufferDataTransform* constMapTransform = nullptr;

	//ヒープ設定
	D3D12_HEAP_PROPERTIES cbHeapProp_{};
	//リソース設定
	D3D12_RESOURCE_DESC cbResourceDesc_{};




	//ルートパラメータの設定
	D3D12_ROOT_PARAMETER rootParams[3] = {};


	//定数バッファ用データ構造体(マテリアル)
	struct ConstBufferDataMaterial {
		XMFLOAT4 color;//色(RGBA)
	};
	
	// ビューポート設定コマンド
	D3D12_VIEWPORT viewport{};
	// シザー矩形
	D3D12_RECT scissorRect{};

	//頂点データの構造体
	struct Vertex {
		XMFLOAT3 pos;
		XMFLOAT2 uv;
	};

	//頂点データ
	Vertex vertices[4] = {
		//  x	  y   z		 u	  v
		{{-50.0f,-50.0f,0.0f},{0.0f,1.0f}},//左下
		{{-50.0f,50.0f,0.0f},{0.0f,0.0f}},//左上
		{{50.0f,-50.0f,0.0f},{1.0f,1.0f}},//右下
		{{50.0f,50.0f,0.0f},{1.0f,0.0f}},//右上
	};

	//インデックスデータ
	unsigned short indices[6] = {
		0,1,2,//三角形1つ目
		1,2,3,//三角形2つ目
	};

	//頂点データ全体サイズ = 頂点データ一つ分のサイズ * 頂点データの要素数
	UINT sizeVB = static_cast<UINT>(sizeof(vertices[0]) * _countof(vertices));

	//インデックスデータ全体のサイズ
	UINT sizeIB = static_cast<UINT>(sizeof(uint16_t) * _countof(indices));


	//1.リソースバリアで書き込み可能に変更
	D3D12_RESOURCE_BARRIER barrierDesc{};



	//テクスチャマッピングここから
	
	////横方向ピクセル数
	//const size_t textureWidth = 256;
	////縦方向ピクセル数
	//const size_t textureHeight = 256;
	////配列の要素数
	//const size_t imageDataCount = textureWidth * textureHeight;
	////画像イメージデータ配列
	//XMFLOAT4* imageData = new XMFLOAT4[imageDataCount];//必ず後で解放する

	TexMetadata metadata{};
	ScratchImage scratchImg{};
	ScratchImage mipChain{};

	//ヒープ設定
	D3D12_HEAP_PROPERTIES textureHeapProp{};
	//リソース設定
	D3D12_RESOURCE_DESC textureResourceDesc{};
	//テクスチャバッファの生成
	ID3D12Resource* texBuff = nullptr;

	//SRVの最大個数
	const size_t kMaxSRVCount = 2056;

	//デスクリプタヒープの設定
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};

	//設定を元にSRV用デスクリプタヒープを生成
	ID3D12DescriptorHeap* srvHeap = nullptr;

	//SRVヒープの先頭ハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle;

	//シェーダーリソースビュー設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};//設定構造体

	//デスクリプタレンジの設定
	D3D12_DESCRIPTOR_RANGE descriptorRange{};

	//テクスチャマッピングここまで

	//ビュー変換行列	
	XMMATRIX matView;
	float angle = 0.0f;//カメラの回転角

	Input input;//Inputクラス読み込み
	
public:
	DirectX_(HWND hwnd, WNDCLASSEX w);
	void DrawInitialize();
	void Update();
	void DrawUpdate();
	void CameraInitialize();
	void CameraUpdate();
	void SetHwnd();
};

