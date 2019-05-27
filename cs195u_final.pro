QT += core gui opengl

TARGET = cs195u_engine
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++14
CONFIG += c++14

unix:!macx {
    LIBS += -lGLU
    INCLUDEPATH +=  /usr/include
    LIBS += -lassimp
}
macx {
    QMAKE_CFLAGS_X86_64 += -mmacosx-version-min=10.7
    QMAKE_CXXFLAGS_X86_64 = $$QMAKE_CFLAGS_X86_64
    CONFIG += c++11
    INCLUDEPATH +=  /usr/local/include
    LIBS += /usr/local/lib/libassimp.dylib
}
win32 {
    DEFINES += GLEW_STATIC
    LIBS += -lopengl32 -lglu32
    INCLUDEPATH += "C:/Assimp4/include"
    LIBS += -L"C:/Assimp4/lib/Release" -lassimp
}

SOURCES += \
    libs/glew-1.10.0/src/glew.c \
    src/main.cpp \
    src/mainwindow.cpp \
    src/view.cpp \
    src/viewformat.cpp \
    src/engine/graphics/ResourceLoader.cpp \
    src/engine/graphics/FBO.cpp \
    src/engine/graphics/IBO.cpp \
    src/engine/graphics/Texture.cpp \
    src/engine/graphics/Texture1D.cpp \
    src/engine/graphics/Texture2D.cpp \
    src/engine/graphics/Texture3D.cpp \
    src/engine/graphics/VAO.cpp \
    src/engine/graphics/VBO.cpp \
    src/engine/graphics/VBOAttribMarker.cpp \
    src/engine/graphics/Font.cpp \
    src/engine/graphics/DepthBuffer.cpp \
    src/engine/graphics/RenderBuffer.cpp \
    src/engine/graphics/GraphicsDebug.cpp \
    src/engine/graphics/Shader.cpp \
    src/engine/graphics/Camera.cpp \
    src/engine/graphics/Shape.cpp \
    src/engine/graphics/Graphics.cpp \
    src/engine/graphics/Material.cpp \
    src/engine/graphics/Light.cpp \
    src/engine/basics/application.cpp \
    src/engine/basics/input.cpp \
    src/engine/basics/gameworld.cpp \
    src/engine/basics/gameobject.cpp \
    src/engine/components/component.cpp \
    src/engine/components/componenttype.cpp \
    src/engine/systems/drawsystem.cpp \
    src/engine/systems/system.cpp \
    src/engine/systems/ticksystem.cpp \
    src/engine/basics/keystate.cpp \
    src/engine/components/physicscomponent.cpp \
    src/engine/systems/collisionsystem.cpp \
    src/engine/components/collisioncomponent.cpp \
    src/engine/map/rectangle.cpp \
    src/engine/util/random.cpp \
    src/engine/components/cameracomponent.cpp \
    src/engine/map/textureatlas.cpp \
    src/engine/components/transformcomponent.cpp \
    src/engine/util/transform.cpp \
    src/engine/util/util.cpp \
    src/engine/graphics/cullers/boxculler.cpp \
    src/engine/graphics/cullers/culler.cpp \
    src/engine/graphics/cullers/cullmath.cpp \
    src/engine/graphics/cullers/chunkculler.cpp \
    src/engine/navigation/astar.cpp \
    src/engine/navigation/vertex.cpp \
    src/engine/navigation/edge.cpp \
    src/engine/components/uicomponent.cpp \
    src/engine/components/objectdrawcomponent.cpp \
    src/engine/systems/objectdrawsystem.cpp \
    src/engine/components/drawable.cpp \
    src/engine/components/tickable.cpp \
    src/engine/systems/uidrawsystem.cpp \
    src/engine/systems/uiticksystem.cpp \
    src/test/astartest.cpp \
    src/test/testvertex.cpp \
    src/test/testedge.cpp \
    src/engine/navigation/graphpath.cpp \
    src/dungeon_crawler/map/dungeonedge.cpp \
    src/dungeon_crawler/map/dungeonvertex.cpp \
    src/dungeon_crawler/screens/dungeoncrawlerapplication.cpp \
    src/dungeon_crawler/screens/dungeoncrawlerlandingscreen.cpp \
    src/dungeon_crawler/map/point.cpp \
    src/dungeon_crawler/components/dcplayerinputcomponent.cpp \
    src/dungeon_crawler/components/healthcomponent.cpp \
    src/engine/screens/blankscreen.cpp \
    src/engine/screens/gamescreen.cpp \
    src/engine/screens/screen.cpp \
    src/engine/screens/pausescreen.cpp \
    src/engine/components/unpausecomponent.cpp \
    src/engine/components/pausecomponent.cpp \
    src/engine/components/collisionresponsecomponent.cpp \
    src/engine/components/timeremovecomponent.cpp \
    src/engine/UI/textui.cpp \
    src/engine/UI/uielement.cpp \
    src/engine/UI/shapeui.cpp \
    src/engine/UI/button.cpp \
    src/engine/util/ticktimer.cpp \
    src/engine/basics/typeid.cpp \
    src/final/final_screens/finalapplication.cpp \
    src/final/final_screens/mainscreen.cpp \
    src/final/final_screens/menuscreen.cpp \
    src/engine/collisionutils/aabbox.cpp \
    src/engine/navigation/navigationmesh.cpp \
    src/engine/systems/continuouscollisionsystem.cpp \
    src/engine/components/continuouscollisioncomponent.cpp \
    src/engine/components/trianglemeshcomponent.cpp \
    src/final/mapgeneration/trianglemeshterraingenerator.cpp \
    src/engine/components/animationcomponent.cpp \
    src/engine/Animation/mesh.cpp \
    src/engine/graphics/MeshShape.cpp \
    src/engine/systems/animationdrawsystem.cpp \
    src/engine/systems/animationticksystem.cpp \
    src/final/mapgeneration/chunkloadingsystem.cpp \
    src/final/mapgeneration/trianglemeshcache.cpp \
    src/engine/navigation/navigationtriangle.cpp \
    src/engine/navigation/navigationpolygon.cpp \
    src/engine/navigation/navigationedge.cpp \
    src/test/navmeshtest.cpp \
    src/engine/UI/uipanel.cpp \
    src/final/mapgeneration/mountainenvironment.cpp \
    src/final/mapgeneration/desertenvironment.cpp \
    src/engine/collisionutils/object.cpp \
    src/engine/collisionutils/ellipsoid.cpp \
    src/engine/collisionutils/linesegment.cpp \
    src/engine/collisionutils/plane.cpp \
    src/engine/collisionutils/sphere.cpp \
    src/engine/collisionutils/triangle.cpp \
    src/engine/collisionutils/ellipsoidtrianglecollision.cpp \
    src/engine/systems/camerasystem.cpp \
    src/final/mapgeneration/aquaticenvironment.cpp \
    src/engine/map_generation/compoundnoise.cpp \
    src/engine/map_generation/mapnoise.cpp \
    src/engine/map_generation/valuenoise.cpp \
    src/engine/map_generation/environment.cpp \
    src/engine/map_generation/circleweightfunction.cpp \
    src/engine/map_generation/inversecircleweightfunction.cpp \
    src/engine/map_generation/uniformweightfunction.cpp \
    src/engine/map_generation/squareweightfunction.cpp \
    src/final/mapgeneration/blankenvironment.cpp \
    src/final/abilities/abilityconstants.cpp \
    src/final/enemygeneration/enemygenerator.cpp \
    src/final/mapgeneration/squaremapnoise.cpp \
    src/engine/UI/sliderui.cpp \
    src/engine/decisionmaking/btnode.cpp \
    src/engine/decisionmaking/composite.cpp \
    src/engine/decisionmaking/condition.cpp \
    src/engine/decisionmaking/action.cpp \
    src/engine/decisionmaking/sequence.cpp \
    src/engine/decisionmaking/selector.cpp \
    src/engine/components/aicomponent.cpp \
    src/engine/components/airesponsecomponent.cpp \
    src/final/decisionmaking/findpathtotarget.cpp \
    src/final/decisionmaking/movetowardstarget.cpp \
    src/final/decisionmaking/neartarget.cpp \
    src/final/decisionmaking/setupdefense.cpp \
    src/final/final_screens/gameoverscreen.cpp \
    src/final/final_components/collision_components/bulletcollisionresponsecomponent.cpp \
    src/final/final_components/collision_components/cubecollisioncomponent.cpp \
    src/final/final_components/collision_components/cylindercollisioncomponent.cpp \
    src/final/final_components/player_components/deathcomponent.cpp \
    src/final/final_components/player_components/dynamicmovecomponent.cpp \
    src/final/final_components/enemy_components/enemyaicomponent.cpp \
    src/final/final_components/enemy_components/enemyairesponsecomponent.cpp \
    src/final/final_components/enemy_components/enemycollisionresponsecomponent.cpp \
    src/final/final_components/enemy_components/enemymovecomponent.cpp \
    src/final/final_components/collision_components/impactbulletcollisionresponsecomponent.cpp \
    src/final/final_components/player_components/playerabilitycomponent.cpp \
    src/final/final_components/player_components/playercollisionresponsecomponent.cpp \
    src/final/final_components/player_components/playercontrolcomponent.cpp \
    src/final/final_components/collision_components/spherecollisioncomponent.cpp \
    src/final/final_components/terrain_components/terrainsettingcomponent.cpp \
    src/final/final_components/terrain_components/trianglemeshterraincomponent.cpp \
    src/final/final_components/enemy_components/enemyabilitycomponent.cpp \
    src/final/enemygeneration/enemyremovalsystem.cpp \
    src/final/final_components/player_components/playerlevelcomponent.cpp \
    src/final/decisionmaking/deadself.cpp

