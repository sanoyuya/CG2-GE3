#include "EditorObject.h"

EditorObject::~EditorObject()
{
}

void EditorObject::Initialize()
{
	model_ = std::make_unique<Model>();
	transform_.Initialize();
}

void EditorObject::Update(Camera* camera)
{
	transform_.TransUpdate(camera);
}

void EditorObject::Draw()
{
	model_->DrawModel(&transform_, color_, tiling_);
}

const myMath::Vector3& EditorObject::GetPos()
{
	return transform_.translation;
}

const myMath::Vector3& EditorObject::GetRot()
{
	return transform_.rotation;
}

const myMath::Vector3& EditorObject::GetScale()
{
	return transform_.scale;
}

const std::string& EditorObject::GetName()
{
	return objectName_;
}

const myMath::Vector3& EditorObject::GetColliderCenter()
{
	return colliderCenter_;
}

const myMath::Vector3& EditorObject::GetColliderSize()
{
	return colliderSize_;
}

void EditorObject::SetModel(const uint32_t& tex)
{
	model_->SetModel(tex);
}

void EditorObject::SetPos(const myMath::Vector3& position)
{
	transform_.translation = position;
}

void EditorObject::SetRot(const myMath::Vector3& rotation)
{
	transform_.rotation = rotation;
}

void EditorObject::SetScale(const myMath::Vector3& scale)
{
	transform_.scale = scale;
}

void EditorObject::SetColor(const myMath::Vector4& color)
{
	color_ = color;
}

void EditorObject::SetName(const std::string& name)
{
	objectName_ = name;
}

void EditorObject::SetColliderCenter(const myMath::Vector3& colliderCenter)
{
	colliderCenter_ = colliderCenter;
}

void EditorObject::SetColliderSize(const myMath::Vector3& colliderSize)
{
	colliderSize_ = colliderSize;
}

void EditorObject::SetShader(const ShaderMode& mode)
{
	model_->SetShaderMode(mode);
}

void EditorObject::SetTiling(const myMath::Vector2 tiling)
{
	tiling_ = tiling;
}