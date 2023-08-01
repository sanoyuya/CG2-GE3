#pragma once
#include"EnemyDeathParticleEmitter.h"
#include"Camera.h"

class PlayerDeathAnimation
{
private:

	std::unique_ptr<EnemyDeathParticleEmitter>deathParticleEmitter_;
	Transform deathParticleEmitterTrans_;

	bool deathFlag_ = false;
	bool animationFlag_ = false;
	float deathAnimationTimer = 0.0f;

public:

	PlayerDeathAnimation() = default;
	~PlayerDeathAnimation() = default;

	void Initialize();

	void Update(const myMath::Vector3 position);

	void ParticleUpdate(Camera* camera);

	void Draw();

	const bool GetDeathFlag();
};