HEADERS += \
    libs/glew-1.10.0/include/GL/glew.h \
    libs/stb/stb_rect_pack.h \
    libs/stb/stb_truetype.h \
    src/mainwindow.h \
    src/view.h \
    src/viewformat.h \
    src/engine/util/CommonIncludes.h \
    src/engine/graphics/ResourceLoader.h \
    src/engine/graphics/CylinderData.h \
    src/engine/graphics/SphereData.h \
    src/engine/graphics/FBO.h \
    src/engine/graphics/IBO.h \
    src/engine/graphics/Texture.h \
    src/engine/graphics/Texture1D.h \
    src/engine/graphics/Texture2D.h \
    src/engine/graphics/Texture3D.h \
    src/engine/graphics/VAO.h \
    src/engine/graphics/VBO.h \
    src/engine/graphics/VBOAttribMarker.h \
    src/engine/graphics/CubeData.h \
    src/engine/graphics/Font.h \
    src/engine/graphics/DepthBuffer.h \
    src/engine/graphics/RenderBuffer.h \
    src/engine/graphics/GraphicsDebug.h \
    src/engine/graphics/Shader.h \
    src/engine/graphics/ShaderAttribLocations.h \
    src/engine/graphics/Camera.h \
    src/engine/graphics/Graphics.h \
    src/engine/graphics/Shape.h \
    src/engine/graphics/Material.h \
    src/engine/graphics/Light.h \
    src/engine/graphics/Constants.h \
    src/engine/basics/application.h \
    src/engine/basics/input.h \
    src/engine/basics/gameworld.h \
    src/engine/systems/system.h \
    src/engine/systems/drawsystem.h \
    src/engine/systems/ticksystem.h \
    src/engine/components/component.h \
    src/engine/components/componenttype.h \
    src/engine/basics/gameobject.h \
    src/engine/basics/keystate.h \
    src/engine/components/physicscomponent.h \
    src/engine/systems/collisionsystem.h \
    src/engine/components/collisioncomponent.h \
    src/engine/map/rectangle.h \
    src/engine/util/random.h \
    src/engine/components/cameracomponent.h \
    src/engine/map/textureatlas.h \
    src/engine/map/direction.h \
    src/engine/components/transformcomponent.h \
    src/engine/util/transform.h \
    src/engine/util/util.h \
    src/engine/graphics/cullers/boxculler.h \
    src/engine/graphics/cullers/culler.h \
    src/engine/graphics/cullers/cullmath.h \
    src/engine/graphics/cullers/chunkculler.h \
    src/engine/navigation/astar.h \
    src/engine/navigation/vertex.h \
    src/engine/navigation/edge.h \
    src/engine/components/uicomponent.h \
    src/engine/components/objectdrawcomponent.h \
    src/engine/systems/objectdrawsystem.h \
    src/engine/components/drawable.h \
    src/engine/components/tickable.h \
    src/engine/systems/uidrawsystem.h \
    src/engine/systems/uiticksystem.h \
    src/test/astartest.h \
    src/test/testvertex.h \
    src/test/testedge.h \
    src/engine/navigation/graphpath.h \
    src/dungeon_crawler/map/dungeonedge.h \
    src/dungeon_crawler/map/dungeonvertex.h \
    src/dungeon_crawler/screens/dungeoncrawlerapplication.h \
    src/dungeon_crawler/screens/dungeoncrawlerlandingscreen.h \
    src/dungeon_crawler/map/point.h \
    src/dungeon_crawler/components/dcplayerinputcomponent.h \
    src/dungeon_crawler/components/healthcomponent.h \
    src/engine/screens/screen.h \
    src/engine/screens/gamescreen.h \
    src/engine/screens/blankscreen.h \
    src/engine/screens/pausescreen.h \
    src/engine/components/unpausecomponent.h \
    src/engine/components/pausecomponent.h \
    src/engine/components/collisionresponsecomponent.h \
    src/engine/components/timeremovecomponent.h \
    src/engine/UI/textui.h \
    src/engine/UI/uielement.h \
    src/engine/UI/shapeui.h \
    src/engine/UI/button.h \
    src/engine/UI/textalignment.h \
    src/engine/util/ticktimer.h \
    src/engine/basics/typeid.h \
    src/final/final_screens/finalapplication.h \
    src/final/final_screens/mainscreen.h \
    src/final/final_screens/menuscreen.h \
    src/engine/collisionutils/aabbox.h \
    src/engine/collisionutils/floor.h \
    src/engine/collisionutils/interval.h \
    src/engine/collisionutils/ray.h \
    src/engine/collisionutils/collisionshape.h \
    src/engine/navigation/navigationmesh.h \
    src/engine/systems/continuouscollisionsystem.h \
    src/engine/components/continuouscollisioncomponent.h \
    src/engine/components/trianglemeshcomponent.h \
    src/final/mapgeneration/trianglemeshterraingenerator.h \
    src/engine/components/animationcomponent.h \
    src/engine/Animation/mesh.h \
    src/engine/map/shapevertex.h \
    src/engine/graphics/MeshShape.h \
    src/engine/systems/animationdrawsystem.h \
    src/engine/systems/animationticksystem.h \
    src/final/mapgeneration/chunkloadingsystem.h \
    src/final/mapgeneration/trianglemeshcache.h \
    src/engine/navigation/navigationtriangle.h \
    src/engine/navigation/navigationpolygon.h \
    src/engine/navigation/navigationedge.h \
    src/test/navmeshtest.h \
    src/engine/UI/uipanel.h \
    src/final/mapgeneration/mountainenvironment.h \
    src/final/mapgeneration/desertenvironment.h \
    src/engine/collisionutils/ellipsoid.h \
    src/engine/collisionutils/hittest.h \
    src/engine/collisionutils/linesegment.h \
    src/engine/collisionutils/object.h \
    src/engine/collisionutils/plane.h \
    src/engine/collisionutils/sphere.h \
    src/engine/collisionutils/triangle.h \
    src/engine/collisionutils/ellipsoidtrianglecollision.h \
    src/engine/systems/camerasystem.h \
    src/final/mapgeneration/aquaticenvironment.h \
    src/engine/map_generation/weightfunction.h \
    src/engine/map_generation/valuenoise.h \
    src/engine/map_generation/noisefunction.h \
    src/engine/map_generation/mapnoise.h \
    src/engine/map_generation/compoundnoise.h \
    src/engine/map_generation/environment.h \
    src/engine/map_generation/circleweightfunction.h \
    src/engine/map_generation/inversecircleweightfunction.h \
    src/engine/map_generation/uniformweightfunction.h \
    src/engine/map_generation/squareweightfunction.h \
    src/final/mapgeneration/blankenvironment.h \
    src/final/abilities/abilityconstants.h \
    src/final/enemygeneration/enemygenerator.h \
    src/final/mapgeneration/squaremapnoise.h \
    src/engine/UI/sliderui.h \
    src/engine/decisionmaking/btnode.h \
    src/engine/decisionmaking/condition.h \
    src/engine/decisionmaking/action.h \
    src/engine/decisionmaking/selector.h \
    src/engine/decisionmaking/sequence.h \
    src/engine/decisionmaking/composite.h \
    src/engine/components/airesponsecomponent.h \
    src/engine/components/aicomponent.h \
    src/final/decisionmaking/findpathtotarget.h \
    src/final/decisionmaking/movetowardstarget.h \
    src/final/decisionmaking/neartarget.h \
    src/final/decisionmaking/setupdefense.h \
    src/final/final_screens/gameoverscreen.h \
    src/final/final_components/player_components/deathcomponent.h \
    src/final/final_components/enemy_components/enemyaicomponent.h \
    src/final/final_components/collision_components/bulletcollisionresponsecomponent.h \
    src/final/final_components/collision_components/cubecollisioncomponent.h \
    src/final/final_components/collision_components/cylindercollisioncomponent.h \
    src/final/final_components/enemy_components/enemyairesponsecomponent.h \
    src/final/final_components/enemy_components/enemycollisionresponsecomponent.h \
    src/final/final_components/enemy_components/enemymovecomponent.h \
    src/final/final_components/player_components/playerabilitycomponent.h \
    src/final/final_components/player_components/playercollisionresponsecomponent.h \
    src/final/final_components/player_components/playercontrolcomponent.h \
    src/final/final_components/collision_components/spherecollisioncomponent.h \
    src/final/final_components/terrain_components/terrainsettingcomponent.h \
    src/final/final_components/terrain_components/trianglemeshterraincomponent.h \
    src/final/final_components/player_components/dynamicmovecomponent.h \
    src/final/final_components/collision_components/impactbulletcollisionresponsecomponent.h \
    src/final/final_components/enemy_components/enemyabilitycomponent.h \
    src/final/enemygeneration/enemyremovalsystem.h \
    src/final/final_components/player_components/playerlevelcomponent.h \
    src/final/decisionmaking/deadself.h

