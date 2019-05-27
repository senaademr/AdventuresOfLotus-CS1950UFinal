#include "chunkloadingsystem.h"

#include "engine/basics/gameworld.h"
#include "final/mapgeneration/trianglemeshterraingenerator.h"
#include "engine/map_generation/compoundnoise.h"
#include "engine/map_generation/valuenoise.h"
#include "engine/map/textureatlas.h"

#include "engine/components/transformcomponent.h"
#include "engine/basics/gameobject.h"
#include "final/final_components/terrain_components/terrainsettingcomponent.h"
#include "final/final_components/terrain_components/trianglemeshterraincomponent.h"

#include "engine/navigation/navigationpolygon.h"
#include "engine/util/util.h"
#include "engine/navigation/navigationmesh.h"

#include "engine/map_generation/mapnoise.h"
#include "engine/map_generation/uniformweightfunction.h"
#include "engine/map_generation/circleweightfunction.h"
#include "engine/map_generation/inversecircleweightfunction.h"
#include "engine/map_generation/squareweightfunction.h"

#include "final/mapgeneration/blankenvironment.h"
#include "final/mapgeneration/desertenvironment.h"
#include "final/mapgeneration/mountainenvironment.h"
#include "final/mapgeneration/aquaticenvironment.h"
#include "final/mapgeneration/squaremapnoise.h"

#include "engine/util/random.h"

#include "final/enemygeneration/enemygenerator.h"
#include "final/enemygeneration/enemyremovalsystem.h"

ChunkLoadingSystem::ChunkLoadingSystem(std::shared_ptr<GameWorld> gameWorld, std::shared_ptr<EnemyRemovalSystem> enemyRemoval,
                                       std::shared_ptr<TransformComponent> playerTransform)
    : m_gameWorld(gameWorld),
      m_enemyRemoval(enemyRemoval),
      m_playerTransform(playerTransform),
    m_compoundNoise(nullptr),
    m_environmentTexture(nullptr),
    m_atlas(nullptr),
    m_terrainGenerator(nullptr),
    m_enemyGenerator(nullptr),
    m_oldPlayerPosition(-100, 120),
    m_navMesh(nullptr)
{
    addType(TypeID::value<TerrainSettingComponent>());
    m_navMesh = std::make_shared<NavigationMesh>();

    m_terrainHashMap = QHash<glm::ivec2, std::shared_ptr<GameObject>>();


    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    m_compoundNoise = std::make_shared<CompoundNoise>(seed);
    Random::setSeed(seed);
    std::cout << "seed: " << seed << std::endl;

    makeCompoundNoise(seed);

    m_atlas = std::make_shared<TextureAtlas>(16, 16);
    m_atlas->addTexture("sand", glm::ivec2(2, 14));
    m_atlas->addTexture("stone", glm::ivec2(1, 15));
    m_atlas->addTexture("grass", glm::ivec2(0, 15));
    m_atlas->addTexture("snow", glm::ivec2(2, 11));
    m_atlas->addTexture("water", glm::ivec2(14, 3));
    m_atlas->addTexture("blank", glm::ivec2(8, 11));

    m_terrainGenerator = std::make_shared<TriangleMeshTerrainGenerator>(m_compoundNoise, m_atlas, m_environmentTexture);
    m_enemyGenerator = std::make_shared<EnemyGenerator>(m_compoundNoise, m_navMesh, m_gameWorld, m_playerTransform);
}

