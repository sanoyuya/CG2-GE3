#include "PlayerDeathAnimation.h"
#include"MultiTexturePostEffect.h"

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
		MultiTexturePostEffect::SetEffectMode(MultiTextureEffectMode::GrayScale);
		animationFlag_ = true;
	}
	else
	{
		deathAnimationTimer++;
		MultiTexturePostEffect::SetGrayScale(deathAnimationTimer / maxDeathAnimationTimer_);
		if (deathAnimationTimer >= maxDeathAnimationTimer_)
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
		//死亡演出の描画
		deathParticleEmitter_->Draw();
	}
}

const bool PlayerDeathAnimation::GetDeathFlag()
{
	return deathFlag_;
}