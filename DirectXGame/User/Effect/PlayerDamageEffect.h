#pragma once
#include"Player.h"

class PlayerDamageEffect
{
private:

	float power_ = 0.0f;
	bool damageFlag_ = false;

	const float maxPower_ = 10.0f;
	const float minPower_ = 0.0f;
	const float subPower_ = 0.125f;

public:

	PlayerDamageEffect();
	~PlayerDamageEffect();

	void Update(Player* player);
};