#pragma once
#include"myMath.h"
#include"DirectX_.h"
#include"WindowsApp.h"
#include"TextureManager.h"
#include"DrawCommon.h"
#include<array>
#include"Pipeline.h"

class Sprite
{
private:

	HRESULT result;
	char PADING[4];
	static Microsoft::WRL::ComPtr<ID3D12Device>device;
	static Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>cmdList;

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
	static myMath::Matrix4 matProjection;

	//定数バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource>constBuff;
	//定数バッファのマッピング用ポインタ
	myMath::Matrix4* constBuffMap = nullptr;

	static Microsoft::WRL::ComPtr<ID3DBlob>vsBlob; // 頂点シェーダオブジェクト
	static Microsoft::WRL::ComPtr<ID3DBlob>psBlob; // ピクセルシェーダオブジェクト

	static std::array<PipelineSet, 6> pip;

	int blendMode = (int)BlendMode::Alpha;//初期値半透明合成

public:

	Sprite() {}
	virtual ~Sprite() {}

	static void Initialize();

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
	/// <param name="flipX">X反転</param>
	/// <param name="flipY">Y反転</param>
	void DrawSprite(TextureData& textureData, myMath::Vector2 position, myMath::Vector4 color = { 1.0f,1.0f ,1.0f ,1.0f }, myMath::Vector2 scale = { 1.0f,1.0f }, float rotation = 0.0f, myMath::Vector2 anchorpoint = { 0.5f,0.5f }, bool flipX = false, bool flipY = false);

	/// <summary>
	/// 横連番スプライト描画
	/// </summary>
	/// <param name="textureData">テクスチャデータ</param>
	/// <param name="position">座標</param>
	/// <param name="radiusX">一枚の横の長さ</param>
	/// <param name="num">何枚目か</param>
	/// <param name="color">色</param>
	/// <param name="scale">大きさ</param>
	/// <param name="rotation">回転</param>
	/// <param name="anchorpoint">中心点</param>
	/// <param name="flipX">X反転</param>
	/// <param name="flipY">Y反転</param>
	void DrawAnimationSpriteX(TextureData& textureData, myMath::Vector2 position, float radiusX, uint16_t& num, myMath::Vector4 color = { 1.0f,1.0f ,1.0f ,1.0f }, myMath::Vector2 scale = { 1.0f,1.0f }, float rotation = 0.0f, myMath::Vector2 anchorpoint = { 0.5f,0.5f }, bool flipX = false, bool flipY = false);

	/// <summary>
	/// 縦連番スプライト描画
	/// </summary>
	/// <param name="textureData">テクスチャデータ</param>
	/// <param name="position">座標</param>
	/// <param name="radiusY">一枚の縦の長さ</param>
	/// <param name="num">何枚目か</param>
	/// <param name="color">色</param>
	/// <param name="scale">大きさ</param>
	/// <param name="rotation">回転</param>
	/// <param name="anchorpoint">中心点</param>
	/// <param name="flipX">X反転</param>
	/// <param name="flipY">Y反転</param>
	void DrawAnimationSpriteY(TextureData& textureData, myMath::Vector2 position, float radiusY, uint16_t& num, myMath::Vector4 color = { 1.0f,1.0f ,1.0f ,1.0f }, myMath::Vector2 scale = { 1.0f,1.0f }, float rotation = 0.0f, myMath::Vector2 anchorpoint = { 0.5f,0.5f }, bool flipX = false, bool flipY = false);

	/// <summary>
	/// ブレンドモードのセット
	/// </summary>
	/// <param name="mode">モード</param>
	void SetBlendMode(BlendMode mode);

private:
	void CreateVertexIndexBuffer();
	void CreateConstBuff();
	static void LoadShader();
	void Update(myMath::Vector2 position, myMath::Vector2 scale, float rotation);
	void BlendSet(BlendMode mode);
};