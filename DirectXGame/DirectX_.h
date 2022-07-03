#pragma once
#include "Input.h"
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include<vector>
#include<string>
#include <d3dcompiler.h>
#include<DirectXTex.h>
#include <DirectXMath.h>
#include"myMath.h"
using namespace myMath;
using namespace DirectX;

class DirectX_
{
private:
	const int window_width = 1280;//横幅
	const int window_height = 720;//縦幅
	Input input;//Inputクラス読み込み

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

	////定数バッファの生成
	//ID3D12Resource* constBuffTransform0 = nullptr;
	//ConstBufferDataTransform* constMapTransform0 = nullptr;

	//ID3D12Resource* constBuffTransform1 = nullptr;
	//ConstBufferDataTransform* constMapTransform1 = nullptr;

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
		XMFLOAT3 pos;		//xyz座標
		XMFLOAT3 normal;	//法線ベクトル
		XMFLOAT2 uv;		//uv座標
	};

	//頂点データ
	Vertex vertices[24] = {
		//  x	  y   z		 u	  v
		//前
		{{-5.0f,-5.0f,-5.0f},{}, {0.0f,1.0f}},//左下
		{{-5.0f,5.0f,-5.0f},{},{0.0f,0.0f}},//左上
		{{5.0f,-5.0f,-5.0f},{},{1.0f,1.0f}},//右下
		{{5.0f,5.0f,-5.0f},{},{1.0f,0.0f}},//右上
		//後(前面とZ座標の符号が逆)
		{{-5.0f,-5.0f,5.0f},{},{0.0f,1.0f}},//左下
		{{-5.0f,5.0f,5.0f},{},{0.0f,0.0f}},//左上
		{{5.0f,-5.0f,5.0f},{},{1.0f,1.0f}},//右下
		{{5.0f,5.0f,5.0f},{},{1.0f,0.0f}},//右上
		//左
		{{-5.0f,-5.0f,-5.0f},{},{0.0f,1.0f}},//左下
		{{-5.0f,-5.0f,5.0f},{},{0.0f,0.0f}},//左上
		{{-5.0f,5.0f,-5.0f},{},{1.0f,1.0f}},//右下
		{{-5.0f,5.0f,5.0f},{},{1.0f,0.0f}},//右上
		//右(左面とX座標の符号が逆)
		{{5.0f,-5.0f,-5.0f},{},{0.0f,1.0f}},//左下
		{{5.0f,-5.0f,5.0f},{},{0.0f,0.0f}},//左上
		{{5.0f,5.0f,-5.0f},{},{1.0f,1.0f}},//右下
		{{5.0f,5.0f,5.0f},{},{1.0f,0.0f}},//右上
		//下
		{{-5.0f,-5.0f,5.0f},{},{0.0f,1.0f}},//左下
		{{-5.0f,-5.0f,-5.0f},{},{0.0f,0.0f}},//左上
		{{5.0f,-5.0f,5.0f},{},{1.0f,1.0f}},//右下
		{{5.0f,-5.0f,-5.0f},{},{1.0f,0.0f}},//右上
		//上(上面とY座標の符号が逆)
		{{-5.0f,5.0f,5.0f},{},{0.0f,1.0f}},//左下
		{{-5.0f,5.0f,-5.0f},{},{0.0f,0.0f}},//左上
		{{5.0f,5.0f,5.0f},{},{1.0f,1.0f}},//右下
		{{5.0f,5.0f,-5.0f},{},{1.0f,0.0f}},//右上
	};

	//インデックスデータ
	unsigned short indices[36] = {
		//前
		0,1,2,//三角形1つ目
		2,1,3,//三角形2つ目
		//後(前の面に4加算)
		4,6,5,//三角形1つ目
		7,5,6,//三角形2つ目
		//左(前の面に4加算)
		8,9,10,//三角形1つ目
		10,9,11,//三角形2つ目
		//右(前の面に4加算)
		12,14,13,//三角形1つ目
		15,13,14,//三角形2つ目
		//下(前の面に4加算)
		16,17,18,//三角形1つ目
		18,17,19,//三角形2つ目
		//上(前の面に4加算)
		20,22,21,//三角形1つ目
		23,21,22,//三角形2つ目
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

	





	//深度バッファ
	D3D12_RESOURCE_DESC depthResourceDesc{};
	D3D12_HEAP_PROPERTIES depthHeapProp{};
	D3D12_CLEAR_VALUE depthClearValue{};
	ID3D12Resource* depthBuff = nullptr;
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	ID3D12DescriptorHeap* dsvHeap = nullptr;
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};




	Matrix4 MATRIX4;



	//ビュー変換行列	
	XMMATRIX matView;
	float angle = 0.0f;//カメラの回転角
	//カメラ生成
	XMFLOAT3 eye = { 0, 0, 0 };	//視点座標
	XMFLOAT3 target = { 0, 0, 0 };	//注視点座標
	XMFLOAT3 up = { 0, 1, 0 };		//上方向ベクトル

	//射影変換行列(透視投影)
	XMMATRIX matProjection = XMMatrixPerspectiveFovLH(ChangeRadians(45.0f),
		(float)window_width / window_height,
		0.1f, 1000.0f
	);



	//3Dオブジェクト型
	struct Object3d
	{
		//定数バッファ(行列用)
		ID3D12Resource* constBuffTransform;
		//定数バッファマップ(行列用)
		ConstBufferDataTransform* constMapTransform;
		//アフィン変換情報
		XMFLOAT3 scale = { 1,1,1 };
		XMFLOAT3 rotation = { 0,0,0 };
		XMFLOAT3 position = { 0,0,0 };
		//ワールド変換行列
		XMMATRIX matWorld;
		//親オブジェクトへのポインタ
		Object3d* parent = nullptr;
	};

	//3Dオブジェクトの数
	const size_t kObjectCount = 50;
	//3Dオブジェクトの配列
	Object3d object3ds[50];

public:
	DirectX_(HWND hwnd, WNDCLASSEX w);
	void DrawInitialize();
	void UpdateClear();
	void UpdateEnd();
	void DrawUpdate();
	void InitializeObject3d(Object3d* object, ID3D12Device* device);
	void UpdateObject3d(Object3d* object, XMMATRIX& matView, XMMATRIX& matProjection);
	void DrawObject3d(Object3d* object, ID3D12GraphicsCommandList* commandList, D3D12_VERTEX_BUFFER_VIEW& vbView, D3D12_INDEX_BUFFER_VIEW& ibView, UINT numIndices);
};

