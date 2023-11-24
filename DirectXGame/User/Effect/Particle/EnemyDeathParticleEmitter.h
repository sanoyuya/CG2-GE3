#pragma once
#include"ParticleBase.h"

class EnemyDeathParticleEmitter:public ParticleBase
{
private:

	std::unique_ptr<ParticleManager>particleMan_;
	uint32_t tex_;

	const float startScale_ = 3.0f;
	const float endScale_ = 10.0f;

public:

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyDeathParticleEmitter() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 生成処理
	/// </summary>
	/// <param name="center">中心座標</param>
	void Create(const myMath::Vector3 center);

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="camera">カメラのポインタ</param>
	void Update(Camera* camera);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();
};