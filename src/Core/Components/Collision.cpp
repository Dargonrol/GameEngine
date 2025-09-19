#pragma once

#include "Collision.h"
namespace Pong
{
    void checkBallCollision(GameData& gamedata)
    {
        Ball& ball = gamedata.ball;
        Rectangle& bar1 = gamedata.players[0].bar;
        Rectangle& bar2 = gamedata.players[1].bar;

        // detect if ball scores
        if (ball.pos.x > GetScreenWidth())
        {
            gamedata.players[0].score += 1;
            gamedata.gameState = GameState::RESTART;
            return;
        }
        if (ball.pos.x < 0)
        {
            gamedata.players[1].score += 1;
            gamedata.gameState = GameState::RESTART;
            return;
        }

        // check upper and lower bound ball collision
        if (ball.pos.y <= 0 + ball.radius || ball.pos.y >= GetScreenHeight() - ball.radius)
        {
            ball.vel.y *= -1;
            return;
        }

        int padding = 10;
        // check left player collision with ball
        if (
            ball.directionIsLeft &&
            ball.pos.x - ball.radius <= bar1.x + bar1.width + padding &&
            ball.pos.x - ball.radius >= bar1.x - padding &&
            ball.pos.y + ball.radius >= bar1.y - padding &&
            ball.pos.y - ball.radius <= bar1.y + bar1.height + padding
            )
        {
            ball.vel.x *= -1;
            ball.directionIsLeft = false;
            return;
        }

        // check right player collision with ball
        if (
            !ball.directionIsLeft &&
            ball.pos.x + ball.radius >= bar2.x - padding &&
            ball.pos.x + ball.radius <= bar2.x + bar2.width + padding &&
            ball.pos.y - ball.radius <= bar2.y + bar2.height + padding &&
            ball.pos.y + ball.radius >= bar2.y - padding
            )
        {
            ball.vel.x *= -1;
            ball.directionIsLeft = true;
            return;
        }
    }
}