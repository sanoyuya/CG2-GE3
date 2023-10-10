#pragma once
#include"myMath.h"
#include"DirectXBase.h"
#include"WindowsApp.h"
#include"TextureManager.h"
#include"DrawCommon.h"
#include<array>
#include"Pipeline.h"
#include"IndexBuffer.h"
#include"VertexBuffer.h"
#include"ConstantBuffer.h"
#include"SpriteCommon.h"

class Sprite2D
{
private:

	HRESULT result_ = S_FALSE;
	char PADING_[4] = {};

	//頂点バッファ
	std::unique_ptr<VertexBuffer> vertexBuffer_ = {};
	//頂点マップ
	PosUvColor* vertMap_ = {};

	//インデックスバッファ
	std::unique_ptr<IndexBuffer> indexBuffer_ = {};

	//インデックスバッファをマッピング
	uint16_t* indexMap_ = 0;

	// 定数バッファ
	std::unique_ptr<ConstantBuffer> constBuffMaterial_ = {};

	//定数バッファのマッピング用ポインタ
	myMath::Matrix4 constBuffMap_ = {};

	//プロジェクション行列
	static myMath::Matrix4 matProjection_;

	BlendMode blendMode_ = BlendMode::Alpha;//初期値半透明合成

	TextureData* texture_ = {};

public:

	Sprite2D() {}
	virtual ~Sprite2D() {}

	/// <summary>
	/// 静的初期化処理
	/// </summary>
	/// <param name="windowsApp">windowsAppのポインタ</param>
	static void StaticInitialize(WindowsApp* windowsApp);

	/// <summary>
	/// スプライトの初期化処理(2D)
	/// </summary>
	/// <param name="handle">テクスチャのハンドル</param>
	void Sprite2DInitialize(uint32_t handle);

	/// <summary>
	/// スプライトの描画(2D)
	/// </summary>
	/// <param name="position">座標</param>
	/// <param name="color">色(初期値:{ 1.0f,1.0f ,1.0f ,1.0f })</param>
	/// <param name="scale">大きさ(初期値:{ 1.0f,1.0f })</param>
	/// <param name="rotation">回転(初期値:0.0f)</param>
	/// <param name="anchorpoint">中心点(初期値:{ 0.5f,0.5f })</param>
	/// <param name="flipX">X反転(初期値:false)</param>
	/// <param name="flipY">Y反転(初期値:false)</param>
	void DrawSprite2D(myMath::Vector2 position, myMath::Vector4 color = { 1.0f,1.0f ,1.0f ,1.0f }, myMath::Vector2 scale = { 1.0f,1.0f }, float rotation = 0.0f, myMath::Vector2 anchorpoint = { 0.5f,0.5f }, bool flipX = false, bool flipY = false);

	/// <summary>
	/// スプライトの切り抜き描画(2D)
	/// </summary>
	/// <param name="position">座標</param>
	/// <param name="clipCenter">切り取りする中心座標</param>
	/// <param name="clipRadius">切り取りする半径</param>
	/// <param name="color">色(初期値:{ 1.0f,1.0f ,1.0f ,1.0f })</param>
	/// <param name="scale">大きさ(初期値:{ 1.0f,1.0f })</param>
	/// <param name="rotation">回転(初期値:0.0f)</param>
	/// <param name="flipX">X反転(初期値:false)</param>
	/// <param name="flipY">Y反転(初期値:false)</param>
	void DrawSpriteClip2D(myMath::Vector2 position, myMath::Vector2 clipCenter, myMath::Vector2 clipRadius, myMath::Vector4 color = { 1.0f,1.0f ,1.0f ,1.0f }, myMath::Vector2 scale = { 1.0f,1.0f }, float rotation = 0.0f, bool flipX = false, bool flipY = false);

