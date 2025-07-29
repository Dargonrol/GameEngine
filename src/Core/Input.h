#pragma once

#include "../Game.h"
#include "Constants.h"

using namespace Constants;

inline void handleInputs(GameData& gamedata)
{
    float delta = GetFrameTime();
    if (IsKeyPressed(KEY_R)) { gamedata.gameState = GameState::RESTART; }
    if ((IsKeyPressed(KEY_ENTER) && gamedata.gameState == GameState::STOPPED)) { gamedata.gameState = GameState::RUNNING; }
    if (IsKeyPressed(KEY_ESCAPE))
    {
        if (gamedata.gameState == GameState::STOPPED)
            gamedata.gameState = GameState::RUNNING;
        else
            gamedata.gameState = GameState::STOPPED;
    }

    if (gamedata.gameState == GameState::RUNNING)
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
}