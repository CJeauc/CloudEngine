# CloudEngine

CloudEngine is a C++/Opengl second year student project realised as a team of 3 peoples : [William Dewaele](https://github.com/Wdewaele), [Saad Raouf](https://github.com/Synyproxy) and myself, in the given time of 5 months.

![alt text](https://github.com/CJeauc/CloudEngine/blob/master/Screenshots/Editor.PNG)

## What is this project about
- Make a game engine from scratch in C++
- The final objective is to make a fps-puzle game with CloudEngine
- Use as few libraries as possible (if we want to use something, we have to implemente it)
- The project counts as our end year project for our second year at Isart Digital Montréal

![](https://media.giphy.com/media/27II2p7JgqbdA65mSD/giphy.gif)

Collision and jump using box collider components and a rigidbody component. The floating cube is a child of the moving and don't have any collider nor physic.

## Constraints
- The editor must work on Windows.
- The engine must use our own mathematics library.
- The engine can only support one rendering API. 
- The engine can use an existing physic library.

## My part
Despite helping my partners, i made the math library ([CloudMath](https://github.com/CJeauc/CloudEngine/tree/master/CloudEngine/CloudMath)), the Entity Component System ([ECS](https://github.com/CJeauc/CloudEngine/tree/master/CloudEngine/Core/include/Core/ECS)), the Physic Engine using Bullet 3 ([Physic](https://github.com/CJeauc/CloudEngine/tree/master/CloudEngine/Physic)) and the components and system needed to the physic to work ([Components](https://github.com/CJeauc/CloudEngine/tree/master/CloudEngine/Core/include/Core/CoreComponent/Physic), [System](https://github.com/CJeauc/CloudEngine/tree/master/CloudEngine/Core/include/Core/CoreSystem/PhysicSystem.h)). I also took care of the resources and singleton management ([Resources Management](https://github.com/CJeauc/CloudEngine/tree/master/CloudEngine/Core/include/Core/Managers), [Singleton Management](https://github.com/CJeauc/CloudEngine/blob/master/CloudEngine/Core/include/Core/Engine/Cloud.h)).

## Libraries used
- Bullet
- Assimp
- Irrklang
- OpenGl
- Qt

## Project status
- The project is currently in progress, so some features will come on future updates.
- We are currently halfway through the time given for the project (deadline : 14 june 2019).

## Build Instruction
- To run the engine you need to set the project "Game" or the project "Editor" as startup project
- To build the editor project, you need to install QT (which is quite heavy).
- You can also run the Editor using the [Build](https://github.com/CJeauc/CloudEngine/tree/master/BuildCloudEngine). ([Editor.exe](https://github.com/CJeauc/CloudEngine/blob/master/BuildCloudEngine/Build/Release-x64/Editor/Editor.exe))

