#include "Retention.h"

void Retention::SetStageNum(const Stage stageNum)
{
	stageNum_ = stageNum;
}

const Stage Retention::GetStageNum()
{
	return stageNum_;
}

Retention* Retention::GetInstance()
{
	static Retention instance;
	return &instance;
}