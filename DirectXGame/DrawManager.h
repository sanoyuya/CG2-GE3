#pragma once
#include"TextureManager.h"
#include"Sprite.h"

class DrawManager:public Sprite
{
public:

	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	/// <param name="filePath">�t�@�C����</param>
	/// <returns></returns>
	TextureData LoadTexture(const std::string& filePath);
};