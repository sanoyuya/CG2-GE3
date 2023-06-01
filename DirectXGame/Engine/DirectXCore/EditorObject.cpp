#include "EditorObject.h"

EditorObject::~EditorObject()
{
}

void EditorObject::Initialize()
{
	model = std::make_unique<Model>();
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

const myMath::Vector3& EditorObject::GetPos()
{
	return transform.translation;
}

const myMath::Vector3& EditorObject::GetRot()
{
	return transform.rotation;
}

const myMath::Vector3& EditorObject::GetScale()
{
	return transform.scale;
}

const std::string& EditorObject::GetName()
{
	return objectName;
}

const myMath::Vector3& EditorObject::GetColliderCenter()
{
	return colliderCenter;
}

const myMath::Vector3& EditorObject::GetColliderSize()
{
	return colliderSize;
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

void EditorObject::SetName(const std::string& name)
{
	objectName = name;
}

void EditorObject::SetColliderCenter(const myMath::Vector3& colliderCenter_)
{
	colliderCenter = colliderCenter_;
}

void EditorObject::SetColliderSize(const myMath::Vector3& colliderSize_)
{
	colliderSize = colliderSize_;
}