#pragma once
#include"myMath.h"
#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")

struct PosUvColor
{
	myMath::Vector3 pos;//���W
	myMath::Vector2 uv;//uv���W
	myMath::Vector4 color;//�F
};

enum class BlendMode
{
	None,//�m�[�u�����h
	Alpha,//����������
	Add,//���Z����
	Sub,//���Z����
	Mul,//��Z����
	Inv//�F���]
};

namespace DrawCommon
{
	/// <summary>
	/// �V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	/// </summary>
	/// <param name="shaderFileName">�t�@�C���̖��O</param>
	/// <param name="entrypointName">�G���g���[�|�C���g�̖��O</param>
	/// <param name="shaderModelName">�V�F�[�_�[���f���w��</param>
	/// <param name="blob">�V�F�[�_�I�u�W�F�N�g</param>
	/// <returns>�V�F�[�_�̓ǂݍ��݂ƃR���p�C���������V�F�[�_�I�u�W�F�N�g</returns>
	ID3DBlob* ShaderCompile(const wchar_t* shaderFileName,LPCSTR entrypointName, LPCSTR shaderModelName, ID3DBlob* blob);
}