void ChunkLoadingSystem::makeCompoundNoise(unsigned int seed){


    std::shared_ptr<ValueNoise> emptyNoise = std::make_shared<ValueNoise>();
    emptyNoise->setOctaves(0);
    std::shared_ptr<MapNoise> emptyNoiseMap = std::make_shared<MapNoise>(emptyNoise, std::make_shared<BlankEnvironment>(), .005);
    emptyNoiseMap->addWeightFunction(std::make_shared<UniformWeightFunction>(1));
    m_compoundNoise->addNoiseFunction(emptyNoiseMap);

    std::shared_ptr<ValueNoise> environmentNoise = std::make_shared<ValueNoise>(seed);
    environmentNoise->setFrequency(3);
    environmentNoise->setAmplitude(100);
    environmentNoise->setYShift(50);

    std::shared_ptr<MapNoise> desertNoiseMap = makeDesert(seed, environmentNoise, 0);
    std::shared_ptr<MapNoise> mountainNoiseMap = makeMountain(seed, environmentNoise, 1);
    std::shared_ptr<MapNoise> waterNoiseMap = makeAquatic(seed, environmentNoise, 2);
    m_mapEnvironments.append(desertNoiseMap);
    m_mapEnvironments.append(mountainNoiseMap);
    m_mapEnvironments.append(waterNoiseMap);

    for(std::shared_ptr<MapNoise> mapEnvironment : m_mapEnvironments){
        m_compoundNoise->addNoiseFunction(mapEnvironment);
    }
}


std::shared_ptr<MapNoise> ChunkLoadingSystem::makeDesert(unsigned int seed, std::shared_ptr<ValueNoise> squareMapNoise, int environmentIndex){
    std::shared_ptr<ValueNoise> desertNoise = std::make_shared<ValueNoise>();
    desertNoise->setAmplitude(12.f);
    desertNoise->setFrequency(.06f);
    desertNoise->setOctaves(1);
    desertNoise->setYShift(0);
    std::shared_ptr<MapNoise> desertNoiseMap = std::make_shared<SquareMapNoise>(desertNoise, std::make_shared<DesertEnvironment>(), 1,
                                                                                squareMapNoise, environmentIndex, EnvChunkInnerSize, EnvChunkOuterSize);
//    desertNoiseMap->addWeightFunction(std::make_shared<SquareWeightFunction>(glm::vec2(0), 40, 100));
//    //desertNoiseMap->addWeightFunction(std::make_shared<SquareWeightFunction>(glm::vec2(250, 0), 20, 100));
    return desertNoiseMap;
}

std::shared_ptr<MapNoise> ChunkLoadingSystem::makeAquatic(unsigned int seed, std::shared_ptr<ValueNoise> squareMapNoise, int environmentIndex){
    std::shared_ptr<ValueNoise> waterNoise = std::make_shared<ValueNoise>();
    waterNoise->setAmplitude(20.f);
    waterNoise->setFrequency(.3);
    waterNoise->setYShift(-40);
    std::shared_ptr<MapNoise> waterNoiseMap = std::make_shared<SquareMapNoise>(waterNoise, std::make_shared<AquaticEnvironment>(seed), 5,
                                                                         squareMapNoise, environmentIndex, EnvChunkInnerSize, EnvChunkOuterSize);
//    waterNoiseMap->addWeightFunction(std::make_shared<SquareWeightFunction>(glm::vec2(0, 150), 40, 100));
    return waterNoiseMap;
}

std::shared_ptr<MapNoise> ChunkLoadingSystem::makeMountain(unsigned int seed, std::shared_ptr<ValueNoise> squareMapNoise, int environmentIndex){
    std::shared_ptr<ValueNoise> mountainNoise= std::make_shared<ValueNoise>();
    mountainNoise->setAmplitude(30.f);
    mountainNoise->setFrequency(.1f);
    mountainNoise->setOctaves(5);
    mountainNoise->setYShift(20);
    std::shared_ptr<MapNoise> mountainNoiseMap = std::make_shared<SquareMapNoise>(mountainNoise, std::make_shared<MountainEnvironment>(seed), 5,
                                                                            squareMapNoise, environmentIndex, EnvChunkInnerSize, EnvChunkOuterSize);
//    mountainNoiseMap->addWeightFunction(std::make_shared<SquareWeightFunction>(glm::vec2(150, 0), 40, 100));
//    mountainNoiseMap->addWeightFunction(std::make_shared<SquareWeightFunction>(glm::vec2(150, 150), 40, 100));
    return mountainNoiseMap;
}


