#pragma once
#include"TextureManager.h"
#include"Sprite.h"

class DrawManager:public Sprite
{
public:
	TextureData LoadTexture(const std::string& filePath);
};