#include "DrawManager.h"

TextureData DrawManager::LoadTexture(const std::string& filePath)
{
	return TextureManager::GetInstance()->LoadTexture(filePath);
}