#ifndef BTNODE_H
#define BTNODE_H
#include <map>
#include <glm/glm.hpp>
enum Status	{SUCCESS, FAIL, RUNNING};
class BTNode
{
public:
    BTNode(std::map<std::string, std::string> &blackboard);
    virtual ~BTNode();
    virtual Status update(float seconds) = 0;
    virtual void reset() = 0;

protected:
    void writeToBlackboard(const std::string &key, const std::string &value);
    std::string readFromBlackbload(const std::string &key) const;

private:
    std::map<std::string, std::string> &m_blackboard;
};

#endif // BTNODE_H
