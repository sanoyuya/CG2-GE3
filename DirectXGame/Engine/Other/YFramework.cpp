#include "YFramework.h"
#include "MyGame.h"
#include"SceneFactory.h"
#include"SceneManager.h"
#include"imgui.h"
#include"LightManager.h"

void YFramework::Initialize()
{
	windowsApp_ = std::make_unique<WindowsApp>();//WindowsAppクラス読み込み
	windowsApp_->CreatWindow(title_.c_str(), windowWidth_, windowHeight_);//ウィンドウ作成

	fps_ = std::make_unique<FPS>();
	fps_->Initialize();

	//DirectX初期化処理 ここから

	directX_ = DirectXBase::GetInstance();//DirectX_クラス読み込み
	directX_->Initialize(windowsApp_.get());

	//imGuiの初期化
	imGuiManager_ = ImGuiManager::GetInstance();
	imGuiManager_->Initialize(windowsApp_.get());

	//キー取得開始
	input_ = InputManager::GetInstance();
	input_->Initialize(windowsApp_.get());

	// オーディオの初期化
	audioManager_ = AudioManager::GetInstance();
	audioManager_->Initialize();

	//DirectX初期化処理 ここまで

	//描画初期化処理ここから

	Camera::StaticInitialize(windowsApp_.get());

	TextureManager::GetInstance()->StaticInitialize();

	SpriteCommon::Initialize();
	Sprite2D::StaticInitialize(windowsApp_.get());

	Model::StaticInitialize();

	LightManager::StaticInitialize(DirectXBase::GetInstance()->GetDevice().Get());

	//描画初期化処理ここまで

	windowsApp_->Appearance();

	//シーンファクトリーを生成し、マネージャにセット
	AbstractSceneFactory* sceneFactory = new SceneFactory();
	SceneManager::GetInstance()->SetSceneFactory(sceneFactory);

	postEffect_ = std::make_unique<PostEffect>();
	postEffect_->Initialize();
}

void YFramework::Destroy()
{
	imGuiManager_->Destroy();
	directX_->Destroy();
	audioManager_->Destroy();
}

void YFramework::Update()
{
	if (!windowsApp_->MessageWindow())
	{
		endRequest_ = true;
	}

	input_->Update();
	audioManager_->Update();

	directX_->SetClearColor();//背景色を設定 初期値(水色)
	directX_->UpdateClear(windowsApp_.get());
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
		imGuiManager_->Begin();

		Update();

		imGuiManager_->End();

		if (GetEndRequest())
		{
			break;
		}

		//描画処理
		Draw();
		postEffect_->Draw();

#ifdef _DEBUG

		

#endif // DEBUG

		imGuiManager_->Draw();//ALの評価課題出すまではこっち

		directX_->UpdateEnd();

		//FPS制御
		fps_->Update();
	}
	Destroy();
}

void YFramework::Draw()
{
}

bool& YFramework::GetEndRequest()
{
	return endRequest_;
}