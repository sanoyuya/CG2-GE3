#pragma once
#include"TextureManager.h"
#include"Sprite2D.h"
#include"Sprite3D.h"

class Sprite:public Sprite2D, public Sprite3D
{
public:

	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	/// <param name="filePath">ファイル名</param>
	/// <returns></returns>
	uint32_t LoadTexture(const std::string& filePath);
};