glm::ivec2 ChunkLoadingSystem::getCell(glm::vec3 position, float chunkSize){
    int x = std::floor(position.x/ chunkSize);
    int z = std::floor(position.z / chunkSize);
    return glm::ivec2(x, z);
}

glm::ivec2 ChunkLoadingSystem::getCell(glm::vec3 position){
    return getCell(position, CHUNK_SIZE);
}

glm::ivec2 ChunkLoadingSystem::getPlayerCell(){
    return getCell(m_playerTransform->getPosition());
}

void ChunkLoadingSystem::generateTerrain(){
    glm::ivec2 playerPosition = m_oldPlayerPosition;
    //std::cout << "player position: " << playerPosition << std::endl;
    for(int i = - viewDistance; i < viewDistance+1; i ++){
        for(int j = - viewDistance; j < viewDistance+1; j ++){
            glm::ivec2 position = playerPosition + glm::ivec2(j, i);
            if(!m_terrainHashMap.contains(position)){
                m_positionsToAdd.append(position);
            }
        }
    }
}



void ChunkLoadingSystem::removeTerrain(){
    for(glm::ivec2 position : m_terrainHashMap.keys()){
        if(std::abs(m_oldPlayerPosition.x-position.x) > unloadDistance
                || std::abs(m_oldPlayerPosition.y - position.y) > unloadDistance){
            removeChunk(position);
            removeChunkEnemies(position);
        }
    }
}

void ChunkLoadingSystem::removeChunk(glm::ivec2 position){
    std::shared_ptr<TriangleMeshTerrainComponent> terrainMap
            = m_terrainHashMap.value(position)->getComponent<TriangleMeshTerrainComponent>();
    disconnectTerrainFromNeighbors(position, terrainMap);
    m_navMesh->removeChunk(terrainMap);
    m_enemyRemoval->chunkRemoved(position, CHUNK_SIZE);

    m_gameWorld->removeObject(m_terrainHashMap.value(position));
    m_terrainHashMap.remove(position);
}

void ChunkLoadingSystem::removeChunkEnemies(glm::ivec2 position) {
    // remove enemy objects
//    for (std::shared_ptr<GameObject> enemy : m_enemiesHashMap[position]) {
//        m_gameWorld->removeObject(enemy);
//    }
    // remove position key in hashmap
    m_enemiesHashMap.remove(position);
}

void ChunkLoadingSystem::disconnectTerrainFromNeighbors(glm::ivec2 position, std::shared_ptr<TriangleMeshTerrainComponent> terrainMap){
    QMap<Direction, glm::ivec2> offsets = Util::getDirectionOffsets();
    for(Direction dir : offsets.keys()){
        glm::ivec2 neighborPosition = offsets.value(dir) + position;
        if(m_terrainHashMap.contains(neighborPosition)){
            std::shared_ptr<TriangleMeshTerrainComponent> neighborTerrainMap
                    = m_terrainHashMap.value(neighborPosition)->getComponent<TriangleMeshTerrainComponent>();
            //std::cout << "removing neighbor " << dir << "from position: " << position << ", neighbor pos: " << neighborPosition << std::endl;
            terrainMap->removeNeighbor(neighborTerrainMap, dir);
        }
    }
}

void ChunkLoadingSystem::connectTerrainToNeighbors(glm::ivec2 position, std::shared_ptr<TriangleMeshTerrainComponent> terrainMap){
    QMap<Direction, glm::ivec2> offsets = Util::getDirectionOffsets();
    for(Direction dir : offsets.keys()){
        glm::ivec2 neighborPosition = offsets.value(dir) + position;
        if(m_terrainHashMap.contains(neighborPosition)){
            std::shared_ptr<TriangleMeshTerrainComponent> neighborTerrainMap
                    = m_terrainHashMap.value(neighborPosition)->getComponent<TriangleMeshTerrainComponent>();
            //std::cout << "setting neighbor " << dir << "for position: " << position << ", neighbor pos: " << neighborPosition << std::endl;
            terrainMap->setNeighbor(neighborTerrainMap, dir);
        }
    }
}

