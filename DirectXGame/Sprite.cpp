#include "Sprite.h"
#include <d3dcompiler.h>
#include"Camera.h"

Microsoft::WRL::ComPtr<ID3D12Device>Sprite::device;
Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>Sprite::cmdList;
myMath::Matrix4 Sprite::matProjection;
Blob Sprite::blob;//シェーダオブジェクト
std::array<PipelineSet, 6> Sprite::pip;

void Sprite::StaticInitialize()
{
	device = DirectX_::GetInstance()->GetDevice();
	cmdList = DirectX_::GetInstance()->GetCommandList();

	float width = static_cast<float>(WindowsApp::GetInstance()->GetWidth());
	float height = static_cast<float>(WindowsApp::GetInstance()->GetHeight());

	myMath::MakeOrthogonalL(0.0f, width, height, 0.0f, 0.0f, 1.0f, matProjection);

	LoadShader();

	for (int i = 0; i < pip.size(); i++)
	{
		Pipeline::CreateSpritePipline(blob, (BlendMode)i, device.Get(), pip);
	}
}

void Sprite::SpriteInitialize(uint32_t handle)
{
	texture = TextureManager::GetTextureData(handle);
	CreateVertexIndexBuffer();
	CreateConstBuff();
}

void Sprite::DrawSprite(myMath::Vector2 position, myMath::Vector4 color, myMath::Vector2 scale, float rotation, myMath::Vector2 anchorpoint, bool flipX, bool flipY)
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
	BlendSet((BlendMode)blendMode);

	vbView = vertexBuffer->GetView();
	ibView = indexBuffer->GetView();

	// プリミティブ形状の設定コマンド
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト
	// 頂点バッファビューの設定コマンド
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	//定数バッファビュー(CBV)の設定コマンド
	cmdList->SetGraphicsRootConstantBufferView(0, constBuffMaterial->GetAddress());
	//SRVヒープの設定コマンド
	cmdList->SetDescriptorHeaps(1, texture->srvHeap.GetAddressOf());
	//SRVヒープの先頭ハンドルを取得(SRVを指しているはず)
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = texture->gpuHandle;
	//SRVヒープ先頭にあるSRVをルートパラメーター1番に設定
	cmdList->SetGraphicsRootDescriptorTable(1, srvGpuHandle);
	//インデックスバッファビューの設定コマンド
	cmdList->IASetIndexBuffer(&ibView);

	// 描画コマンド
	cmdList->DrawIndexedInstanced(_countof(indices), 1, 0, 0, 0);
}

void Sprite::DrawSpriteClip(myMath::Vector2 position, myMath::Vector2 clipCenter, myMath::Vector2 clipRadius, myMath::Vector4 color, myMath::Vector2 scale, float rotation, bool flipX, bool flipY)
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
	BlendSet((BlendMode)blendMode);

	vbView = vertexBuffer->GetView();
	ibView = indexBuffer->GetView();

	// プリミティブ形状の設定コマンド
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト
	// 頂点バッファビューの設定コマンド
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	//定数バッファビュー(CBV)の設定コマンド
	cmdList->SetGraphicsRootConstantBufferView(0, constBuffMaterial->GetAddress());
	//SRVヒープの設定コマンド
	cmdList->SetDescriptorHeaps(1, texture->srvHeap.GetAddressOf());
	//SRVヒープの先頭ハンドルを取得(SRVを指しているはず)
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = texture->gpuHandle;
	//SRVヒープ先頭にあるSRVをルートパラメーター1番に設定
	cmdList->SetGraphicsRootDescriptorTable(1, srvGpuHandle);
	//インデックスバッファビューの設定コマンド
	cmdList->IASetIndexBuffer(&ibView);

	// 描画コマンド
	cmdList->DrawIndexedInstanced(_countof(indices), 1, 0, 0, 0);
}

void Sprite::DrawAnimationSpriteX(myMath::Vector2 position, uint16_t sheetsNum, uint16_t& nowNum, myMath::Vector4 color, myMath::Vector2 scale, float rotation, myMath::Vector2 anchorpoint, bool flipX, bool flipY)
{
	DrawAnimationSpriteXY(position, sheetsNum, 1, nowNum, color, scale, rotation, anchorpoint, flipX, flipY);
}

