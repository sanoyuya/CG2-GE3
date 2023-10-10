#pragma once
#include"ParticleManager.h"

class ParticleBase
{
public:

	/// <summary>
	/// 基底クラスのデストラクタ
	/// </summary>
	virtual ~ParticleBase() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Initialize() = 0;

	/// <summary>
	/// 生成処理
	/// </summary>
	/// <param name="center">中心座標</param>
	virtual void Create(const myMath::Vector3 center) = 0;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="camera">カメラのポインタ</param>
	virtual void Update(Camera* camera) = 0;

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() = 0;
};