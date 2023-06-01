#pragma once
#include"DrawOversight.h"
#include"myMath.h"

class EditorObject
{
private:

	std::unique_ptr<Model> model;
	Transform transform;
	std::string objectName;
	myMath::Vector3 colliderCenter = { 0.0f,0.0f ,0.0f };
	myMath::Vector3 colliderSize = { 0.0f,0.0f ,0.0f };

public:

	EditorObject() = default;
	~EditorObject();

	void Initialize();
	void Update(Camera* camera);
	void Draw();

	const myMath::Vector3& GetPos();
	const myMath::Vector3& GetRot();
	const myMath::Vector3& GetScale();
	const std::string& GetName();
	const myMath::Vector3& GetColliderCenter();
	const myMath::Vector3& GetColliderSize();

	void SetModel(const uint32_t& tex);
	void SetPos(const myMath::Vector3& position);
	void SetRot(const myMath::Vector3& rotation);
	void SetScale(const myMath::Vector3& scale);
	void SetName(const std::string& name);
	void SetColliderCenter(const myMath::Vector3& colliderCenter_);
	void SetColliderSize(const myMath::Vector3& colliderSize_);
};