#pragma once
#include"DrawCommon.h"
#include<memory>
#include"SpriteCommon.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "TextureManager.h"
#include"Camera.h"
#include"Transform.h"

enum class BillboardFlag
{
	NonBillboard,//ビルボードをしない
	AllBillboard,//すべて打ち消す
	XBillboard,//X軸を打ち消す
	YBillboard,//Y軸を打ち消す
	XYBillboard//Z軸を打ち消す
};

class Sprite3D
{
private:

	HRESULT result = S_OK;
	char PADING[4] = {};

	//頂点バッファ
	std::unique_ptr<VertexBuffer> vertexBuffer = {};
	//頂点マップ
	PosUvColor* vertMap = {};

	//インデックスバッファ
	std::unique_ptr<IndexBuffer> indexBuffer = {};

	//インデックスバッファをマッピング
	uint16_t* indexMap = 0;

	// 定数バッファ
	std::unique_ptr<ConstantBuffer> constBuffMaterial = {};

	//定数バッファのマッピング用ポインタ
	myMath::Matrix4 constBuffMap = {};

	BlendMode blendMode = BlendMode::Alpha;//初期値半透明合成

	TextureData* texture = {};

public:

	Sprite3D() {}
	virtual ~Sprite3D() {}

	/// <summary>
	/// スプライトの初期化処理(3D)
	/// </summary>
	void Sprite3DInitialize(uint32_t handle);

	/// <summary>
	/// スプライトの描画(3D)
	/// </summary>
	/// <param name="camera">カメラ</param>
	/// <param name="transform">Transformのデータ</param>
	/// <param name="billboardFlag">ビルボードの種類(初期値:NonBillboard)</param>
	/// <param name="color">色(初期値:{ 1.0f,1.0f ,1.0f ,1.0f })</param>
	/// <param name="anchorpoint">中心点(初期値:{ 0.5f,0.5f })</param>
	/// <param name="flipX">X反転</param>
	/// <param name="flipY">Y反転</param>
	void DrawSprite3D(Camera* camera, Transform& transform, BillboardFlag billboardFlag = BillboardFlag::NonBillboard, myMath::Vector4 color = { 1.0f,1.0f ,1.0f ,1.0f }, myMath::Vector2 anchorpoint = { 0.5f,0.5f }, bool flipX = false, bool flipY = false);

	/// <summary>
	/// スプライトの切り取り描画(3D)
	/// </summary>
	/// <param name="camera">カメラ</param>
	/// <param name="transform">Transformのデータ</param>
	/// <param name="clipCenter">切り取りする中心座標</param>
	/// <param name="clipRadius">切り取りする半径</param>
	/// <param name="billboardFlag">ビルボードの種類(初期値:NonBillboard)</param>
	/// <param name="color">色(初期値:{ 1.0f,1.0f ,1.0f ,1.0f })</param>
	/// <param name="flipX">X反転</param>
	/// <param name="flipY">Y反転</param>
	void DrawSpriteClip3D(Camera* camera, Transform& transform, myMath::Vector2 clipCenter, myMath::Vector2 clipRadius, BillboardFlag billboardFlag = BillboardFlag::NonBillboard, myMath::Vector4 color = { 1.0f,1.0f ,1.0f ,1.0f }, bool flipX = false, bool flipY = false);

	/// <summary>
	/// 横連番スプライト描画(3D)
	/// </summary>
	/// <param name="camera">カメラ</param>
	/// <param name="transform">Transformのデータ</param>
	/// <param name="sheetsNum">枚数</param>
	/// <param name="nowNum">何枚目か</param>
	/// <param name="billboardFlag">ビルボードの種類(初期値:NonBillboard)</param>
	/// <param name="color">色(初期値:{ 1.0f,1.0f ,1.0f ,1.0f })</param>
	/// <param name="anchorpoint">中心点</param>
	/// <param name="flipX">X反転</param>
	/// <param name="flipY">Y反転</param>
	void DrawAnimationSpriteX3D(Camera* camera, Transform& transform, uint16_t sheetsNum, uint16_t& nowNum, BillboardFlag billboardFlag = BillboardFlag::NonBillboard, myMath::Vector4 color = { 1.0f,1.0f ,1.0f ,1.0f }, myMath::Vector2 anchorpoint = { 0.5f,0.5f }, bool flipX = false, bool flipY = false);

	/// <summary>
	/// 縦連番スプライト描画(3D)
	/// </summary>
	/// <param name="camera">カメラ</param>
	/// <param name="transform">Transformのデータ</param>
	/// <param name="sheetsNum">枚数</param>
	/// <param name="nowNum">何枚目か</param>
	/// <param name="billboardFlag">ビルボードの種類(初期値:NonBillboard)</param>
	/// <param name="color">色(初期値:{ 1.0f,1.0f ,1.0f ,1.0f })</param>
	/// <param name="anchorpoint">中心点</param>
	/// <param name="flipX">X反転</param>
	/// <param name="flipY">Y反転</param>
	void DrawAnimationSpriteY3D(Camera* camera, Transform& transform, uint16_t sheetsNum, uint16_t& nowNum, BillboardFlag billboardFlag = BillboardFlag::NonBillboard, myMath::Vector4 color = { 1.0f,1.0f ,1.0f ,1.0f }, myMath::Vector2 anchorpoint = { 0.5f,0.5f }, bool flipX = false, bool flipY = false);

	/// <summary>
	/// 縦横連番スプライト描画(3D)
	/// </summary>
	/// <param name="camera">カメラ</param>
	/// <param name="transform">Transformのデータ</param>
	/// <param name="sheetsNumX">横の枚数</param>
	/// <param name="sheetsNumY">縦の枚数</param>
	/// <param name="nowNum">何枚目か</param>
	/// <param name="billboardFlag">ビルボードの種類(初期値:NonBillboard)</param>
	/// <param name="color">色(初期値:{ 1.0f,1.0f ,1.0f ,1.0f })</param>
	/// <param name="anchorpoint">中心点</param>
	/// <param name="flipX">X反転</param>
	/// <param name="flipY">Y反転</param>
	void DrawAnimationSpriteXY3D(Camera* camera, Transform& transform, uint16_t sheetsNumX, uint16_t sheetsNumY, uint16_t& nowNum, BillboardFlag billboardFlag = BillboardFlag::NonBillboard, myMath::Vector4 color = { 1.0f,1.0f ,1.0f ,1.0f }, myMath::Vector2 anchorpoint = { 0.5f,0.5f }, bool flipX = false, bool flipY = false);

	/// <summary>
	/// ブレンドモードのセット(3D)
	/// </summary>
	/// <param name="mode">モード</param>
	void SetSprite3DBlendMode(const BlendMode& mode);

private:
	void CreateVertexIndexBuffer();
	void CreateConstBuff();
	void Update(Camera* camera, Transform transform,BillboardFlag flag);
	//void Update(myMath::Vector2 position, myMath::Vector2 scale, float rotation);
};

