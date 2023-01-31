#pragma once
#include"myMath.h"
#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")
#include<string>

struct PosUvColor
{
	myMath::Vector3 pos;//���W
	myMath::Vector2 uv;//uv���W
	myMath::Vector4 color;//�F
};

struct PosNormalUv
{
	myMath::Vector3 pos;//���W
	myMath::Vector3 normal;//�@��
	myMath::Vector2 uv;//uv���W
};

//�}�e���A���悤�萔�o�b�t�@�\����
struct ConstBuffDataMaterial
{
	//�A���r�G���g�W��
	myMath::Vector3 ambient;
	//�p�f�B���O
	float pad1;
	//�f�B�t���[�Y�W��
	myMath::Vector3 diffuse;
	//�p�f�B���O
	float pad2;
	//�X�y�L�����[�W��
	myMath::Vector3 specular;
	//�A���t�@
	float alpha;
};

//�}�e���A��
struct ModelMaterial
{
	//�}�e���A����
	std::string name;
	//�A���r�G���g�e���x
	myMath::Vector3 ambient = { 0.06f, 0.06f, 0.06f };
	//�f�B�t���[�Y�e���x
	myMath::Vector3 diffuse = { 0.0f,0.0f,0.0f };
	//�X�y�L�����[�e���x
	myMath::Vector3 specular = { 0.0f,0.0f,0.0f };

	float shininess = 1.0f;
	//�A���t�@
	float alpha = 1.0f;
	//�e�N�X�`���t�@�C����
	std::string textureFiename;

	ConstBuffDataMaterial GetConstBuffMaterial();
};

struct worldViewpojCamera
{
	//���[���h�s��
	myMath::Matrix4 world;
	//���[���h���W
	myMath::Matrix4 matWorld;
	//�J�������W(���[���h���W)
	myMath::Vector3 cameraPos;
};

class DrawCommon
{
public:
	static ID3DBlob* ShaderCompile(const wchar_t* shaderFileName, LPCSTR entrypointName, LPCSTR shaderModelName, ID3DBlob* blob);
};