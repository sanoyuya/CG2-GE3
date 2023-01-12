#pragma once
#include"myMath.h"
#include"DrawOversight.h"

class SceneChangeAnimation
{
private:

	bool animationFlag = false;
	float animationTimer = 0.0f;

	std::unique_ptr<Sprite>animationSprite;
	uint32_t animationTex = 0;

	float alpha = 0.0f;

public:

	void Initialize();
	void Update();
	void Draw();

	//ゲッター
	const bool& GetAnimationFlag();
	const float& GetAnimationTimer();

	//セッター
	void SetAnimationFlag(const bool animationFlag);

	//シングルトン
	static SceneChangeAnimation* GetInstance();

private:

	SceneChangeAnimation() = default;
	~SceneChangeAnimation() = default;

	//コピーコンストラクタ・代入演算子削除
	SceneChangeAnimation& operator=(const SceneChangeAnimation&) = delete;
	SceneChangeAnimation(const SceneChangeAnimation&) = delete;
};