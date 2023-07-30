#pragma once
#include"DrawOversight.h"

class SceneChangeAnimation
{
private:

	bool animationFlag_ = false;
	uint8_t animationTimer_ = 0;
	const uint8_t maxAnimationTime = 180;

	std::unique_ptr<Sprite>back_;
	uint32_t backTex_ = 0;

	float alpha_ = 0.0f;

public:

	void StaticInitialize();

	void Update();

	void Change(const std::string& sceneName);

	void ChangeAfter();

	void Draw();

	void SetAnimationFlag(bool flag);

	//シングルトン
	static SceneChangeAnimation* GetInstance();

private:

	SceneChangeAnimation() = default;
	~SceneChangeAnimation() = default;

	void Reset();

	//コピーコンストラクタ・代入演算子削除
	SceneChangeAnimation& operator=(const SceneChangeAnimation&) = delete;
	SceneChangeAnimation(const SceneChangeAnimation&) = delete;
};