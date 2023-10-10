#pragma once
#include <d3d12.h>
#include<wrl.h>
#include<memory>
#include<array>

enum class BlendMode
{
	None,//ノーブレンド
	Alpha,//半透明合成
	Add,//加算合成
	Sub,//減算合成
	Mul,//乗算合成
	Inv//色反転
};

enum class ShaderMode
{
	Basic,//標準
	Phong,//フォンシェーディング
	Toon,//トゥーンシェーディング
	RimLight,//リムライト
	MultiPhong,//マルチレンダーターゲット用
	SimpleColor//単色シェーダー用
};

struct PipelineSet
{
	//ルートシグネチャ
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
	//パイプランステートの生成
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
};

struct Blob
{
	//頂点シェーダオブジェクト
	Microsoft::WRL::ComPtr<ID3DBlob>vs;
	//ピクセルシェーダオブジェクト
	Microsoft::WRL::ComPtr<ID3DBlob>ps;
	//ジオメトリシェーダオブジェクト
	Microsoft::WRL::ComPtr<ID3DBlob>gs;
};

class Pipeline
{
public://スプライト

	/// <summary>
	/// スプライト用パイプラインの生成
	/// </summary>
	/// <param name="blob">シェーダーオブジェクト</param>
	/// <param name="blend">ブレンドモード</param>
	/// <param name="device">デバイス</param>
	/// <param name="pip">パイプライン</param>
	static void CreateSpritePipline(Blob& blob, BlendMode blend, ID3D12Device* device, std::array<PipelineSet, 6>& pip);

	/// <summary>
	/// パーティクル用パイプラインの生成
	/// </summary>
	/// <param name="blob">シェーダーオブジェクト</param>
	/// <param name="blend">ブレンドモード</param>
	/// <param name="device">デバイス</param>
	/// <param name="pip">パイプライン</param>
	static void CreateParticlePipline(Blob& blob, BlendMode blend, ID3D12Device* device, std::array<PipelineSet, 6>& pip);

public://モデル

	/// <summary>
	/// Basicモデル用パイプライン生成
	/// </summary>
	/// <param name="blob">シェーダーオブジェクト</param>
	/// <param name="blend">ブレンドモード</param>
	/// <param name="device">デバイス</param>
	/// <param name="pip">パイプライン</param>
	static void CreateBasicModelPipline(Blob& blob, BlendMode blend, ID3D12Device* device, std::array<PipelineSet, 6>& pip);

	/// <summary>
	/// Phongモデル用パイプライン生成
	/// </summary>
	/// <param name="blob">シェーダーオブジェクト</param>
	/// <param name="blend">ブレンドモード</param>
	/// <param name="device">デバイス</param>
	/// <param name="pip">パイプライン</param>
	static void CreatePhongModelPipline(Blob& blob, BlendMode blend, ID3D12Device* device, std::array<PipelineSet, 6>& pip);

	/// <summary>
	/// マルチレンダーターゲットPhongモデル用パイプライン生成
	/// </summary>
	/// <param name="blob">シェーダーオブジェクト</param>
	/// <param name="blend">ブレンドモード</param>
	/// <param name="device">デバイス</param>
	/// <param name="pip">パイプライン</param>
	static void CreateMultiPhongModelPipline(Blob& blob, BlendMode blend, ID3D12Device* device, std::array<PipelineSet, 6>& pip);
	
public://ポストエフェクト

	/// <summary>
	/// ポストエフェクト用パイプライン生成
	/// </summary>
	/// <param name="blob">シェーダーオブジェクト</param>
	/// <param name="pip">パイプライン</param>
	static void CreatePostEffectPipline(Blob& blob, PipelineSet& pip);

	static void CreateMultiTexturePipline(Blob& blob, PipelineSet& pip);
};