#include "SceneFactory.h"
#include "EngineOP.h"
#include"DemoScene.h"

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

    return std::unique_ptr<BaseScene>(newScene);
}