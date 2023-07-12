#pragma once
#include"PostEffect.h"

class MultiRenderPostEffect
{
private:

	Microsoft::WRL::ComPtr<ID3D12Resource>texBuff_[2];

	DescriptorHeap::DescriptorHeapViewHandle handle_;
	DescriptorHeap::DescriptorHeapViewHandle handle2_;

	//深度バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource>depthBuff_;
	//RTV用デスクリプタヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>descHeapRTV_;
	//DSV用デスクリプタヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>descHeapDSV_;

	//頂点バッファ
	std::unique_ptr<VertexBuffer> vertexBuffer_ = {};
	//頂点マップ
	PosUvColor* vertMap_ = {};
	//インデックスバッファ
	std::unique_ptr<IndexBuffer> indexBuffer_ = {};
	// 定数バッファ
	std::unique_ptr<ConstantBuffer> constBuffMaterial_ = {};
	//定数バッファのマッピング用ポインタ
	myMath::Matrix4 constBuffMap_ = {};
	//プロジェクション行列
	static myMath::Matrix4 matProjection_;

	//シェーダオブジェクト
	static std::array<Blob, 5> sBlob_;
	//パイプライン
	static std::array<PipelineSet, 5> sPip_;

	//画面クリアカラー
	static const float sClearColor_[4];

public:

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(WindowsApp* windowsApp);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// シーン描画前処理
	/// </summary>
	void PreDrawScene(WindowsApp* windowsApp);

	/// <summary>
	/// シーン描画処理後
	/// </summary>
	void PostDrawScene();

private:

	void VertSetting();
	void CreateBuff();
	//texBuff_の生成
	void CreateTexBuff(WindowsApp* windowsApp);
	//RTVの作成
	void CreateRTV();
	//深度バッファの生成
	void CreateDepth(WindowsApp* windowsApp);
	//DSVの作成
	void CreateDSV();

	void CreatePipline();

	void LoadShader();

	void DrawCommand();
	//SRVの作成
	void CreateSRV();
};