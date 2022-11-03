#pragma once
#include"TextureManager.h"
#include"Sprite.h"

class DrawManager:public Sprite
{
public:

	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	/// <param name="filePath">ファイル名</param>
	/// <returns></returns>
	TextureData LoadTexture(const std::string& filePath);
};