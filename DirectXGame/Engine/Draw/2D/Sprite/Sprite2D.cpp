#include "Sprite2D.h"
#include <d3dcompiler.h>
#include"Camera.h"
#include <algorithm>

myMath::Matrix4 Sprite2D::matProjection_;

void Sprite2D::StaticInitialize(WindowsApp* windowsApp)
{
	float width = windowsApp->GetWidth();
	float height = windowsApp->GetHeight();

	myMath::MakeOrthogonalL(0.0f, width, height, 0.0f, 0.0f, 1.0f, matProjection_);
}

void Sprite2D::Sprite2DInitialize(uint32_t handle)
{
	texture_ = TextureManager::GetTextureData(handle);
	CreateBuff();
}

void Sprite2D::DrawSprite2D(myMath::Vector2 position, myMath::Vector4 color, myMath::Vector2 scale, float rotation, myMath::Vector2 anchorpoint, bool flipX, bool flipY)
{
	int isFlipX, isFlipY;
	if (flipX == false)isFlipX = 1;
	else isFlipX = -1;
	if (flipY == false)isFlipY = 1;
	else isFlipY = -1;

	float left = ((0.0f - anchorpoint.x) * texture_->width) * isFlipX;
	float right = ((1.0f - anchorpoint.x) * texture_->width) * isFlipX;
	float top = ((0.0f - anchorpoint.y) * texture_->height) * isFlipY;
	float bottom = ((1.0f - anchorpoint.y) * texture_->height) * isFlipY;

	//頂点データ
	PosUvColor vertices[] =
	{
		{{left,top,0.0f},{0.0f,0.0f},{color.x, color.y, color.z, color.w}},//左上インデックス0
		{{left,bottom,0.0f},{0.0f,1.0f},{color.x, color.y, color.z, color.w}},//左下インデックス1
		{{right,top,0.0f},{1.0f,0.0f},{color.x, color.y, color.z, color.w}},//右上インデックス2
		{{right,bottom,0.0f},{1.0f,1.0f},{color.x, color.y, color.z, color.w}},//右下インデックス3
	};

	//インデックスデータ
	uint32_t indices[] =
	{
		1,0,3,//三角形1つ目
		2,3,0,//三角形2つ目
	};

	//頂点バッファへのデータ転送
	vertexBuffer_->Update(vertices);

	//インデックスバッファへのデータ転送
	indexBuffer_->Update(indices);

	Update(position, scale, rotation);

	// パイプラインステートとルートシグネチャの設定コマンド
	SpriteCommon::BlendSet(blendMode_);

	//描画コマンド
	SpriteCommon::DrawCommand(texture_, vertexBuffer_->GetView(), indexBuffer_->GetView(), constBuffMaterial_.get());
}

void Sprite2D::DrawSpriteClip2D(myMath::Vector2 position, myMath::Vector2 clipCenter, myMath::Vector2 clipRadius, myMath::Vector4 color, myMath::Vector2 scale, float rotation, bool flipX, bool flipY)
{
	int isFlipX, isFlipY;
	if (flipX == false)isFlipX = 1;
	else isFlipX = -1;
	if (flipY == false)isFlipY = 1;
	else isFlipY = -1;

	float left = -clipRadius.x * isFlipX;
	float right = clipRadius.x * isFlipX;
	float top = -clipRadius.y * isFlipY;
	float bottom = clipRadius.y * isFlipY;

	//頂点データ
	PosUvColor vertices[] =
	{
		{{left,top,0.0f},{(clipCenter.x - clipRadius.x) / texture_->width,(clipCenter.y - clipRadius.y)/ texture_->height},{color.x, color.y, color.z, color.w}},//左上インデックス0
		{{left,bottom,0.0f},{(clipCenter.x - clipRadius.x) / texture_->width,(clipCenter.y + clipRadius.y) / texture_->height},{color.x, color.y, color.z, color.w}},//左下インデックス1
		{{right,top,0.0f},{(clipCenter.x + clipRadius.x) / texture_->width,(clipCenter.y - clipRadius.y) / texture_->height},{color.x, color.y, color.z, color.w}},//右上インデックス2
		{{right,bottom,0.0f},{(clipCenter.x + clipRadius.x) / texture_->width,(clipCenter.y + clipRadius.y) / texture_->height},{color.x, color.y, color.z, color.w}},//右下インデックス3
	};

	//インデックスデータ
	uint32_t indices[] =
	{
		1,0,3,//三角形1つ目
		2,3,0,//三角形2つ目
	};

	//頂点バッファへのデータ転送
	vertexBuffer_->Update(vertices);

	//インデックスバッファへのデータ転送
	indexBuffer_->Update(indices);

	Update(position, scale, rotation);

	// パイプラインステートとルートシグネチャの設定コマンド
	SpriteCommon::BlendSet(blendMode_);

	//描画コマンド
	SpriteCommon::DrawCommand(texture_, vertexBuffer_->GetView(), indexBuffer_->GetView(), constBuffMaterial_.get());
}

