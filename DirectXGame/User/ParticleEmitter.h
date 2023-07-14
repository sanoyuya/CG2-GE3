#pragma once
#include"ParticleManager.h"

class ParticleEmitter
{
private:

	std::unique_ptr<ParticleManager>particleMan_;
	uint32_t tex_;

public:

	void Initialize();
	void Create(const myMath::Vector3 center);
	void Update(Camera* camera);
	void Draw();
};