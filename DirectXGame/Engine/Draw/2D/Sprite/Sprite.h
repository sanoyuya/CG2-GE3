#pragma once
#include"TextureManager.h"
#include"Sprite2D.h"
#include"Sprite3D.h"

class Sprite:public Sprite2D, public Sprite3D
{
public:

	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	/// <param name="filePath">�t�@�C����</param>
	/// <returns></returns>
	uint32_t LoadTexture(const std::string& filePath);
};