void Sprite2D::DrawAnimationSpriteX2D(myMath::Vector2 position, uint16_t sheetsNum, uint16_t& nowNum, myMath::Vector4 color, myMath::Vector2 scale, float rotation, myMath::Vector2 anchorpoint, bool flipX, bool flipY)
{
	DrawAnimationSpriteXY2D(position, sheetsNum, 1, nowNum, color, scale, rotation, anchorpoint, flipX, flipY);
}

void Sprite2D::DrawAnimationSpriteY2D(myMath::Vector2 position, uint16_t sheetsNum, uint16_t& nowNum, myMath::Vector4 color, myMath::Vector2 scale, float rotation, myMath::Vector2 anchorpoint, bool flipX, bool flipY)
{
	DrawAnimationSpriteXY2D(position, 1, sheetsNum, nowNum, color, scale, rotation, anchorpoint, flipX, flipY);
}

void Sprite2D::DrawAnimationSpriteXY2D(myMath::Vector2 position, uint16_t sheetsNumX, uint16_t sheetsNumY, uint16_t& nowNum, myMath::Vector4 color, myMath::Vector2 scale, float rotation, myMath::Vector2 anchorpoint, bool flipX, bool flipY)
{
	int isFlipX, isFlipY;
	if (flipX == false)isFlipX = 1;
	else isFlipX = -1;
	if (flipY == false)isFlipY = 1;
	else isFlipY = -1;

	float left = ((0.0f - anchorpoint.x) * texture_->width/ sheetsNumX) * isFlipX;
	float right = ((1.0f - anchorpoint.x) * texture_->width / sheetsNumX) * isFlipX;
	float top = ((0.0f - anchorpoint.y) * texture_->height/ sheetsNumY) * isFlipY;
	float bottom = ((1.0f - anchorpoint.y) * texture_->height / sheetsNumY) * isFlipY;

	uint16_t animationXYNum = sheetsNumX * sheetsNumY;//分割数(総合計)
	uint16_t x = nowNum % sheetsNumX;
	uint16_t y = nowNum / sheetsNumX;

	if (nowNum + 1 > animationXYNum)
	{
		nowNum = 0;//0枚目に戻す処理
	}

	//頂点データ
	PosUvColor vertices[] =
	{
		{{left,top,0.0f},{static_cast<float>(x) / static_cast<float>(sheetsNumX),static_cast<float>(y) / static_cast<float>(sheetsNumY)},{color.x, color.y, color.z, color.w}},//左上インデックス0
		{{left,bottom,0.0f},{static_cast<float>(x) / static_cast<float>(sheetsNumX),(static_cast<float>(y) + 1) / static_cast<float>(sheetsNumY)},{color.x, color.y, color.z, color.w}},//左下インデックス1
		{{right,top,0.0f},{(static_cast<float>(x) + 1) / static_cast<float>(sheetsNumX),static_cast<float>(y) / static_cast<float>(sheetsNumY)},{color.x, color.y, color.z, color.w}},//右上インデックス2
		{{right,bottom,0.0f},{(static_cast<float>(x) + 1) / static_cast<float>(sheetsNumX),(static_cast<float>(y) + 1) / static_cast<float>(sheetsNumY)},{color.x, color.y, color.z, color.w}},//右下インデックス3
	};

	//インデックスデータ
	uint32_t indices[] =
	{
		1,0,3,//三角形1つ目
		2,3,0,//三角形2つ目
	};

	//頂点バッファへのデータ転送
	vertexBuffer_->Update(vertices);

	//インデックスバッファへのデータ転送
	indexBuffer_->Update(indices);

	Update(position, scale, rotation);

	// パイプラインステートとルートシグネチャの設定コマンド
	SpriteCommon::BlendSet(blendMode_);

	//描画コマンド
	SpriteCommon::DrawCommand(texture_, vertexBuffer_->GetView(), indexBuffer_->GetView(), constBuffMaterial_.get());
}