void Sprite::DrawAnimationSpriteY(myMath::Vector2 position, uint16_t sheetsNum, uint16_t& nowNum, myMath::Vector4 color, myMath::Vector2 scale, float rotation, myMath::Vector2 anchorpoint, bool flipX, bool flipY)
{
	DrawAnimationSpriteXY(position, 1, sheetsNum, nowNum, color, scale, rotation, anchorpoint, flipX, flipY);
}

void Sprite::DrawAnimationSpriteXY(myMath::Vector2 position, uint16_t sheetsNumX, uint16_t sheetsNumY, uint16_t& nowNum, myMath::Vector4 color, myMath::Vector2 scale, float rotation, myMath::Vector2 anchorpoint, bool flipX, bool flipY)
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
	BlendSet((BlendMode)blendMode);

	vbView = vertexBuffer->GetView();
	ibView = indexBuffer->GetView();

	// プリミティブ形状の設定コマンド
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト
	// 頂点バッファビューの設定コマンド
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	//定数バッファビュー(CBV)の設定コマンド
	cmdList->SetGraphicsRootConstantBufferView(0, constBuffMaterial->GetAddress());
	//SRVヒープの設定コマンド
	cmdList->SetDescriptorHeaps(1, texture->srvHeap.GetAddressOf());
	//SRVヒープの先頭ハンドルを取得(SRVを指しているはず)
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = texture->gpuHandle;
	//SRVヒープ先頭にあるSRVをルートパラメーター1番に設定
	cmdList->SetGraphicsRootDescriptorTable(1, srvGpuHandle);
	//インデックスバッファビューの設定コマンド
	cmdList->IASetIndexBuffer(&ibView);

	// 描画コマンド
	cmdList->DrawIndexedInstanced(_countof(indices), 1, 0, 0, 0);
}

void Sprite::SetSpriteBlendMode(BlendMode mode)
{
	blendMode = int(mode);
}

void Sprite::CreateVertexIndexBuffer()
{
	vertexBuffer = std::make_unique<VertexBuffer>();
	vertexBuffer->Create(4, sizeof(PosUvColor));

	indexBuffer = std::make_unique<IndexBuffer>();
	indexBuffer->Create(6);
}

void Sprite::CreateConstBuff()
{
	constBuffMaterial = std::make_unique<ConstantBuffer>();
	constBuffMaterial->Create(sizeof(myMath::Matrix4));
}

void Sprite::LoadShader()
{
	//頂点シェーダの読み込みとコンパイル
	blob.vs = DrawCommon::ShaderCompile(L"Resources/shaders/SpriteVS.hlsl", "main", "vs_5_0", blob.vs.Get());
	//ピクセルシェーダの読み込みとコンパイル
	blob.ps = DrawCommon::ShaderCompile(L"Resources/shaders/SpritePS.hlsl", "main", "ps_5_0", blob.ps.Get());
}

void Sprite::Update(myMath::Vector2 position, myMath::Vector2 scale, float rotation)
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

void Sprite::BlendSet(BlendMode mode)
{
	switch (mode)
	{
	case BlendMode::None:

		cmdList->SetPipelineState(pip[0].pipelineState.Get());
		cmdList->SetGraphicsRootSignature(pip[0].rootSignature.Get());

		break;

	case BlendMode::Alpha:

		cmdList->SetPipelineState(pip[1].pipelineState.Get());
		cmdList->SetGraphicsRootSignature(pip[1].rootSignature.Get());

		break;

	case BlendMode::Add:

		cmdList->SetPipelineState(pip[2].pipelineState.Get());
		cmdList->SetGraphicsRootSignature(pip[2].rootSignature.Get());

		break;

	case BlendMode::Sub:

		cmdList->SetPipelineState(pip[3].pipelineState.Get());
		cmdList->SetGraphicsRootSignature(pip[3].rootSignature.Get());

		break;

	case BlendMode::Mul:

		cmdList->SetPipelineState(pip[4].pipelineState.Get());
		cmdList->SetGraphicsRootSignature(pip[4].rootSignature.Get());

		break;

	case BlendMode::Inv:

		cmdList->SetPipelineState(pip[5].pipelineState.Get());
		cmdList->SetGraphicsRootSignature(pip[5].rootSignature.Get());

		break;
	}
}