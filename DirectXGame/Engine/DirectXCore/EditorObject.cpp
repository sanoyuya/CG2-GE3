#include "EditorObject.h"

void EditorObject::Initialize()
{
	model = new Model;
	transform.Initialize();
}

void EditorObject::Update(Camera* camera)
{
	transform.TransUpdate(camera);
}

void EditorObject::Draw()
{
	model->DrawModel(&transform);
}

void EditorObject::SetModel(const uint32_t& tex)
{
	model->SetModel(tex);
}

void EditorObject::SetPos(const myMath::Vector3& position)
{
	transform.translation = position;
}

void EditorObject::SetRot(const myMath::Vector3& rotation)
{
	transform.rotation = rotation;
}

void EditorObject::SetScale(const myMath::Vector3& scale)
{
	transform.scale = scale;
}