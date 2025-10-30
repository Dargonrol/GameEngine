cmake_minimum_required(VERSION 3.16)
project(Pong VERSION 0.1 LANGUAGES CXX)

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
        src/main.cpp
		src/Game.h
		src/Game.cpp
		src/Core/Graphics/Graphics.cpp
		src/Core/Graphics/Graphics.h
		src/Core/Player.h
		src/Core/Items.h
		src/Core/Graphics/Background.cpp
		src/Core/Graphics/Background.h
		src/Core/Ball.h
        src/Core/Collision.h
		src/Core/Graphics/Draw.h
		src/Core/Graphics/Draw.cpp
		src/Core/Constants.h
		src/Core/Input.h
        src/Core/Collision.cpp
		src/Core/Music/MusicManager.cpp
		src/Core/Music/MusicManager.h
		src/Core/Level/Level.h
		src/Core/ECS/Entity/Entity.h
		src/Core/ErrorCodes.h
		src/Core/ECS/Components/Components.h
		src/Core/ECS/Systems/SystemManager.cpp
		src/Core/ECS/Systems/SystemManager.h
		src/Core/ECS/Entity/EntityManager.cpp
		src/Core/ECS/Entity/EntityManager.h
        src/Core/ECS/Registry.h
		src/Core/ECS/Systems/CollisionSystem.cpp
		src/Core/ECS/Systems/CollisionSystem.h
		src/Core/Renderer/Renderer.h
		src/Core/Color.h
		src/Core/Renderer/RaylibRenderer/RaylibRenderer.cpp
		src/Core/Renderer/RaylibRenderer/RaylibRenderer.h
		src/Core/Renderer/RaylibRenderer/Window.h
		src/Core/ECS/Systems/System.h
        src/Core/ECS/ECS.h
		src/Core/Level/LevelManager.cpp
		src/Core/Level/LevelManager.h
		src/Core/Layer/Layer.h
		src/Core/Layer/LayerStack.cpp
		src/Core/Layer/LayerStack.h
)

target_compile_definitions(
        Pong PRIVATE WORKDIR_PATH="${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(Pong PRIVATE raylib glm)

