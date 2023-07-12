#pragma once
#include"WindowsApp.h"
#include"DirectXBase.h"
#include "DrawCommon.h"
#include"Pipeline.h"
#include"IndexBuffer.h"
#include"VertexBuffer.h"
#include"ConstantBuffer.h"
#include"TextureManager.h"
#include"myMath.h"

struct VertexPosUV
{
	myMath::Vector3 pos;//座標
	myMath::Vector2 uv;//uv座標
};

enum EffectMode
{
	None,//何もしない
	BrightnessUP,//明度を2倍で出力
	Inverse,//色反転
	Blur,//ぼかし
	GaussianBlur,//ガウシアンブラー	
	GrayScale,//モノクロ
	SepiaColor,//セピアカラー
	UVShift,//UVずらし
	Bloom//ブルーム
};

class PostEffect
{
private:

	Microsoft::WRL::ComPtr<ID3D12Resource>texBuff_;

	DescriptorHeap::DescriptorHeapViewHandle handle_;

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
	float constBuffMap_ = {};
	//プロジェクション行列
	static myMath::Matrix4 matProjection_;

	//シェーダオブジェクト
	static std::array<Blob, 9> sBlob_;
	//パイプライン
	static std::array<PipelineSet, 9> sPip_;

	//画面クリアカラー
	static const float sClearColor_[4];

	static EffectMode sEffectMode_;

	static float power_;

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

public:

	static void SetEffectMode(const EffectMode& mode);

	static void SetPower(const float power);

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
	//パイプライン生成
	void CreatePipline();
	//シェーダー読み込み
	void LoadShader();
	//描画コマンド
	void DrawCommand();
	//SRVの作成
	void CreateSRV();
	//パイプラインステートとルートシグネチャの設定コマンド
	void SetPipline();
};