	/// <summary>
	/// 横連番スプライト描画(2D)
	/// </summary>
	/// <param name="position">座標</param>
	/// <param name="sheetsNum">枚数</param>
	/// <param name="nowNum">何枚目か</param>
	/// <param name="color">色(初期値:{ 1.0f,1.0f ,1.0f ,1.0f })</param>
	/// <param name="scale">大きさ(初期値:{ 1.0f,1.0f })</param>
	/// <param name="rotation">回転(初期値:0.0f)</param>
	/// <param name="anchorpoint">中心点(初期値:{ 0.5f,0.5f })</param>
	/// <param name="flipX">X反転(初期値:false)</param>
	/// <param name="flipY">Y反転(初期値:false)</param>
	void DrawAnimationSpriteX2D(myMath::Vector2 position, uint16_t sheetsNum, uint16_t& nowNum, myMath::Vector4 color = { 1.0f,1.0f ,1.0f ,1.0f }, myMath::Vector2 scale = { 1.0f,1.0f }, float rotation = 0.0f, myMath::Vector2 anchorpoint = { 0.5f,0.5f }, bool flipX = false, bool flipY = false);

	/// <summary>
	/// 縦連番スプライト描画(2D)
	/// </summary>
	/// <param name="position">座標</param>
	/// <param name="sheetsNum">枚数</param>
	/// <param name="nowNum">何枚目か</param>
	/// <param name="color">色(初期値:{ 1.0f,1.0f ,1.0f ,1.0f })</param>
	/// <param name="scale">大きさ(初期値:{ 1.0f,1.0f })</param>
	/// <param name="rotation">回転(初期値:0.0f)</param>
	/// <param name="anchorpoint">中心点(初期値:{ 0.5f,0.5f })</param>
	/// <param name="flipX">X反転(初期値:false)</param>
	/// <param name="flipY">Y反転(初期値:false)</param>
	void DrawAnimationSpriteY2D(myMath::Vector2 position, uint16_t sheetsNum, uint16_t& nowNum, myMath::Vector4 color = { 1.0f,1.0f ,1.0f ,1.0f }, myMath::Vector2 scale = { 1.0f,1.0f }, float rotation = 0.0f, myMath::Vector2 anchorpoint = { 0.5f,0.5f }, bool flipX = false, bool flipY = false);

	/// <summary>
	/// 縦横連番スプライト描画(2D)
	/// </summary>
	/// <param name="position">座標</param>
	/// <param name="sheetsNumX">横の枚数</param>
	/// <param name="sheetsNumY">縦の枚数</param>
	/// <param name="nowNum">何枚目か</param>
	/// <param name="color">色(初期値:{ 1.0f,1.0f ,1.0f ,1.0f })</param>
	/// <param name="scale">大きさ(初期値:{ 1.0f,1.0f })</param>
	/// <param name="rotation">回転(初期値:0.0f)</param>
	/// <param name="anchorpoint">中心点(初期値:{ 0.5f,0.5f })</param>
	/// <param name="flipX">X反転(初期値:false)</param>
	/// <param name="flipY">Y反転(初期値:false)</param>
	void DrawAnimationSpriteXY2D(myMath::Vector2 position, uint16_t sheetsNumX, uint16_t sheetsNumY, uint16_t& nowNum, myMath::Vector4 color = { 1.0f,1.0f ,1.0f ,1.0f }, myMath::Vector2 scale = { 1.0f,1.0f }, float rotation = 0.0f, myMath::Vector2 anchorpoint = { 0.5f,0.5f }, bool flipX = false, bool flipY = false);

	void DrawCircleGaugeSprite2D(myMath::Vector2 position, float angle = 0.0f, myMath::Vector4 color = { 1.0f,1.0f ,1.0f ,1.0f }, myMath::Vector2 scale = { 1.0f,1.0f }, float rotation = 0.0f, bool flipX = false, bool flipY = false);

	/// <summary>
	/// ブレンドモードのセット(2D)
	/// </summary>
	/// <param name="mode">モード</param>
	void SetSprite2DBlendMode(const BlendMode& mode);

private:

	/// <summary>
	/// バッファの生成処理
	/// </summary>
	void CreateBuff();

	/// <summary>
	/// 行列計算
	/// </summary>
	/// <param name="position">座標</param>
	/// <param name="scale">大きさ</param>
	/// <param name="rotation">角度</param>
	void Update(myMath::Vector2 position, myMath::Vector2 scale, float rotation);
};