#pragma once
#include"TextureManager.h"
#include"Sprite.h"
#include"Model.h"

class DrawOversight :public Sprite, public Model
{
public:

	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	/// <param name="filePath">�t�@�C����</param>
	/// <returns></returns>
	uint32_t LoadTexture(const std::string& filePath);
};