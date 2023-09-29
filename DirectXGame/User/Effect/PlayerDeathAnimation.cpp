#include "PlayerDeathAnimation.h"
#include"PostEffect.h"

void PlayerDeathAnimation::Initialize()
{
	deathParticleEmitter_ = std::make_unique<EnemyDeathParticleEmitter>();
	deathParticleEmitter_->Initialize();
	deathParticleEmitterTrans_.Initialize();
}

void PlayerDeathAnimation::Update(const myMath::Vector3 position)
{
	if (animationFlag_ == false)
	{
		deathParticleEmitter_->Create(position);
		PostEffect::SetEffectMode(EffectMode::GrayScale);
		animationFlag_ = true;
	}
	else
	{
		deathAnimationTimer++;
		PostEffect::SetGrayScale(deathAnimationTimer / 60);
		if (deathAnimationTimer >= 60.0f)
		{
			deathFlag_ = true;
		}
	}
}

void PlayerDeathAnimation::ParticleUpdate(Camera* camera)
{
	if (animationFlag_ == true)
	{
		deathParticleEmitter_->Update(camera);
	}
}

void PlayerDeathAnimation::Draw()
{
	if (animationFlag_ == true)
	{
		//Ž€–S‰‰o‚Ì•`‰æ
		deathParticleEmitter_->Draw();
	}
}

const bool PlayerDeathAnimation::GetDeathFlag()
{
	return deathFlag_;
}