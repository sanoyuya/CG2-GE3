#pragma once
#include <unordered_map>
#include"DrawCommon.h"
#include"TextureManager.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"ConstantBuffer.h"
#include"Transform.h"
#include"Pipeline.h"
#include"LightManager.h"

struct ModelData
{
	ModelData() = default;
	~ModelData() = default;

	std::string filePath;
	uint32_t modelHandle;

private:

	char PADING1[4] = {};

public:

	TextureData* textureData;

	//頂点バッファ
	std::unique_ptr<VertexBuffer> vertexBuffer;
	//インデックスバッファ
	std::unique_ptr<IndexBuffer> indexBuffer;

private:

	char PADING2[4] = {};

public:

	//インデックスの数
	uint32_t maxIndex = 0;

private:

	char PADING3[4] = {};

public:

	//頂点の数
	uint32_t maxVert = 0;
	//ワールド行列
	myMath::Matrix4 matWorld;
	//頂点データ
	std::vector<PosNormalUv>vertices;
	//頂点インデックス
	std::vector<uint32_t> indices;
	//頂点法線スムージング用データ
	std::unordered_map<uint32_t, std::vector<uint32_t>>smoothData;
	//マテリアル
	ModelMaterial modelMaterial{};
	// 定数バッファ
	std::unique_ptr<ConstantBuffer> constBuffMaterial;

	// 定数バッファビューの設定
	D3D12_CONSTANT_BUFFER_VIEW_DESC constantBufferView = {};

private:

	//コピーコンストラクタ・代入演算子削除
	ModelData& operator=(const ModelData&) = delete;
	ModelData(const ModelData&) = delete;
};

class Model
{
protected:

	static Microsoft::WRL::ComPtr<ID3D12Device> sDevice_;
	static Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> sCmdList_;

	static std::vector<std::string>sFilePaths_;

	static std::unordered_map<std::string, std::unique_ptr<ModelData>> sModelDatas_;

	static uint32_t sModelCount_;

	static const uint32_t sMaxModel_ = 1024;

	ModelData* modelData_ = nullptr;

private:

	static std::array<Blob,6> sBlob_;//シェーダオブジェクト

	static std::array<std::array<PipelineSet, 6>,6> sPip_;

	BlendMode blendMode_ = BlendMode::Alpha;//初期値半透明合成

	static ShaderMode sShaderMode_;

	ShaderMode shaderMode_ = sShaderMode_;//標準

	std::unique_ptr<ConstantBuffer> constantBuff_;

	myMath::Vector4 tmp_;

	//ライト
	static LightManager* sLightManager_;

public:

	/// <summary>
	/// ワールド行列の取得
	/// </summary>
	/// <returns>ワールド行列</returns>
	const myMath::Matrix4& GetMatWorld();

	/// <summary>
	/// 頂点座標を取得
	/// </summary>
	/// <returns>頂点座標配列</returns>
	const std::vector<PosNormalUv>GetVertices();

	/// <summary>
	/// インデックスを取得
	/// </summary>
	/// <returns>インデックス座標配列</returns>
	const std::vector<uint32_t>GetIndices();

	/// <summary>
	/// モデルデータのセット
	/// </summary>
	/// <param name="modelHandle">モデルのハンドル</param>
	void SetModel(const uint32_t modelHandle);

	/// <summary>
	/// ブレンドモードのセット
	/// </summary>
	/// <param name="mode">ブレンドモード</param>
	void SetModelBlendMode(const BlendMode& mode);

	/// <summary>
	/// モデル単体のシェーダーモードのセット
	/// </summary>
	/// <param name="mode">シェーダーモード</param>
	void SetShaderMode(const ShaderMode& mode);

	static void SetStaticShaderMode(const ShaderMode& mode);

	Model();
	virtual ~Model();

	/// <summary>
	/// モデルの描画
	/// </summary>
	/// <param name="transform">Transformのデータ</param>
	/// <param name="color">色(初期値:{ 1.0f,1.0f ,1.0f ,1.0f })</param>
	void DrawModel(Transform* transform, myMath::Vector4 color = { 1.0f,1.0f ,1.0f ,1.0f });

	/// <summary>
	/// モデルの生成
	/// </summary>
	/// <param name="filePath">ファイル名</param>
	/// <param name="smoothing">スムージングするかどうか(初期値:false)</param>
	/// <returns></returns>
	static uint32_t CreateObjModel(const std::string& filePath, bool smoothing = false);

	static uint32_t CreateAssimpModel(const std::string& filePath);

	/// <summary>
	/// ライトのセット
	/// </summary>
	/// <param name="light">ライト</param>
	static void SetLight(LightManager* lightManager_);

	/// <summary>
	/// 静的初期化処理
	/// </summary>
	static void StaticInitialize();

	/// <summary>
	/// 静的解放処理
	/// </summary>
	static void StaticDestory();

private:

	static void LoadShader();

	/// <summary>
	/// パイプライン設定を適用
	/// </summary>
	/// <param name="bMode">ブレンドモード</param>
	/// <param name="sMode">シェーダーモード</param>
	void PiplineSet(BlendMode bMode, ShaderMode sMode);
};