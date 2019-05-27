#ifndef UNPAUSECOMPONENT_H
#define UNPAUSECOMPONENT_H

#include "component.h"
#include "tickable.h"

class Application;
class PauseScreen;
class Input;

class UnpauseComponent : public Component, public Tickable
{
public:
    UnpauseComponent(PauseScreen* pauseScreen);

    // Tickable interface
public:
    void tick(float seconds);

private:
    PauseScreen* m_pauseScreen;
    std::shared_ptr<Input> m_input;
};

#endif // UNPAUSECOMPONENT_H
