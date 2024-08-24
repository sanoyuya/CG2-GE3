#pragma once
#include"DrawOversight.h"
#include"InputManager.h"

class Player
{
private:

	InputManager* input_ = nullptr;

	int8_t nowNum_ = 0;
	//横
	int8_t heightNum_ = 0;
	//縦
	int8_t widthNum_ = 0;
	const int8_t cMinNum_ = 0;
	const int8_t cMaxNum_ = 2;

public:

	void Initialize();

	void Update();

	void Draw();

private:

	void BoardSelect();
};