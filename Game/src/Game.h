#pragma once
#include <array>

#include "../src/Core/Graphics/Background.h"
#include "Core/Ball.h"
#include "Core/Player.h"

namespace Core
{
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
        Ball ball;
        GameState gameState;
        Background background;
    } GameData;

    class Game
    {
    public:
        static Game& getInstance()
        {
            static Game instance;
            return instance;
        }
        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;

        void run();
        void init();
        void shutdown();

    private:
        Game() = default;
        ~Game() = default;

        void updateGameLogic();

        void initData();
        void resetData();

    private:
        GameData gamedata;
    };
}