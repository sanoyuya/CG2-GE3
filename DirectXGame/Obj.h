#pragma once
#include"DrawCommon.h"
#include"DirectX_.h"
#include<vector>
class Object
{
private:

	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>cmdList = nullptr;

	std::vector<PosNormalUv>vertices;
	std::vector<uint16_t>indices;

	//頂点バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource>vertBuff;
	//頂点マップ
	PosUvColor* vertMap;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//インデックスバッファの生成
	Microsoft::WRL::ComPtr<ID3D12Resource>indexBuff;
	//インデックスバッファをマッピング
	uint16_t* indexMap;
	//インデックスバッファビューの作成
	D3D12_INDEX_BUFFER_VIEW ibView{};
	//プロジェクション行列
	myMath::Matrix4 matProjection;

	//定数バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource>constBuff;
	//定数バッファのマッピング用ポインタ
	myMath::Matrix4* constBuffMap = nullptr;

	Microsoft::WRL::ComPtr<ID3DBlob>vsBlob; // 頂点シェーダオブジェクト
	Microsoft::WRL::ComPtr<ID3DBlob>psBlob; // ピクセルシェーダオブジェクト

	// ルートシグネチャ
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
	// パイプランステートの生成
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;

public:
	void Initialize();
	void Update();
	void Draw();
};