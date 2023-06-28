#include "GameScene.h"
#include"SceneManager.h"
#include"PhysicsMath.h"
#include<imgui.h>

void GameScene::Initialize()
{
	input_ = InputManager::GetInstance();
	audioManager_ = AudioManager::GetInstance();

	camera_ = std::make_unique<Camera>();
	camera_->Initialize(true);
	cameraPos_ = { 0.0f,0.0f,-10.0f };

	lightManager_.reset(lightManager_->Create());
	Model::SetLight(lightManager_.get());
	lightPos_ = { 0.0f,0.0f,-2.0f };
	lightColor_ = { 1.0f,1.0f ,1.0f };
	lightAtten_ = { 0.3f,0.1f,0.1f };

	//�V��
	model_ = std::make_unique<Model>();
	//model->SetModelBlendMode(BlendMode::Sub);
	modelTex_ = Model::CreateObjModel("Resources/skydome");
	model_->SetModel(modelTex_);
	modelTrans_.Initialize();

	sphereTex_ = Model::CreateObjModel("Resources/sphere", true);
	sphere2Tex_ = Model::CreateObjModel("Resources/sphere2",true);
	
	//���̋�
	sphere_ = std::make_unique<Model>();
	sphere_->SetShaderMode(ShaderMode::Phong);
	sphere_->SetModel(sphereTex_);
	sphereTrans_.Initialize();
	sphereTrans_.translation = { -3.0f ,-3.0f,0.0f };

	//�^�񒆂̋�
	sphere2_ = std::make_unique<Model>();
	sphere2_->SetShaderMode(ShaderMode::Toon);
	sphere2_->SetModel(sphereTex_);
	sphere2Trans_.Initialize();
	sphere2Trans_.translation = { 0.0f ,-3.0f,0.0f };

	//�E�̋�
	sphere3_ = std::make_unique<Model>();
	sphere3_->SetShaderMode(ShaderMode::SimpleColor);
	sphere3_->SetModel(sphereTex_);
	sphere3Trans_.Initialize();
	sphere3Trans_.translation = { 3.0f ,-3.0f,0.0f };

	lightSphere_ = std::make_unique<Model>();
	lightSphere_->SetModel(sphereTex_);
	lightSphereTrans_.Initialize();
	lightSphereTrans_.scale.x = 0.25f;
	lightSphereTrans_.scale.y = 0.25f;
	lightSphereTrans_.scale.z = 0.25f;

	assimpModelTex_ = Model::CreateAssimpModel("gltfBox");
	assimpModel_= std::make_unique<Model>();
	assimpModel_->SetModel(assimpModelTex_);
	assimpModelTrans_.Initialize();
}

void GameScene::Destroy()
{
}

void GameScene::Update()
{
	if (input_->KeyboardTriggerPush(DIK_SPACE))
	{
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}

	ImGuiUpdate();

	assimpModel_->SetShaderMode(shaderMode_);

	PostEffect::SetEffectMode(mode_);

	PostEffect::SetPower(blurPower);

	CamMove();
	Rotation();

	lightManager_->Update();

	//�|�C���g���C�g
	lightManager_->SetPointLightActive(0, true);
	lightManager_->SetPointLightPos(0, lightPos_);
	lightManager_->SetPointLightColor(0, lightColor_);
	lightManager_->SetPointLightAtten(0, lightAtten_);

	modelTrans_.TransUpdate(camera_.get());//�V��
	sphereTrans_.TransUpdate(camera_.get());//��
	sphere2Trans_.TransUpdate(camera_.get());
	sphere3Trans_.TransUpdate(camera_.get());
	lightSphereTrans_.translation = lightPos_;
	lightSphereTrans_.TransUpdate(camera_.get());
	assimpModelTrans_.TransUpdate(camera_.get());
}

void GameScene::Draw()
{
	model_->DrawModel(&modelTrans_);
	sphere_->DrawModel(&sphereTrans_, color_);
	sphere2_->DrawModel(&sphere2Trans_, color_);
	sphere3_->DrawModel(&sphere3Trans_, color_);
	if (lightDisplayFlag_)
	{
		lightSphere_->DrawModel(&lightSphereTrans_, { lightColor_.x,lightColor_.y,lightColor_.z,0.5f });
	}
	assimpModel_->DrawModel(&assimpModelTrans_,color_);
}

void GameScene::Rotation()
{
	sphereTrans_.rotation.y -= 0.02f;
	sphere2Trans_.rotation.y -= 0.02f;
	sphere3Trans_.rotation.y -= 0.02f;
}

void GameScene::CamMove()
{
	if (input_->KeyboardKeepPush(DIK_UP))
	{
		cameraPos_.y += 0.05f;
	}
	if (input_->KeyboardKeepPush(DIK_DOWN))
	{
		cameraPos_.y -= 0.05f;
	}
	if (input_->KeyboardKeepPush(DIK_RIGHT))
	{
		cameraPos_.x += 0.05f;
	}
	if (input_->KeyboardKeepPush(DIK_LEFT))
	{
		cameraPos_.x -= 0.05f;
	}

	camera_->SetEye(cameraPos_);
	camera_->SetTarget({ 0.0f,0.0f ,0.0f });
	camera_->Update(true);
}

void GameScene::ImGuiUpdate()
{
	//��
	ImGui::Begin("model");
	ImGui::ColorEdit4("color", &color_.x);
	int shaderMode = static_cast<int>(shaderMode_);
	ImGui::SliderInt("shaderMode", &shaderMode, 0, 5);
	shaderMode_ = static_cast<ShaderMode>(shaderMode);
	if(ImGui::Button("texFlag"))
	{
		if (texFlag_ == false)
		{
			sphere_->SetModel(sphereTex_);
			sphere2_->SetModel(sphereTex_);
			sphere3_->SetModel(sphereTex_);
			texFlag_ = true;
		}
		else
		{
			sphere_->SetModel(sphere2Tex_);
			sphere2_->SetModel(sphere2Tex_);
			sphere3_->SetModel(sphere2Tex_);
			texFlag_ = false;
		}
	}
	ImGui::End();

	//���C�g
	ImGui::Begin("light");
	ImGui::SliderFloat3("position", &lightPos_.x, -10.0f, 10.0f);
	ImGui::ColorEdit3("color", &lightColor_.x);
	ImGui::SliderFloat3("atten", &lightAtten_.x, 0.0f, 1.0f);
	if (ImGui::Button("lightDisplayFlag"))
	{
		if (lightDisplayFlag_ == false)
		{
			lightDisplayFlag_ = true;
		}
		else
		{
			lightDisplayFlag_ = false;
		}
	}
	ImGui::End();

	int mode = static_cast<int>(mode_);
	ImGui::Begin("postEffect");
	ImGui::SliderInt("effectMode", &mode, 0, 8);
	ImGui::SliderFloat("blurPower", &blurPower, 0.0f, 10.0f);
	ImGui::End();
	mode_= static_cast<EffectMode>(mode);
}