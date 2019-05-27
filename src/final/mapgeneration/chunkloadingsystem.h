#ifndef CHUNKLOADINGSYSTEM_H
#define CHUNKLOADINGSYSTEM_H


#include "engine/systems/ticksystem.h"
#include "engine/map/direction.h"

#include <QHash>
//keep before including qHash

namespace glm{
namespace detail {

inline uint qHash(const glm::ivec2 &v){
    return ::qHash(53 + ::qHash(v.x)) * 53 + ::qHash(v.y);
    //return qHash(QString::number(v.x) + QString::number(v.y));
}
}
}
#include <QString>

class GameWorld;
class EnemyRemovalSystem;
class TransformComponent;
class CompoundNoise;
class TriangleMeshTerrainGenerator;
class TriangleMeshTerrainComponent;
class NavigationMesh;
class TextureAtlas;
class EnvironmentTexture;
class EnemyGenerator;
class MapNoise;
class ValueNoise;

class ChunkLoadingSystem : public TickSystem
{
public:
    ChunkLoadingSystem(std::shared_ptr<GameWorld> gameWorld, std::shared_ptr<EnemyRemovalSystem> enemyRemoval, std::shared_ptr<TransformComponent> playerTransform);

    // TickSystem interface
public:
    void tick(float seconds);

    std::shared_ptr<NavigationMesh> getNavmesh();
    QHash<glm::ivec2, std::shared_ptr<GameObject> >& getTerrainObjects();
    static glm::ivec2 getCell(glm::vec3 position, float chunkSize);
    glm::ivec2 getCell(glm::vec3 position);


    const float CHUNK_SIZE = 12.f;
    const int DENSITY = 2.f;
    const int viewDistance = 3;
    const int MAX_ENEMY_PER_CHUNK = 1;
//    const float ENEMY_GENERATION_CHANCE = 1.0;
    const float BASE_ENEMY_GENERATION_CHANCE = 0.3;
    const float ENEMY_GENERATION_DECAY_MOD = .5f;
    const int unloadDistance = viewDistance+1;

    const float EnvChunkInnerSize = 40;
    const float EnvChunkOuterSize = 100;
    const float EnvChunkDistanceBetween = EnvChunkOuterSize* 1.5f;
private:
    void makeCompoundNoise(unsigned int seed);

    std::shared_ptr<MapNoise> makeDesert(unsigned int seed, std::shared_ptr<ValueNoise> squareMapNoise, int environmentIndex);
    std::shared_ptr<MapNoise> makeAquatic(unsigned int seed, std::shared_ptr<ValueNoise> squareMapNoise, int environmentIndex);
    std::shared_ptr<MapNoise> makeMountain(unsigned int seed, std::shared_ptr<ValueNoise> squareMapNoise, int environmentIndex);

    int getEnvironmentIndex(glm::ivec2 chunkCoordinate);
    float getEnemyGenerationChance();

    void generateTerrain();
    void connectTerrainToNeighbors(glm::ivec2 position, std::shared_ptr<TriangleMeshTerrainComponent> terrainMap);

    void disconnectTerrainFromNeighbors(glm::ivec2 position, std::shared_ptr<TriangleMeshTerrainComponent> terrainMap);
    void removeTerrain();
    void removeChunk(glm::ivec2 position);
    void removeChunkEnemies(glm::ivec2 position);
    glm::ivec2 getPlayerCell();
    void addTerrain(glm::ivec2 position);
    void addEnemies(glm::ivec2 position);
    void addNoiseToObjects();

private:
    QList<glm::ivec2> m_positionsToAdd;
    std::shared_ptr<GameWorld> m_gameWorld;
    std::shared_ptr<EnemyRemovalSystem> m_enemyRemoval;
    std::shared_ptr<TransformComponent> m_playerTransform;
    std::shared_ptr<CompoundNoise> m_compoundNoise;
    std::shared_ptr<EnvironmentTexture> m_environmentTexture;
    std::shared_ptr<TextureAtlas> m_atlas;
    std::shared_ptr<TriangleMeshTerrainGenerator> m_terrainGenerator;
    std::shared_ptr<EnemyGenerator> m_enemyGenerator;
    QList<std::shared_ptr<MapNoise> > m_mapEnvironments;

    QHash<glm::ivec2, std::shared_ptr<GameObject>> m_terrainHashMap;
    QHash<glm::ivec2, QList<std::shared_ptr<GameObject>>> m_enemiesHashMap;

    glm::ivec2 m_oldPlayerPosition;
    std::shared_ptr<NavigationMesh> m_navMesh;
};


#endif // CHUNKLOADINGSYSTEM_H
