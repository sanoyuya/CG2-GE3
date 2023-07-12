#include "DrawCommon.h"
#include <wrl.h>
#include <string>
#pragma comment(lib,"d3dcompiler.lib")

ConstBuffDataMaterial ModelMaterial::GetConstBuffMaterial()
{
	ConstBuffDataMaterial result;
	result.ambient = ambient;
	result.diffuse = diffuse;
	result.specular = specular;
	result.alpha = alpha;
	return result;
}

ID3DBlob* DrawCommon::ShaderCompile(const wchar_t* shaderFileName, LPCSTR entrypointName, LPCSTR shaderModelName, ID3DBlob* blob)
{
	HRESULT result;
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr; // �G���[�I�u�W�F�N�g

	//�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	result = D3DCompileFromFile(
		shaderFileName,	//�V�F�[�_�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,	//�f�o�b�O�p�ݒ�
		entrypointName, shaderModelName,	//�G���g���[�|�C���g���A�V�F�[�_�[���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,	//�f�o�b�O�p�ݒ�
		0,
		&blob, &errorBlob);

	//�G���[�Ȃ�
	if (FAILED(result)) {
		//errorBlob����G���[���e��string�^�ɃR�s�[
		std::string error;
		error.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			error.begin());
		error += "\n";
		//�G���[���e���o�̓E�B���h�E�ɕ\��
		OutputDebugStringA(error.c_str());
		assert(0);
	}

	return blob;
}
