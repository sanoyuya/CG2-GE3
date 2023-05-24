#pragma once
#include"DrawOversight.h"
#include"myMath.h"

class EditorObject
{
private:

	Model* model = nullptr;
	Transform transform;

public:

	void Initialize();
	void Update(Camera* camera);
	void Draw();

	void SetModel(const uint32_t& tex);
	void SetPos(const myMath::Vector3& position);
	void SetRot(const myMath::Vector3& rotation);
	void SetScale(const myMath::Vector3& scale);
};