#include "SceneFactory.h"
#include"TitleScene.h"
#include"GameScene.h"
#include "EngineOP.h"
#include"ResultScene.h"

std::unique_ptr<BaseScene> SceneFactory::CreateScene(const std::string& sceneName)
{
    //éüÇÃÉVÅ[ÉìÇê∂ê¨
    BaseScene* newScene = nullptr;

    if (sceneName == "TITLE")
    {
        newScene = new TitleScene();
    }
    else if (sceneName == "GAME")
    {
        newScene = new GameScene();
    }
    else if (sceneName == "EngineOP")
    {
        newScene = new EngineOP();
    }
    else if (sceneName == "RESULT")
    {
        newScene = new ResultScene();
    }

    return std::unique_ptr<BaseScene>(newScene);
}