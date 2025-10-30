cmake_minimum_required(VERSION 3.16)
project(Pong VERSION 0.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib
        GIT_TAG master
)

FetchContent_Declare(
		glm
		GIT_REPOSITORY https://github.com/g-truc/glm
		GIT_TAG master
)

FetchContent_MakeAvailable(raylib)
FetchContent_MakeAvailable(glm)

add_executable(Pong
		Game/src/main.cpp
		Game/src/Game.h
		Game/src/Game.cpp
		Game/src/Core/Graphics/Graphics.cpp
		Game/src/Core/Graphics/Graphics.h
		Game/src/Core/Player.h
		Game/src/Core/Items.h
		Game/src/Core/Graphics/Background.cpp
		Game/src/Core/Graphics/Background.h
		Game/src/Core/Ball.h
		Game/src/Core/Collision.h
		Game/src/Core/Graphics/Draw.h
		Game/src/Core/Graphics/Draw.cpp
		Game/src/Core/Constants.h
		Game/src/Core/Input.h
		Game/src/Core/Collision.cpp
		Game/src/Core/Music/MusicManager.cpp
		Game/src/Core/Music/MusicManager.h
		Engine/src/Core/Level/Level.h
		Engine/src/Core/ECS/Entity/Entity.h
		Engine/src/Core/ErrorCodes.h
		Engine/src/Core/ECS/Component/Component.h
		Engine/src/Core/ECS/Systems/SystemManager.cpp
		Engine/src/Core/ECS/Systems/SystemManager.h
		Engine/src/Core/ECS/Entity/EntityManager.cpp
		Engine/src/Core/ECS/Entity/EntityManager.h
		Engine/src/Core/ECS/Registry.h
		Engine/src/Core/ECS/Systems/CollisionSystem.cpp
		Engine/src/Core/ECS/Systems/CollisionSystem.h
		Engine/src/Core/Renderer/Renderer.h
		Engine/src/Core/Color.h
		Engine/src/Core/Renderer/RaylibRenderer/RaylibRenderer.cpp
		Engine/src/Core/Renderer/RaylibRenderer/RaylibRenderer.h
		Engine/src/Core/Renderer/RaylibRenderer/Window.h
		Engine/src/Core/ECS/Systems/System.h
		Engine/src/Core/ECS/ECS.h
		Engine/src/Core/Level/LevelManager.cpp
		Engine/src/Core/Level/LevelManager.h
		Engine/src/Core/Layer/Layer.h
		Engine/src/Core/Layer/LayerStack.cpp
		Engine/src/Core/Layer/LayerStack.h
		Engine/src/Core/Layer/Layer.cpp
		Engine/src/Core/ECS/Component/Components/Core.h
		Engine/src/Core/ECS/Component/Components/Audio.h
		Engine/src/Core/ECS/Component/Components/Gameplay.h
		Engine/src/Core/ECS/Component/Components/Logic.h
		Engine/src/Core/ECS/Component/Components/Meta.h
		Engine/src/Core/ECS/Component/Components/Network.h
		Engine/src/Core/ECS/Component/Components/Physics.h
		Engine/src/Core/ECS/Component/Components/Rendering.h
		Engine/src/Core/ECS/Component/Components/SYSTEM.h
)

target_compile_definitions(
        Pong PRIVATE WORKDIR_PATH="${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(Pong PRIVATE raylib glm)