FORMS += src/mainwindow.ui

RESOURCES += \
    res/shaders/shaders.qrc \
    res/fonts/fonts.qrc \
    res/images/images.qrc \
    res/meshes/mesh.qrc

OTHER_FILES += \
    res/images/grass.png \
    res/images/ice.png \
    res/images/rocky.png \
    res/images/minecraftSand.png \
    res/images/terrain.png \
    res/images/crosshair.png \

DISTFILES += \
    res/shaders/shader.vert \
    res/shaders/shader.frag \
    res/shaders/skinning.vert \
    res/images/BaseMesh_Anim.fbx \
    res/images/Apple.obj \
    res/images/boblampclean.md5anim \
    res/images/boblampclean.md5mesh \
    src/engine/Animation/boblampclean.md5anim \
    src/engine/Animation/boblampclean.md5mesh

INCLUDEPATH += src libs glm libs/glew-1.10.0/include
DEPENDPATH += src libs glm libs/glew-1.10.0/include

# Don't add the -pg flag unless you know what you are doing. It makes QThreadPool freeze on Mac OS X
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_CXXFLAGS_WARN_ON -= -Wall
QMAKE_CXXFLAGS_WARN_ON += -Waddress -Warray-bounds -Wc++0x-compat -Wchar-subscripts -Wformat\
                          -Wmain -Wmissing-braces -Wparentheses -Wreorder -Wreturn-type \
                          -Wsequence-point -Wsign-compare -Wstrict-overflow=1 -Wswitch \
                          -Wtrigraphs -Wuninitialized -Wunused-label -Wunused-variable \
                          -Wvolatile-register-var -Wno-extra

QMAKE_CXXFLAGS += -g
