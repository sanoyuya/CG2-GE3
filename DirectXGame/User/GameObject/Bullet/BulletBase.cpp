#include "BulletBase.h"
std::unique_ptr<PlayerEngineSmokeParticleEmitter>BulletBase::smokeEmitter_;

void BulletBase::LoadAsset()
{
	smokeEmitter_ = std::make_unique<PlayerEngineSmokeParticleEmitter>();
	smokeEmitter_->Initialize();
}

void BulletBase::EmitterUpdate(Camera* camera)
{
	smokeEmitter_->Update(camera);
}

void BulletBase::EmitterDraw()
{
	smokeEmitter_->Draw();
}