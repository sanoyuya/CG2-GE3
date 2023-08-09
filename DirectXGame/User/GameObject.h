#pragma once
#include"Camera.h"

//オブジェクト基底クラス
class GameObject
{
public:

	virtual ~GameObject() = default;

	//初期化処理
	virtual void Initialize() = 0;

	//更新処理
	virtual void Update() = 0;

	//描画処理
	virtual void Draw() = 0;

	//オブジェクトの名前取得処理
	virtual std::string GetName() = 0;
};