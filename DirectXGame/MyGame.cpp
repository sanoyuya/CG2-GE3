#include "MyGame.h"
#include"TitleScene.h"
#include"SceneFactory.h"

bool MyGame::endRequest;

void MyGame::Initialize()
{
	//基底クラスの初期化処理
	YFramework::Initialize();

	windowsApp = WindowsApp::GetInstance();//WindowsAppクラス読み込み
	windowsApp->CreatWindow(L"DirectXGame");//ウィンドウ作成

	fps = std::make_unique<FPS>();
	fps->Initialize();

	//DirectX初期化処理 ここから

	directX = DirectX_::GetInstance();//DirectX_クラス読み込み
	directX->Initialize();

	//キー取得開始
	input = InputManager::GetInstance();
	input->Initialize();

	// オーディオの初期化
	audioManager = AudioManager::GetInstance();
	audioManager->Initialize();

	//DirectX初期化処理 ここまで

	//描画初期化処理ここから

	textureManager = TextureManager::GetInstance();
	textureManager->StaticInitialize();

	SpriteCommon::Initialize();
	Sprite2D::StaticInitialize();

	Model::StaticInitialize();

	//描画初期化処理ここまで
	
	sceneManager = SceneManager::GetInstance();
	sceneManager->Initialize();
	//最初のシーンを生成
	BaseScene* titleScene = new TitleScene();
	//シーンマネージャーに最初のシーンをセット
	sceneManager->SetNextScene(titleScene);
}

void MyGame::Destroy()
{
	windowsApp->Break();
	directX->Destroy();
	textureManager->Destroy();
	audioManager->Destroy();

	//基底クラスの終了処理
	YFramework::Destroy();
}

void MyGame::Update()
{
	//基底クラスの更新処理
	YFramework::Update();

	if (!windowsApp->MessageWindow())
	{
		endRequest = true;
	}

	input->Update();
	audioManager->Update();

	directX->SetClearColor();//背景色を設定 初期値(水色)
	directX->UpdateClear();
}

void MyGame::Draw()
{
	sceneManager->Draw();

	directX->UpdateEnd();

	//FPS制御
	fps->Update();
}

const bool& MyGame::GetEndRequest()
{
	return endRequest;
}