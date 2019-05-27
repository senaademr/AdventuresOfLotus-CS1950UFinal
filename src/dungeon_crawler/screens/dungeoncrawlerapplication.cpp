#include "dungeoncrawlerapplication.h"

#include "dungeoncrawlerlandingscreen.h"
#include "engine/screens/pausescreen.h"
#include "engine/screens/blankscreen.h"
#include "test/astartest.h"
#include "engine/basics/typeid.h"

class TransformComponent;

DungeonCrawlerApplication::DungeonCrawlerApplication(View* view) :  Application(view)
{
    AStarTest test = AStarTest();
    test.runTests();
//    std::shared_ptr<Screen> game = std::make_shared<DungeonCrawlerScreen>(view);
//    this->setScreen(game);

//    std::shared_ptr<Screen> gameScreen = std::make_shared<DungeonCrawlerLandingScreen>(view, this);
//    this->pushScreen(gameScreen);

//    this->addScreen("menu", std::make_shared<DungeonCrawlerLandingScreen>(view, this));
//    this->addScreen("pause", std::make_shared<PauseScreen>(view, this, "game"));
//    this->setScreen("menu");
    //this->setScreen(std::make_shared<DungeonCrawlerLandingScreen>(view, this));

//    std::cout << "transform: " << TypeID::value<TransformComponent>()<< std::endl;
//    std::cout << "application: " << TypeID::value<Application>()<< std::endl;
//    std::cout << "transform: " << TypeID::value<TransformComponent>()<< std::endl;
}


