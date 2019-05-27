#include "finalapplication.h"

#include "engine/screens/pausescreen.h"
#include "engine/screens/blankscreen.h"

#include "menuscreen.h"
#include "mainscreen.h"
#include "gameoverscreen.h"

#include "engine/components/transformcomponent.h"
#include "engine/basics/typeid.h"

#include "test/navmeshtest.h"

class TransformComponent;

FinalApplication::FinalApplication(View* view) :  Application(view)
{
//    AStarTest test = AStarTest();
//    test.runTests();
//    NavmeshTest test = NavmeshTest();
//    test.runTests();

    std::shared_ptr<Screen> menuScreen = std::make_shared<MenuScreen>(view, this);
    std::shared_ptr<Screen> gameScreen = std::make_shared<MainScreen>(view, this);
    std::shared_ptr<Screen> gameOverScreen = std::make_shared<GameOverScreen>(view, this);
    this->addScreen("game", gameScreen);
    this->addScreen("menu", menuScreen);
    this->addScreen("gameOver", gameOverScreen);
    this->setScreen("menu");
}

