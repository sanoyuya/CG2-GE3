#include "BuildingBase.h"
uint32_t BuildingBase::sBuildingTex_;
uint32_t BuildingBase::sCubeTex_;

void BuildingBase::LoadAsset()
{
	sBuildingTex_ = Model::CreateObjModel("Resources/building2");
	sCubeTex_ = Model::CreateObjModel("Resources/cube");
}