#include "Game.h"

#include "Graphics.h"
#include "raylib.h"

void Game::run()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();

        updateGameLogic();
        draw();

        EndDrawing();
    }
}

void Game::updateGameLogic()
{
    float delta = GetFrameTime();
    float time = GetTime();

    switch (gamedata.gameState)
    {
        case GameState::RUNNING:
            handleInputs(delta);
            gamedata.background.draw(time);
            break;

        case GameState::RESTART:
            break;

        case GameState::STOPPED:
            gamedata.gameState = GameState::RUNNING;
            break;

        case GameState::START:
            gamedata.players = {
                Player{0, {}, Rectangle{10, (float) GetRandomValue(0, GetScreenHeight() - 50), 10, 50}, DEFAULT_SPEED},
                Player{
                    0, {},
                    Rectangle{
                        (float) GetScreenWidth() - 10 - 10, (float) GetRandomValue(0, GetScreenHeight() - 50), 10, 50
                    },
                    DEFAULT_SPEED
                }
            };
            gamedata.gameState = GameState::RUNNING;
            break;
    }
}

void Game::draw()
{
    ClearBackground(Color{0, 0, 0, 0xFF});
    for (Player &player: gamedata.players)
    {
        DrawRectangleRec(player.bar, Color{0xFF, 0xFF, 0xFF, 0xFF});
    }
    DrawText("Test", 20, 20, 20, Color{0xFF, 0xFF, 0xFF, 0xFF});
}

void Game::handleInputs(float delta)
{
    if (IsKeyDown(KEY_W)) { gamedata.players[0].bar.y -= DEFAULT_SPEED * delta; }
    if (IsKeyDown(KEY_S)) { gamedata.players[0].bar.y += DEFAULT_SPEED * delta; }
    if (IsKeyDown(KEY_A)) { gamedata.players[0].bar.x -= DEFAULT_SPEED * delta; }
    if (IsKeyDown(KEY_D)) { gamedata.players[0].bar.x += DEFAULT_SPEED * delta; }

    if (IsKeyDown(KEY_UP)) { gamedata.players[1].bar.y -= DEFAULT_SPEED * delta; }
    if (IsKeyDown(KEY_DOWN)) { gamedata.players[1].bar.y += DEFAULT_SPEED * delta; }
    if (IsKeyDown(KEY_LEFT)) { gamedata.players[1].bar.x -= DEFAULT_SPEED * delta; }
    if (IsKeyDown(KEY_RIGHT)) { gamedata.players[1].bar.x += DEFAULT_SPEED * delta; }
}


void Game::init()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong 2");
    SetTargetFPS(TARGET_FPS);
    gamedata.gameState = GameState::START;
    gamedata.background = Background{};
}

void Game::shutdown()
{
    CloseWindow();
}
