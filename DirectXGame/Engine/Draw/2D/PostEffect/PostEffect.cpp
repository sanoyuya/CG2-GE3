#include "PostEffect.h"

void PostEffect::Initialize()
{
	scale = { 500.0f,500.0f };
	color = { 1.0f,1.0f ,1.0f ,1.0f };

	//テクスチャ読み込み
	tex = TextureManager::GetInstance()->LoadTexture("Resources/white1x1.png");
	Sprite2D::Sprite2DInitialize(tex);
}

void PostEffect::Draw()
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
	SpriteCommon::BlendSet(blendMode);

	//描画コマンド
	SpriteCommon::DrawCommand(texture, vertexBuffer->GetView(), indexBuffer->GetView(), constBuffMaterial.get());
}