#pragma once
#include"TextureManager.h"
#include"Sprite.h"
#include"Model.h"

class DrawOversight :public Sprite, public Model
{
public:

	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	/// <param name="filePath">ファイル名</param>
	/// <returns></returns>
	uint32_t LoadTexture(const std::string& filePath);
};