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

	//�V���O���g��
	static SceneChangeAnimation* GetInstance();

private:

	SceneChangeAnimation() = default;
	~SceneChangeAnimation() = default;

	void Reset();

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	SceneChangeAnimation& operator=(const SceneChangeAnimation&) = delete;
	SceneChangeAnimation(const SceneChangeAnimation&) = delete;
};