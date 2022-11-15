#pragma once
#include"myMath.h"
#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")

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

namespace DrawCommon
{
	/// <summary>
	/// シェーダの読み込みとコンパイル
	/// </summary>
	/// <param name="shaderFileName">ファイルの名前</param>
	/// <param name="entrypointName">エントリーポイントの名前</param>
	/// <param name="shaderModelName">シェーダーモデル指定</param>
	/// <param name="blob">シェーダオブジェクト</param>
	/// <returns>シェーダの読み込みとコンパイルをしたシェーダオブジェクト</returns>
	ID3DBlob* ShaderCompile(const wchar_t* shaderFileName,LPCSTR entrypointName, LPCSTR shaderModelName, ID3DBlob* blob);
}