#pragma once
#include <array>

#include "Background.h"
#include "Player.h"

enum class GameState
{
    RUNNING,
    STOPPED,
    RESTART,
    START
};

typedef struct GameData
{
    std::array<Player, 2> players;
    GameState gameState;
    Background background;
} GameData;

class Game
{
public:
    Game() = default;

    ~Game() = default;

    void run();

    void init();

    void shutdown();

private:
    void updateGameLogic();

    void draw();

    void handleInputs(float delta);

private:
    GameData gamedata;

    static constexpr int SCREEN_HEIGHT = 450;
    static constexpr int SCREEN_WIDTH = 800;
    static constexpr int TARGET_FPS = 60;
    static constexpr float DEFAULT_SPEED = 200;
};
