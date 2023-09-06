#include "Sprite3D.h"

void Sprite3D::Sprite3DInitialize(uint32_t handle)
{
	texture_ = TextureManager::GetTextureData(handle);
	CreateBuff();
}

void Sprite3D::DrawSprite3D(Camera* camera, Transform& transform, BillboardFlag flag, myMath::Vector4 color, myMath::Vector2 anchorpoint, bool flipX, bool flipY)
{
	int isFlipX, isFlipY;
	if (flipX == false)isFlipX = 1;
	else isFlipX = -1;
	if (flipY == false)isFlipY = -1;
	else isFlipY = 1;

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

	Update(camera, transform, flag);

	// パイプラインステートとルートシグネチャの設定コマンド
	SpriteCommon::BlendSet(blendMode_);

	//描画コマンド
	SpriteCommon::DrawCommand(texture_, vertexBuffer_->GetView(), indexBuffer_->GetView(), constBuffMaterial_.get());
}

void Sprite3D::DrawSpriteClip3D(Camera* camera, Transform& transform, myMath::Vector2 clipCenter, myMath::Vector2 clipRadius, BillboardFlag billboardFlag, myMath::Vector4 color, bool flipX, bool flipY)
{
	int isFlipX, isFlipY;
	if (flipX == false)isFlipX = 1;
	else isFlipX = -1;
	if (flipY == false)isFlipY = -1;
	else isFlipY = 1;

	float left = -clipRadius.x * isFlipX;
	float right = clipRadius.x * isFlipX;
	float top = -clipRadius.y * isFlipY;
	float bottom = clipRadius.y * isFlipY;

	//頂点データ
	PosUvColor vertices[] =
	{
		{{left,top,0.0f},{(clipCenter.x - clipRadius.x) / texture_->width,(clipCenter.y - clipRadius.y) / texture_->height},{color.x, color.y, color.z, color.w}},//左上インデックス0
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

	Update(camera, transform, billboardFlag);

	// パイプラインステートとルートシグネチャの設定コマンド
	SpriteCommon::BlendSet(blendMode_);

	//描画コマンド
	SpriteCommon::DrawCommand(texture_, vertexBuffer_->GetView(), indexBuffer_->GetView(), constBuffMaterial_.get());
}

void Sprite3D::DrawAnimationSpriteX3D(Camera* camera, Transform& transform, uint16_t sheetsNum, uint16_t& nowNum, BillboardFlag billboardFlag, myMath::Vector4 color, myMath::Vector2 anchorpoint, bool flipX, bool flipY)
{
	DrawAnimationSpriteXY3D(camera, transform, sheetsNum, 1, nowNum, billboardFlag, color, anchorpoint, flipX, flipY);
}

void Sprite3D::DrawAnimationSpriteY3D(Camera* camera, Transform& transform, uint16_t sheetsNum, uint16_t& nowNum, BillboardFlag billboardFlag, myMath::Vector4 color, myMath::Vector2 anchorpoint, bool flipX, bool flipY)
{
	DrawAnimationSpriteXY3D(camera, transform, 1, sheetsNum, nowNum, billboardFlag, color, anchorpoint, flipX, flipY);
}

void Sprite3D::DrawAnimationSpriteXY3D(Camera* camera, Transform& transform, uint16_t sheetsNumX, uint16_t sheetsNumY, uint16_t& nowNum, BillboardFlag billboardFlag, myMath::Vector4 color, myMath::Vector2 anchorpoint, bool flipX, bool flipY)
{
	int isFlipX, isFlipY;
	if (flipX == false)isFlipX = 1;
	else isFlipX = -1;
	if (flipY == false)isFlipY = -1;
	else isFlipY = 1;

	float left = ((0.0f - anchorpoint.x) * texture_->width / sheetsNumX) * isFlipX;
	float right = ((1.0f - anchorpoint.x) * texture_->width / sheetsNumX) * isFlipX;
	float top = ((0.0f - anchorpoint.y) * texture_->height / sheetsNumY) * isFlipY;
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

	Update(camera, transform, billboardFlag);

	// パイプラインステートとルートシグネチャの設定コマンド
	SpriteCommon::BlendSet(blendMode_);

	//描画コマンド
	SpriteCommon::DrawCommand(texture_, vertexBuffer_->GetView(), indexBuffer_->GetView(), constBuffMaterial_.get());
}

void Sprite3D::SetSprite3DBlendMode(const BlendMode& mode)
{
	blendMode_ = mode;
}

void Sprite3D::CreateBuff()
{
	vertexBuffer_ = std::make_unique<VertexBuffer>();
	vertexBuffer_->Create(4, sizeof(PosUvColor));

	indexBuffer_ = std::make_unique<IndexBuffer>();
	indexBuffer_->Create(6);

	constBuffMaterial_ = std::make_unique<ConstantBuffer>();
	constBuffMaterial_->Create(sizeof(myMath::Matrix4));
}

void Sprite3D::Update(Camera* camera, Transform transform, BillboardFlag flag)
{
	myMath::Matrix4 mTrans, mRot, mScale;
	myMath::Matrix4 mat = camera->GetMatView();

	//平行移動行列
	mTrans.MakeTranslation(transform.translation);
	//回転行列
	mRot.MakeRotation(transform.rotation);
	//スケール行列
	mScale.MakeScaling(transform.scale);

	switch (flag)
	{
	case BillboardFlag::NonBillboard:
		transform.matWorld = mScale * mRot * mTrans;
		if (transform.parent)
		{
			transform.matWorld *= transform.parent->matWorld;
		}
		transform.matWorld *= camera->GetMatViewInverse() * camera->GetMatProjection();
		break;
	case BillboardFlag::AllBillboard:

		mat.m[3][0] = 0;
		mat.m[3][1] = 0;
		mat.m[3][2] = 0;
		mat.m[3][3] = 1;

		transform.matWorld = mScale * mRot * mat * mTrans;
		if (transform.parent)
		{
			transform.matWorld *= transform.parent->matWorld;
		}
		transform.matWorld *= camera->GetMatViewInverse() * camera->GetMatProjection();
		break;

	case BillboardFlag::XBillboard:

		mat.m[1][0] = 0;
		mat.m[1][1] = 1;
		mat.m[1][2] = 0;
		mat.m[1][3] = 0;

		mat.m[3][0] = 0;
		mat.m[3][1] = 0;
		mat.m[3][2] = 0;
		mat.m[3][3] = 1;

		transform.matWorld = mScale * mRot * mat * mTrans;
		if (transform.parent)
		{
			transform.matWorld *= transform.parent->matWorld;
		}
		transform.matWorld *= camera->GetMatViewInverse() * camera->GetMatProjection();
		break;

	case BillboardFlag::YBillboard:

		mat.m[0][0] = 1;
		mat.m[0][1] = 0;
		mat.m[0][2] = 0;
		mat.m[0][3] = 0;

		mat.m[3][0] = 0;
		mat.m[3][1] = 0;
		mat.m[3][2] = 0;
		mat.m[3][3] = 1;

		transform.matWorld = mScale * mRot * mat * mTrans;
		if (transform.parent)
		{
			transform.matWorld *= transform.parent->matWorld;
		}
		transform.matWorld *= camera->GetMatViewInverse() * camera->GetMatProjection();
		break;

	case BillboardFlag::XYBillboard:

		mat.m[2][0] = 0;
		mat.m[2][1] = 0;
		mat.m[2][2] = 1;
		mat.m[2][3] = 0;

		mat.m[3][0] = 0;
		mat.m[3][1] = 0;
		mat.m[3][2] = 0;
		mat.m[3][3] = 1;

		transform.matWorld = mScale * mRot * mat * mTrans;
		if (transform.parent)
		{
			transform.matWorld *= transform.parent->matWorld;
		}
		transform.matWorld *= camera->GetMatViewInverse() * camera->GetMatProjection();
		break;
	}

	transform.Update();
	constBuffMap_ = transform.matWorld;
	constBuffMaterial_->Update(&constBuffMap_);
}