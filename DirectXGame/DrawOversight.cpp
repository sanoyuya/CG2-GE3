#include "DrawOversight.h"

TextureData DrawOversight::LoadTexture(const std::string& filePath)
{
	return TextureManager::GetInstance()->LoadTexture(filePath);
}