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

	//�Q�b�^�[
	const bool& GetAnimationFlag();
	const float& GetAnimationTimer();

	//�Z�b�^�[
	void SetAnimationFlag(const bool animationFlag);

	//�V���O���g��
	static SceneChangeAnimation* GetInstance();

private:

	SceneChangeAnimation() = default;
	~SceneChangeAnimation() = default;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	SceneChangeAnimation& operator=(const SceneChangeAnimation&) = delete;
	SceneChangeAnimation(const SceneChangeAnimation&) = delete;
};