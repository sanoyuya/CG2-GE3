#include "SceneFactory.h"
#include"TitleScene.h"
#include"GameScene.h"
#include "EngineOP.h"

BaseScene* SceneFactory::CreateScene(const std::string& sceneName)
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

    return newScene;
}