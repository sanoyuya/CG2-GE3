#pragma once

#include"BaseScene.h"

#include<string>

/// <summary>
/// ƒV[ƒ“Hê(ŠT”O)
/// </summary>
class AbstractSceneFactory
{
public:

	virtual ~AbstractSceneFactory() = default;

	//ƒV[ƒ“¶¬
	virtual BaseScene* CreateScene(const std::string& sceneName) = 0;
};