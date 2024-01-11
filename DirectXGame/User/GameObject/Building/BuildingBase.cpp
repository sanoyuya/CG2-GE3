#include "BuildingBase.h"
uint32_t BuildingBase::sBuildingTex_;

void BuildingBase::LoadAsset()
{
	sBuildingTex_ = Model::CreateObjModel("Resources/building3");
}