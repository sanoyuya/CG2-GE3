#pragma once
#include"Player.h"

class PlayerDamageEffect
{
private:

	float power_ = 0.0f;
	bool damageFlag_ = false;

public:

	PlayerDamageEffect();
	~PlayerDamageEffect();

	void Update(Player* player);
};