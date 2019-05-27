# cs195u_engine

## Yuanning Hu

#### Engine:
## Continuous Collision Component
 - Handle continous collision, which is the collision of object(ellipsoid) with terrian(triangle meshes)
 
## Collision Component
 - Handle object object collision. It supports all kinds of collisions among the shapes cylinder, sphere, and cube.

## Collision Response Component
 - Handle collision movements and return the difference between the target the movement and the actual movement for movement adjustment.
 - Contains collision response overridable functions
 
## Continuous Collision System
 - Calculate velocity/movement vector and trigger continous collision response
 
## Collision System
 - Detect collision, calculate mtv and trigger collision response, adjust movement if needed.

#### Game:

## Random Enemy Position Generator
 - Enemy generator was called when loading chunk and enemies are removed when unloading chunk
 - This could be optimized because sometimes the enemy on one chunk can move to another and they shouldn't be removed when the original chunk is unloaded.

## Grant Myers

## Procedural terrain with collisions
 - value noise class deals with terrain generation math
 - chunkloading system loads chunks of terrain
 - trianglemeshterraingenerator generates the terrain geometry 
using trianglemeshcache to store calculated normals and terrain points

#### 4- different biomes with different colors, noise functions, 
 - compound noise works on combining different noise functions, which are contained 
in mapnoise. Mapnoise has an environment (which tells what texture to use for each point)
and returns the weight that compound noise should treat that environment
 - For this game, I subclassed mapnoise into squaremap noise, which takes in a seperate noise function
that determines which environment is present where. 
 - There are 3 environments- aquatic, desert, and mountain, which are defined in chunkloadingsystem

## Navigation meshes - 3
- navmesh is done in navmesh. Navigate takes in two points
and returns a path that you can take to reach the end point
uses navigation triangles and navigation edges
- trianglemeshterraingenerator adds the triangles to 
trianglemeshterraincomponent, which contains all of the navtriangles
for a given chunk. chunkloadingsystem connects and disconnects the
triangles in trianglemeshterraincomponent from each other as chunks are streamed in and out. 
 
## Ayse Sena Demir

## Animation:
#### Engine:
- AnimationComponent - Draws the mesh and ticks as well as  wrapper for some of the mesh class parameters.
- Mesh class - Handles most of the animation and loading and arranging the mesh parameters. Handles the bones and bone transformations and rotations.
- Mesh shape - A class similar to shape class from graphics code with updated elements for animation.
- VertexBone struct - Holds bone id and weight
- Bone struct - Holds the bone transformation and offset.
- AnimationTickSystem and AnimationDrawSystem - Systems for drawing and ticking the animated meshes
#### Game:
- AbilityConstants: Has the constants for the player's abilities for UI and Animation. (Has also been edited by Grant)
- PlayerAbilityComponent: Holds the player abilities and has setter and getter for these.
- PlayerControlComponent: Built up from the existing engine to support player's new abilities and handle animations for walking, sprinting, attacking and changing the attacks etc. (Has been edited by Grant to support shooting balls and smoother animation and better attack animation)
- In MainScreen: Added the animation components for the player as well as the player animation map loading (makePlayerAnimations, this was also edited by Grant for better looking attack animations)
- In EnemyGenerator: Addition's to Yuanning's EnemyGenerator to load all the meshes of the enemies for enemy generation (loadEnemy method). Also the getEnemy method that creates a psedo random enemy for a specific environment from that environment's available enemies and sets up enemy animation time and speed.
- In EnemyMoveComponent: Added the animation maps for the enemies idle, move, attack and death animations as well as mapping them in appropriate places on top of Grant's work. Created enemy movements based on the enemy player distance. (Has been a collaborative effort with Grant to arrange enemy directions.)
- In PlayerCollisionResponse and EnemyCollisionResponse: Filled in objectCollisionResponse methods for player and enemies to lose health.

#### Known Bugs:
- Not really a bug but the if the player shoots while jumping or walking, the animation is stuck on the initial attack pose. (The mesh did not have attack and move animations).
- The jump stops when the velocity is negative of jump velocity therefore sometimes the jump gets stuck.

## UI:
#### Engine:
- UIComponent: Was edited to support UIPanel.
- UIPanel: This class allows multiple UIElements to be added into a panel for relative positioning and sizing of the elements within the panel. The panel can have a back ground or can be blank. It will draw and tick all the elements in it. It has addUIElement method for adding elements as well as callback methods for all the elements in it or only a specific one.
- SliderUI: This ui element class allows the addition of a slider that can respond to clicks and slides on it. It will draw a slider that when clicked on a bar of the bar the circle moves to that point and the circle can be dragged as well. It has a setCallback method that allows the addition of a response to the change in the bar.
#### Game:
- Implemented all the UI in the MainScreen.
- Implemented the MenuScreen and GameOver Screen.
- MainScreen: This screen's UI shows the current selected attack along with all the available attacks. It also has the player's health bar and the stamina bar.
- MenuScreen: This screen has a welcome text as well as the controls for the game. The start button starts the game and the slider allows the user to choose the color of the player. The player is shown in this screen as well so the user can see the color.
- GameOverScreen: Shows up when player dies. It allows the game to start again from scratch when clicked on start. Lets the user know "GameOver".

#### Known Bugs:
- Gameover screen takes a while to load the game again. And the player starts red instead of the prior color.


## Design Decisions:

- ContinuousCollisionComponent - Contain ellipsoids
- ContinuousCollisionSystem - Handle ellipsoid-triangle collision
- ContinuousTriangleMeshSystem - Generate needed TriangleMeshTerrain chunk object based on player's position
- TriangleMeshComponent - Contain triangle mesh information
- TriangleMeshTerrainGenerator - Generate TriangleMeshTerrain chunk object
- InterpolationMath - Help to break down important bump map points into smaller triangles with parameter of density

- AnimationComponent - Draws the mesh and ticks.
- Mesh class - Handles most of the animation and loading and arranging the mesh parameters.
Handles the bones and bone transformations and rotations.
-Bones struct - Holds bone id and weight
