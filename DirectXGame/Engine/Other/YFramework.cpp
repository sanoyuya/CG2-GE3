#include "YFramework.h"
#include "MyGame.h"
#include"SceneFactory.h"
#include"SceneManager.h"
#include"imgui.h"
#include"LightManager.h"
#include"ParticleManager.h"

void YFramework::Initialize()
{
	windowsApp_ = std::make_unique<WindowsApp>();//WindowsAppクラス読み込み
	windowsApp_->CreatWindow(title_.c_str(), windowWidth_, windowHeight_);//ウィンドウ作成

	fps_ = std::make_unique<FPS>();
	fps_->Initialize();

	//DirectX初期化処理 ここから

	//DirectXBaseクラス読み込み
	DirectXBase::GetInstance()->Initialize(windowsApp_.get());

	//imGuiの初期化
	ImGuiManager::GetInstance()->Initialize(windowsApp_.get());

	//キー取得開始
	InputManager::GetInstance()->Initialize(windowsApp_.get());

	// オーディオの初期化
	AudioManager::GetInstance()->Initialize();

	//DirectX初期化処理 ここまで

	//描画初期化処理ここから

	Camera::StaticInitialize(windowsApp_.get());

	TextureManager::GetInstance()->StaticInitialize();

	SpriteCommon::StaticInitialize();
	Sprite2D::StaticInitialize(windowsApp_.get());

	Model::StaticInitialize();

	ParticleManager::StaticInitialize();

	LightManager::StaticInitialize(DirectXBase::GetInstance()->GetDevice().Get());

	//描画初期化処理ここまで

	windowsApp_->Appearance();

	//シーンファクトリーを生成し、マネージャにセット
	AbstractSceneFactory* sceneFactory = new SceneFactory();
	SceneManager::GetInstance()->SetSceneFactory(sceneFactory);
}

void YFramework::Destroy()
{
	ImGuiManager::GetInstance()->Destroy();
	Model::StaticDestory();
	DirectXBase::GetInstance()->Destroy();
	AudioManager::GetInstance()->Destroy();
}

void YFramework::Update()
{
	if (!windowsApp_->MessageWindow())
	{
		endRequest_ = true;
	}

	InputManager::GetInstance()->Update();
	AudioManager::GetInstance()->Update();

	DirectXBase::GetInstance()->SetClearColor();//背景色を設定 初期値(水色)
}

void YFramework::SetWindowData(const std::string& title, const float width, const float height)
{
	wchar_t wtitle[256];

	MultiByteToWideChar(CP_ACP, 0, title.c_str(), -1, wtitle, _countof(wtitle));

	title_ = wtitle;
	windowWidth_ = width;//横幅
	windowHeight_ = height;//縦幅
}

void YFramework::SetWindowColor(const myMath::Vector4& color)
{
	DirectXBase::GetInstance()->SetClearColor(color);
}

void YFramework::Run()
{
	//初期化処理
	Initialize();

	// ゲームループ
	while (true)
	{
		//更新処理
		ImGuiManager::GetInstance()->Begin();

		Update();

		SceneDraw();

		ImGuiManager::GetInstance()->End();

		DirectXBase::GetInstance()->PreDraw(windowsApp_.get());

		if (GetEndRequest())
		{
			break;
		}

		//描画処理
		PostEffectDraw();

#ifdef _DEBUG

		ImGuiManager::GetInstance()->Draw();

#endif _DEBUG

		DirectXBase::GetInstance()->PostDraw();

		//FPS制御
		fps_->Update();
	}
	Destroy();
}

void YFramework::SceneDraw()
{
}

void YFramework::PostEffectDraw()
{
}

bool& YFramework::GetEndRequest()
{
	return endRequest_;
}