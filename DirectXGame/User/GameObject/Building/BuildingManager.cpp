#include "BuildingManager.h"
#include"ColliderManager.h"

BuildingManager::BuildingManager()
{
}

BuildingManager::~BuildingManager()
{
}

void BuildingManager::Initialize(BuildingList& buildingData)
{
	//jsonファイルから読み込む
	Load(buildingData);

	for (std::unique_ptr<BuildingBase>& building : buildings_)
	{
		building->Initialize();
		//ColliderManager::GetInstance()->AddCollision(building.get());
	}
}

void BuildingManager::Update()
{
	for (const std::unique_ptr<BuildingBase>& building : buildings_)
	{
		building->Update();
	}
}

void BuildingManager::Draw()
{
	for (const std::unique_ptr<BuildingBase>& building : buildings_)
	{
		building->Draw();
	}
}

void BuildingManager::Load(BuildingList& buildingData)
{
	std::swap(buildings_, buildingData.buildings);
}

void BuildingManager::ReLoad(BuildingList& buildingData)
{
	Reset();
	Initialize(buildingData);
}

void BuildingManager::Reset()
{
	buildings_.clear();
}

const std::list<std::unique_ptr<BuildingBase>>& BuildingManager::GetBuildingList()
{
	return buildings_;
}