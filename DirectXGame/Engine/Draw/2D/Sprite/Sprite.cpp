#include "Sprite.h"

uint32_t Sprite::LoadTexture(const std::string& filePath)
{
	return TextureManager::GetInstance()->LoadTexture(filePath);
}