#include "Sprite2D.h"
#include <d3dcompiler.h>
#include"Camera.h"

myMath::Matrix4 Sprite2D::matProjection;

void Sprite2D::StaticInitialize()
{
	float width = static_cast<float>(WindowsApp::GetInstance()->GetWidth());
	float height = static_cast<float>(WindowsApp::GetInstance()->GetHeight());

	myMath::MakeOrthogonalL(0.0f, width, height, 0.0f, 0.0f, 1.0f, matProjection);
}

void Sprite2D::Sprite2DInitialize(uint32_t handle)
{
	texture = TextureManager::GetTextureData(handle);
	CreateVertexIndexBuffer();
	CreateConstBuff();
}

void Sprite2D::DrawSprite2D(myMath::Vector2 position, myMath::Vector4 color, myMath::Vector2 scale, float rotation, myMath::Vector2 anchorpoint, bool flipX, bool flipY)
{
	int isFlipX, isFlipY;
	if (flipX == false)isFlipX = 1;
	else isFlipX = -1;
	if (flipY == false)isFlipY = 1;
	else isFlipY = -1;

	float left = ((0.0f - anchorpoint.x) * texture->width) * isFlipX;
	float right = ((1.0f - anchorpoint.x) * texture->width) * isFlipX;
	float top = ((0.0f - anchorpoint.y) * texture->height) * isFlipY;
	float bottom = ((1.0f - anchorpoint.y) * texture->height) * isFlipY;

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
	vertexBuffer->Update(vertices);

	//インデックスバッファへのデータ転送
	indexBuffer->Update(indices);

	Update(position, scale, rotation);

	// パイプラインステートとルートシグネチャの設定コマンド
	SpriteCommon::BlendSet((BlendMode)blendMode);

	//描画コマンド
	SpriteCommon::DrawCommand(texture, vertexBuffer->GetView(), indexBuffer->GetView(), constBuffMaterial.get());
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
		{{left,top,0.0f},{(clipCenter.x - clipRadius.x) / texture->width,(clipCenter.y - clipRadius.y)/ texture->height},{color.x, color.y, color.z, color.w}},//左上インデックス0
		{{left,bottom,0.0f},{(clipCenter.x - clipRadius.x) / texture->width,(clipCenter.y + clipRadius.y) / texture->height},{color.x, color.y, color.z, color.w}},//左下インデックス1
		{{right,top,0.0f},{(clipCenter.x + clipRadius.x) / texture->width,(clipCenter.y - clipRadius.y) / texture->height},{color.x, color.y, color.z, color.w}},//右上インデックス2
		{{right,bottom,0.0f},{(clipCenter.x + clipRadius.x) / texture->width,(clipCenter.y + clipRadius.y) / texture->height},{color.x, color.y, color.z, color.w}},//右下インデックス3
	};

	//インデックスデータ
	uint32_t indices[] =
	{
		1,0,3,//三角形1つ目
		2,3,0,//三角形2つ目
	};

	//頂点バッファへのデータ転送
	vertexBuffer->Update(vertices);

	//インデックスバッファへのデータ転送
	indexBuffer->Update(indices);

	Update(position, scale, rotation);

	// パイプラインステートとルートシグネチャの設定コマンド
	SpriteCommon::BlendSet((BlendMode)blendMode);

	//描画コマンド
	SpriteCommon::DrawCommand(texture, vertexBuffer->GetView(), indexBuffer->GetView(), constBuffMaterial.get());
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

	float left = ((0.0f - anchorpoint.x) * texture->width/ sheetsNumX) * isFlipX;
	float right = ((1.0f - anchorpoint.x) * texture->width / sheetsNumX) * isFlipX;
	float top = ((0.0f - anchorpoint.y) * texture->height/ sheetsNumY) * isFlipY;
	float bottom = ((1.0f - anchorpoint.y) * texture->height / sheetsNumY) * isFlipY;

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
		{{left,top,0.0f},{(float)x / (float)sheetsNumX,(float)y / (float)sheetsNumY},{color.x, color.y, color.z, color.w}},//左上インデックス0
		{{left,bottom,0.0f},{(float)x / (float)sheetsNumX,((float)y + 1) / (float)sheetsNumY},{color.x, color.y, color.z, color.w}},//左下インデックス1
		{{right,top,0.0f},{((float)x + 1) / (float)sheetsNumX,(float)y / (float)sheetsNumY},{color.x, color.y, color.z, color.w}},//右上インデックス2
		{{right,bottom,0.0f},{((float)x + 1) / (float)sheetsNumX,((float)y + 1) / (float)sheetsNumY},{color.x, color.y, color.z, color.w}},//右下インデックス3
	};

	//インデックスデータ
	uint32_t indices[] =
	{
		1,0,3,//三角形1つ目
		2,3,0,//三角形2つ目
	};

	//頂点バッファへのデータ転送
	vertexBuffer->Update(vertices);

	//インデックスバッファへのデータ転送
	indexBuffer->Update(indices);

	Update(position, scale, rotation);

	// パイプラインステートとルートシグネチャの設定コマンド
	SpriteCommon::BlendSet((BlendMode)blendMode);

	//描画コマンド
	SpriteCommon::DrawCommand(texture, vertexBuffer->GetView(), indexBuffer->GetView(), constBuffMaterial.get());
}

void Sprite2D::SetSprite2DBlendMode(BlendMode mode)
{
	blendMode = static_cast<int>(mode);
}

void Sprite2D::CreateVertexIndexBuffer()
{
	vertexBuffer = std::make_unique<VertexBuffer>();
	vertexBuffer->Create(4, sizeof(PosUvColor));

	indexBuffer = std::make_unique<IndexBuffer>();
	indexBuffer->Create(6);
}

void Sprite2D::CreateConstBuff()
{
	constBuffMaterial = std::make_unique<ConstantBuffer>();
	constBuffMaterial->Create(sizeof(myMath::Matrix4));
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

	constBuffMap = matWorld * matProjection;
	constBuffMaterial->Update(&constBuffMap);
}