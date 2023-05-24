#pragma once
#include"DrawOversight.h"
#include"myMath.h"

class EditorObject
{
private:

	Model* model = nullptr;
	Transform transform;
	std::string objectName;

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

	void SetModel(const uint32_t& tex);
	void SetPos(const myMath::Vector3& position);
	void SetRot(const myMath::Vector3& rotation);
	void SetScale(const myMath::Vector3& scale);
	void SetName(const std::string& name);
};