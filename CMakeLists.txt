cmake_minimum_required(VERSION 3.16)
project(Pong VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib
        GIT_TAG master
)

FetchContent_MakeAvailable(raylib)

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
)

target_compile_definitions(
        Pong PRIVATE WORKDIR_PATH="${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(Pong PRIVATE raylib)