void ChunkLoadingSystem::addTerrain(glm::ivec2 position){
    glm::vec3 topLeft = glm::vec3(position.x * CHUNK_SIZE, 0, position.y * CHUNK_SIZE);
    //std::cout << "adding terrain at: " << position << std::endl;

    std::shared_ptr<GameObject> terrainObject =
            m_terrainGenerator->makeTriangleMesh(topLeft,CHUNK_SIZE, DENSITY);

    m_gameWorld->addObject(terrainObject);
    std::shared_ptr<TriangleMeshTerrainComponent> terrainMap = terrainObject->getComponent<TriangleMeshTerrainComponent>();

    connectTerrainToNeighbors(position, terrainMap);

    m_navMesh->addChunk(terrainMap);

    m_terrainHashMap.insert(position, terrainObject);
}

void ChunkLoadingSystem::addEnemies(glm::ivec2 position){
    glm::vec3 topLeft = glm::vec3(position.x * CHUNK_SIZE, 0, position.y * CHUNK_SIZE);

    QList<std::shared_ptr<GameObject>> &enemyList = m_enemiesHashMap[position];
    int enemyListStartIndex = enemyList.size();
    m_enemyGenerator->makeEnemies(topLeft, getEnemyGenerationChance(), CHUNK_SIZE, MAX_ENEMY_PER_CHUNK, enemyList);
    int enemyListEndIndex = enemyList.size();

    for (int i = enemyListStartIndex; i < enemyListEndIndex; i++) { // add emenies to game world
        m_gameWorld->addObject(enemyList.at(i));
    }
}

float ChunkLoadingSystem::getEnemyGenerationChance(){
    int numEnemies = m_enemyRemoval->getNumberEnemies();
    if(numEnemies <= 0){
        return BASE_ENEMY_GENERATION_CHANCE;
    }
    else {
        return BASE_ENEMY_GENERATION_CHANCE * std::pow(ENEMY_GENERATION_DECAY_MOD, numEnemies);
    }
}

void ChunkLoadingSystem::tick(float seconds){
    m_enemyGenerator->tick(seconds);    //just to update time
    addNoiseToObjects();
    if(!m_positionsToAdd.isEmpty()){
        glm::ivec2 positionToAdd = m_positionsToAdd.at(0);
//        std::cout << "positionToAdd: " << positionToAdd << std::endl;
        if(!m_terrainHashMap.contains(positionToAdd)){
            addTerrain(m_positionsToAdd.at(0));
            addEnemies(m_positionsToAdd.at(0));
        }
        m_positionsToAdd.removeFirst();
    }
    else{
        glm::ivec2 playerPosition = getPlayerCell();
        if(playerPosition != m_oldPlayerPosition){
            m_oldPlayerPosition = playerPosition;
            generateTerrain();
            removeTerrain();
        }
    }
}

std::shared_ptr<NavigationMesh> ChunkLoadingSystem::getNavmesh(){
    return m_navMesh;
}

QHash<glm::ivec2, std::shared_ptr<GameObject> >& ChunkLoadingSystem::getTerrainObjects(){
    return m_terrainHashMap;
}

void ChunkLoadingSystem::addNoiseToObjects(){
    for(std::shared_ptr<Component> component : m_components){
        std::shared_ptr<TerrainSettingComponent> terrainComponent = std::dynamic_pointer_cast<TerrainSettingComponent>(component);
        if(terrainComponent){
            terrainComponent->setNoise(m_compoundNoise);
        }
        else{
            std::cout << "wrong component in chunkloadingSystem " << std::endl;
        }
    }
}
