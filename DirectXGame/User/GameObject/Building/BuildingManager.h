#pragma once
#include<list>
#include"Building.h"

struct BuildingList
{
	std::list<std::unique_ptr<BuildingBase>>buildings;
};

class BuildingManager
{
private:

	std::list<std::unique_ptr<BuildingBase>>buildings_;

public:

	BuildingManager();
	~BuildingManager();

	void Initialize(BuildingList& buildingData);

	void Update();

	void Draw();

	void Load(BuildingList& buildingData);

	void ReLoad(BuildingList& buildingData);

	void Reset();

	const std::list<std::unique_ptr<BuildingBase>>& GetBuildingList();
};