#include "Draw.h"
#include "../Constants.h"
#include <string>

using namespace Constants;

void draw(GameData& gamedata)
{
    ClearBackground(Color{0, 0, 0, 0xFF});
    gamedata.background.draw(GetTime());
    switch (gamedata.gameState)
    {
        case GameState::RUNNING:
            drawGameScreen(gamedata);
            break;

        case GameState::STOPPED:
            drawGameScreen(gamedata);
            drawPauseScreen(gamedata);
            break;

        case GameState::RESTART:
            break;

        case GameState::START:
            break;
    }
}


void drawPauseScreen(GameData& gamedata)
{
    float padding = 0.1;
    DrawRectangle(
        GetScreenWidth() * padding,
        GetScreenHeight() * padding,
        GetScreenWidth() - (GetScreenWidth() * padding) * 2,
        GetScreenHeight() - (GetScreenHeight() * padding) * 2,
        Color{60, 60, 60, 200}
        );
    const char* pauseText = "Game Paused";
    DrawText(pauseText, (GetScreenWidth() - MeasureText(pauseText, H1_FONT_SIZE)) / 2, GetScreenHeight() / 2 - GetScreenHeight() * 0.2, H1_FONT_SIZE, WHITE);
}

void drawGameScreen(GameData& gamedata)
{
    for (Player &player: gamedata.players)
    {
        DrawRectangleRec(player.bar, Color{0xFF, 0xFF, 0xFF, 0xFF});
    }
    int score1 = gamedata.players[0].score;
    int score2 = gamedata.players[1].score;
    std::string player1Score = "Player 1: " + std::to_string(score1);
    std::string player2Score = "Player 2: " + std::to_string(score2);
    DrawText(player1Score.c_str(), 20, 20, NORMAL_FONT_SIZE, score1 > score2 ? ORANGE : WHITE);
    DrawText(player2Score.c_str(), GetScreenWidth() - 20 - MeasureText(player2Score.c_str(), NORMAL_FONT_SIZE), 20, NORMAL_FONT_SIZE, score1 < score2 ? ORANGE : WHITE);

    DrawCircle(gamedata.ball.pos.x, gamedata.ball.pos.y, gamedata.ball.radius, RED);
}