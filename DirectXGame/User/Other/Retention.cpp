#include "Retention.h"

void Retention::SetStageNum(const uint16_t stageNum)
{
	stageNum_ = stageNum;
}

const uint16_t Retention::GetStageNum()
{
	return stageNum_;
}

Retention* Retention::GetInstance()
{
	static Retention instance;
	return &instance;
}