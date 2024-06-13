#include "SceneFactory.h"
#include "EngineOP.h"
#include"DemoScene.h"
#include"TitleScene.h"
#include"GameScene.h"

std::unique_ptr<BaseScene> SceneFactory::CreateScene(const std::string& sceneName)
{
    //次のシーンを生成
    BaseScene* newScene = nullptr;

    if (sceneName == "EngineOP")
    {
        newScene = new EngineOP();
    }
    else if (sceneName == "DEMO")
    {
        newScene = new DemoScene();
    }
    else if (sceneName == "TITLE")
    {
        newScene = new TitleScene();
    }
    else if (sceneName == "GAME")
    {
        newScene = new GameScene();
    }

    return std::unique_ptr<BaseScene>(newScene);
}