#include "DrawOversight.h"

uint32_t DrawOversight::LoadTexture(const std::string& filePath)
{
	return TextureManager::GetInstance()->LoadTexture(filePath);
}