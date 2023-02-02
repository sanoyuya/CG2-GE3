#include "SceneFactory.h"
#include"TitleScene.h"
#include"GameScene.h"
#include"Scene3.h"
#include"Scene4.h"
#include"Scene5.h"

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
    else if (sceneName == "SCENE3")
    {
        newScene = new Scene3();
    }
    else if (sceneName == "SCENE4")
    {
        newScene = new Scene4();
    }
    else if (sceneName == "SCENE5")
    {
        newScene = new Scene5();
    }

    return newScene;
}