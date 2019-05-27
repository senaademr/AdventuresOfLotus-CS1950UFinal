#ifndef ENEMYGENERATOR_H
#define ENEMYGENERATOR_H
#include <memory>
#include <glm/glm.hpp>
#include <QList>
#include <map>
#include <vector>
#include <random>

class CompoundNoise;
class GameObject;
class Mesh;
class NavigationMesh;
class TransformComponent;
class AnimationComponent;
class GameWorld;
class EnemyAbilityComponent;


class EnemyGenerator
{
public:
    EnemyGenerator(std::shared_ptr<CompoundNoise> noise, std::shared_ptr<NavigationMesh> navmesh, std::shared_ptr<GameWorld> gameWorld, std::shared_ptr<TransformComponent> playerTransform);
    ~EnemyGenerator();
    void makeEnemies(const glm::vec3 &topLeft, const float &generationChancePerEnemy, const float &dimension,
                     int maxAmount, QList<std::shared_ptr<GameObject>> &enemyList);
    static glm::vec3 getHealthUIPos(std::string enemyName, std::shared_ptr<TransformComponent> transformComponent, std::shared_ptr<AnimationComponent> anim);
    static glm::vec3 getBoundingCylinder(std::string name, float drawScale);
    void tick(float seconds);   //not override

private:
    void createEnemy(std::shared_ptr<GameObject> &enemy, std::string &environment, glm::vec3 pos);
    glm::vec3 setEnemyPosition(std::shared_ptr<GameObject> &enemy, const glm::vec3 &topLeft, const float &dimension) const;
    void loadEnemy(std::string filename, std::string enemymname);

    std::shared_ptr<EnemyAbilityComponent> getEnemyAbilityComponent(std::string enemyName);

    std::shared_ptr<EnemyAbilityComponent> getSpiderAbilityComponent();
    std::shared_ptr<EnemyAbilityComponent> getMagmaAbilityComponent();
    std::shared_ptr<EnemyAbilityComponent> getSpaceAbilityComponent();

    std::vector<std::string> getEnemy(std::string &environment);


    float getDeathAnimationTime(std::string name);
    float getDrawScale(std::string name);
    std::shared_ptr<CompoundNoise> m_noise;
    std::shared_ptr<NavigationMesh> m_navmesh;
    std::shared_ptr<GameWorld> m_gameWorld;
    std::map<std::string, std::shared_ptr<Mesh>> m_enemyMap;
    std::shared_ptr<TransformComponent> m_playerTransform;
    float m_currentTime;

    std::default_random_engine m_generator;

};

#endif // ENEMYGENERATOR_H
