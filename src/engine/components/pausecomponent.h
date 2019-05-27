#ifndef PAUSECOMPONENT_H
#define PAUSECOMPONENT_H

#include "component.h"
#include "tickable.h"

class Application;
class Input;
class Screen;
class View;

class PauseComponent : public Component, public Tickable
{
public:
    PauseComponent(View* view);
    static std::shared_ptr<GameObject> getPauseObject(View *view);

    // Tickable interface
public:
    void tick(float seconds);

private:
    View* m_view;
    std::shared_ptr<Input> m_input;
};

#endif // PAUSECOMPONENT_H
