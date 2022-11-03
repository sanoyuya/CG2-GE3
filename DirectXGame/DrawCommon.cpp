#include "DrawCommon.h"
#include <wrl.h>
#include <string>

namespace DrawCommon
{
	ID3DBlob* DrawCommon::ShaderCompile(const wchar_t* shaderFilename, LPCSTR entrypointname, LPCSTR shaderModelName, ID3DBlob* blob)
	{
		HRESULT result;
		Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr; // エラーオブジェクト

		//シェーダの読み込みとコンパイル
		result = D3DCompileFromFile(
			shaderFilename,	//シェーダファイル名
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,	//デバッグ用設定
			entrypointname, shaderModelName,	//エントリーポイント名、シェーダーモデル指定
			D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,	//デバッグ用設定
			0,
			&blob, &errorBlob);

		//エラーなら
		if (FAILED(result)) {
			//errorBlobからエラー内容をstring型にコピー
			std::string error;
			error.resize(errorBlob->GetBufferSize());

			std::copy_n((char*)errorBlob->GetBufferPointer(),
				errorBlob->GetBufferSize(),
				error.begin());
			error += "\n";
			//エラー内容を出力ウィンドウに表示
			OutputDebugStringA(error.c_str());
			assert(0);
		}

		return blob;
	}
}