#include "Game.h"
#include <string>

#include "raylib.h"
#include "raymath.h"
#include "Core/Collision.h"
#include "Core/Constants.h"
#include "Core/Input.h"
#include "Core/Graphics/Draw.h"

using namespace Constants;

void Game::run()
{
    while (!WindowShouldClose())
    {
        updateGameLogic();

        BeginDrawing();
        draw(gamedata);
        EndDrawing();
    }
}

void Game::updateGameLogic()
{
    float delta = GetFrameTime();
    handleInputs(gamedata);

    gamedata.musicTimePlayed = GetMusicTimePlayed(gamedata.backgroundMusic);
    if (gamedata.musicTimePlayed >= GetMusicTimeLength(gamedata.backgroundMusic))
    {
        StopMusicStream(gamedata.backgroundMusic);
        PlayMusicStream(gamedata.backgroundMusic);
    }

    UpdateMusicStream(gamedata.backgroundMusic);

    float ballVel = (float)GetScreenWidth() * 0.35f;
    switch (gamedata.gameState)
    {
        case GameState::RUNNING:
            if (!IsMusicStreamPlaying(gamedata.backgroundMusic))
            {
                ResumeMusicStream(gamedata.backgroundMusic);
            }
            gamedata.ball.pos.x += gamedata.ball.vel.x * ballVel * delta;
            gamedata.ball.pos.y += gamedata.ball.vel.y * ballVel * delta;
            checkBallCollision(gamedata);
            break;

        case GameState::RESTART:
            resetData();
            gamedata.gameState = GameState::RUNNING;
            break;

        case GameState::STOPPED:
            if (IsMusicStreamPlaying(gamedata.backgroundMusic))
            {
                PauseMusicStream(gamedata.backgroundMusic);
            }
            break;

        case GameState::START:
            initData();
            gamedata.gameState = GameState::RUNNING;
            break;
    }
}

void Game::initData()
{
    float barWidth = (float)GetScreenWidth() * 0.025f;
    float barHeight = (float)GetScreenHeight() * 0.2f;
    float padding = (float)GetScreenWidth() * 0.1;

    gamedata.players = {
        Player{
            0,
            {},
            Rectangle{padding, (float) GetRandomValue(0, GetScreenHeight() - barHeight), barWidth, barHeight},
            DEFAULT_SPEED
        },
        Player{
            0,
            {},
            Rectangle{(float) GetScreenWidth() - padding - barWidth, (float) GetRandomValue(0, GetScreenHeight() - barHeight), barWidth, barHeight},
            DEFAULT_SPEED
        }
    };
    Vector2 vel = {(float)GetRandomValue(-100, 100) / 100, (float)GetRandomValue(-100, 100) / 100};
    gamedata.ball = Ball{
        Vector2{(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2},
        vel / Vector2Length(vel),
        0,
        (int)(((float)GetScreenWidth() / (float)GetScreenHeight()) * BALL_SIZE_FACTOR),
        false
    };
    gamedata.ball.directionIsLeft = gamedata.ball.vel.x < 0;
}

void Game::resetData()
{
    float barWidth = (float)GetScreenWidth() * 0.025f;
    float barHeight = (float)GetScreenHeight() * 0.2f;
    float padding = (float)GetScreenWidth() * 0.1;

    gamedata.players[0].items.clear();
    gamedata.players[0].status = ItemType::NONE;
    gamedata.players[0].bar.x = padding;
    gamedata.players[0].bar.y = (float) GetRandomValue(0, GetScreenHeight() - barHeight);
    gamedata.players[0].bar.height = barHeight;
    gamedata.players[0].bar.width = barWidth;
    gamedata.players[1].items.clear();
    gamedata.players[1].status = ItemType::NONE;
    gamedata.players[1].bar.x = (float) GetScreenWidth() - padding - barWidth;
    gamedata.players[1].bar.y = (float) GetRandomValue(0, GetScreenHeight() - barHeight);
    gamedata.players[1].bar.height = barHeight;
    gamedata.players[1].bar.width = barWidth;

    Vector2 vel = {(float)GetRandomValue(-100, 100) / 100, (float)GetRandomValue(-100, 100) / 100};
    gamedata.ball.pos = Vector2{(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};
    gamedata.ball.vel = vel / Vector2Length(vel),
    gamedata.ball.acc = 0;
    gamedata.ball.directionIsLeft = gamedata.ball.vel.x < 0;
    gamedata.ball.radius = (int)(((float)GetScreenWidth() / (float)GetScreenHeight()) * BALL_SIZE_FACTOR);
}


void Game::init()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong 2");
    SetExitKey(KEY_NULL);
    SetTargetFPS(TARGET_FPS);
    gamedata.gameState = GameState::START;
    gamedata.background = Background{};
    gamedata.musicTimePlayed = 0;
    InitAudioDevice();

    gamedata.backgroundMusic = LoadMusicStream("../resources/lied30.mp3");
    PlayMusicStream(gamedata.backgroundMusic);

}

void Game::shutdown()
{
    CloseWindow();
    UnloadMusicStream(gamedata.backgroundMusic);
    CloseAudioDevice();
}
