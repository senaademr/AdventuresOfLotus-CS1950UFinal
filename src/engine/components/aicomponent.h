#ifndef AICOMPONENT_H
#define AICOMPONENT_H
#include "component.h"
#include "tickable.h"

#include <memory>
#include <glm/glm.hpp>
#include <map>

class Composite;
class AIComponent : public Component, public Tickable
{
public:
    AIComponent();
    virtual ~AIComponent() override;
    void tick(float seconds) override;

protected:
    std::map<std::string, std::string> m_blackboard;
    std::shared_ptr<Composite> m_rootSelector;
};

#endif // AICOMPONENT_H