void Sprite2D::DrawCircleGaugeSprite2D(myMath::Vector2 position, float angle, myMath::Vector4 color, myMath::Vector2 scale, float rotation, bool flipX, bool flipY)
{
	int isFlipX, isFlipY;
	if (flipX == false)isFlipX = 1;
	else isFlipX = -1;
	if (flipY == false)isFlipY = 1;
	else isFlipY = -1;

	float left = -0.5f * texture_->width * isFlipX;
	float right = 0.5f * texture_->width * isFlipX;
	float top = -0.5f * texture_->height * isFlipY;
	float bottom = 0.5f * texture_->height * isFlipY;

	float x = sqrt(2.0f) * cosf(angle);
	float y = sqrt(2.0f) * sinf(angle);

	x = std::clamp(x, -1.0f, 1.0f);
	y = std::clamp(y, -1.0f, 1.0f);

	

	//頂点データ
	PosUvColor vertices[] =
	{
		{{left,top,0.0f},{0.0f,0.0f},{color.x, color.y, color.z, color.w}},//左上インデックス0
		{{left,bottom,0.0f},{0.0f,1.0f},{color.x, color.y, color.z, color.w}},//左下インデックス1
		{{right,top,0.0f},{1.0f,0.0f},{color.x, color.y, color.z, color.w}},//右上インデックス2
		{{right,bottom,0.0f},{1.0f,1.0f},{color.x, color.y, color.z, color.w}},//右下インデックス3
	};

	//インデックスデータ
	uint32_t indices[] =
	{
		1,0,3,//三角形1つ目
		2,3,0,//三角形2つ目
	};

	//頂点バッファへのデータ転送
	vertexBuffer_->Update(vertices);

	//インデックスバッファへのデータ転送
	indexBuffer_->Update(indices);

	Update(position, scale, rotation);

	// パイプラインステートとルートシグネチャの設定コマンド
	SpriteCommon::BlendSet(blendMode_);

	//描画コマンド
	SpriteCommon::DrawCommand(texture_, vertexBuffer_->GetView(), indexBuffer_->GetView(), constBuffMaterial_.get());
}

void Sprite2D::SetSprite2DBlendMode(const BlendMode& mode)
{
	blendMode_ = mode;
}

void Sprite2D::CreateBuff()
{
	vertexBuffer_ = std::make_unique<VertexBuffer>();
	vertexBuffer_->Create(4, sizeof(PosUvColor));

	indexBuffer_ = std::make_unique<IndexBuffer>();
	indexBuffer_->Create(6);

	constBuffMaterial_ = std::make_unique<ConstantBuffer>();
	constBuffMaterial_->Create(sizeof(myMath::Matrix4));
}

void Sprite2D::Update(myMath::Vector2 position, myMath::Vector2 scale, float rotation)
{
	myMath::Matrix4 mTrans, mRot, mScale, matWorld;
	//平行移動行列
	mTrans.MakeTranslation({ position.x,position.y,0.0f });
	//回転行列
	mRot.MakeRotation({ 0.0f,0.0f,rotation });
	//スケール行列
	mScale.MakeScaling({ scale.x,scale.y,1.0f });
	//ワールド行列
	matWorld = mScale * mRot * mTrans;

	constBuffMap_ = matWorld * matProjection_;
	constBuffMaterial_->Update(&constBuffMap_);
}