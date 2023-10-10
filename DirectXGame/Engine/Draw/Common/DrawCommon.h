#pragma once
#include"myMath.h"
#include <d3dcompiler.h>
#include<string>

struct PosUvColor
{
	myMath::Vector3 pos;//座標
	myMath::Vector2 uv;//uv座標
	myMath::Vector4 color;//色
};

struct PosNormalUv
{
	myMath::Vector3 pos;//座標
	myMath::Vector3 normal;//法線
	myMath::Vector2 uv;//uv座標
};

struct PosScaleColor
{
	myMath::Vector3 pos; // xyz座標
	float scale;//スケール
	myMath::Vector4 color;//カラー
};

struct matMatBillboard
{
	myMath::Matrix4 mat;
	myMath::Matrix4 matBillboard;
};

//マテリアルよう定数バッファ構造体
struct ConstBuffDataMaterial
{
	//アンビエント係数
	myMath::Vector3 ambient;
	//パディング
	float pad1;
	//ディフューズ係数
	myMath::Vector3 diffuse;
	//パディング
	float pad2;
	//スペキュラー係数
	myMath::Vector3 specular;
	//アルファ
	float alpha;
};

//マテリアル
struct ModelMaterial
{
	//マテリアル名
	std::string name;
	//アンビエント影響度
	myMath::Vector3 ambient = { 0.06f, 0.06f, 0.06f };
	//ディフューズ影響度
	myMath::Vector3 diffuse = { 0.0f,0.0f,0.0f };
	//スペキュラー影響度
	myMath::Vector3 specular = { 0.0f,0.0f,0.0f };

	float shininess = 1.0f;
	//アルファ
	float alpha = 1.0f;
	//テクスチャファイル名
	std::string textureFiename;

	ConstBuffDataMaterial GetConstBuffMaterial();
};

struct worldViewpojCamera
{
	//ワールド行列
	myMath::Matrix4 world;
	//ワールド座標
	myMath::Matrix4 matWorld;
	//カメラ座標(ワールド座標)
	myMath::Vector3 cameraPos;
};

class DrawCommon
{
public:

	/// <summary>
	/// シェーダーのコンパイル
	/// </summary>
	/// <param name="shaderFileName">シェーダーの名前</param>
	/// <param name="entrypointName">エントリーポイント名</param>
	/// <param name="shaderModelName">シェーダーモデルの指定</param>
	/// <param name="blob">シェーダーオブジェクト</param>
	/// <returns></returns>
	static ID3DBlob* ShaderCompile(const wchar_t* shaderFileName, LPCSTR entrypointName, LPCSTR shaderModelName, ID3DBlob* blob);
};