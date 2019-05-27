#ifndef DEATHCOMPONENT_H
#define DEATHCOMPONENT_H

#include "engine/components/component.h"
class Application;

class DeathComponent : public Component
{
public:
    DeathComponent(Application* app);
    void callGameOver();

private:
    Application* m_application;
};

#endif // DEATHCOMPONENT_H
