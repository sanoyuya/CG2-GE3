#pragma once
#include"myMath.h"
#include"DirectX_.h"
#include"WindowsApp.h"
#include"TextureManager.h"
#include"Camera.h"
#include"DrawCommon.h"

struct PosUvColor
{
	myMath::Vector3 pos;//座標
	myMath::Vector2 uv;//uv座標
	myMath::Vector4 color;//色
};

class Sprite
{
private:

	HRESULT result;
	char PADING[4];
	Microsoft::WRL::ComPtr<ID3D12Device>device;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>cmdList = nullptr;

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

	uint8_t blendMode = (uint8_t)BlendMode::Alpha;//初期値半透明合成

public:

	Sprite(){}
	virtual ~Sprite(){}

	/// <summary>
	/// スプライトの初期化処理
	/// </summary>
	void SpriteInitialize();

	/// <summary>
	/// スプライトの描画
	/// </summary>
	/// <param name="textureData">テクスチャデータ</param>
	/// <param name="position">座標</param>
	/// <param name="color">色</param>
	/// <param name="scale">大きさ</param>
	/// <param name="rotation">回転</param>
	/// <param name="anchorpoint">中心点</param>
	void DrawSprite(TextureData& textureData, myMath::Vector3 position, myMath::Vector4 color = { 1.0f,1.0f ,1.0f ,1.0f }, myMath::Vector3 scale = { 1.0f,1.0f,1.0f }, myMath::Vector3 rotation = { 0.0f,0.0f,0.0f }, myMath::Vector3 anchorpoint = { 0.5f,0.5f,0.5f });

	/// <summary>
	/// ブレンドモードのセット
	/// </summary>
	/// <param name="mode">モード</param>
	void SetBlendMode(BlendMode mode);

private:
	void CreateVertexIndexBuffer();
	void CreateConstBuff();
	void CreatePipline();
	void LoadShader();
};