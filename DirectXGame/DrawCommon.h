#pragma once
#include"myMath.h"
#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")

struct PosUvColor
{
	myMath::Vector3 pos;//ÀW
	myMath::Vector2 uv;//uvÀW
	myMath::Vector4 color;//F
};

enum class BlendMode
{
	None,//m[uh
	Alpha,//¼§¾¬
	Add,//ÁZ¬
	Sub,//¸Z¬
	Mul,//æZ¬
	Inv//F½]
};

namespace DrawCommon
{
	ID3DBlob* ShaderCompile(const wchar_t* shaderFileName,LPCSTR entrypointname, LPCSTR shaderModelName, ID3DBlob* blob);
}