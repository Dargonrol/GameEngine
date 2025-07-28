#include "Background.h"

#include <cmath>

#include "Graphics.h"

typedef struct Star {
    float x, y, z;
} Star;

Star stars[5000];

void InitStars() {
    for (int i = 0; i < 5000; i++) {
        stars[i].x = ((float)rand() / RAND_MAX - 0.5f) * 2.0f;
        stars[i].y = ((float)rand() / RAND_MAX - 0.5f) * 2.0f;
        stars[i].z = ((float)rand() / RAND_MAX) + 0.5f;
    }
}

Background::Background()
{
    InitStars();
}

void drawTunnelLines(float time)
{
    Vector2 center = { (float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f };

    for (int i = 0; i < 500; i++) {
        stars[i].z -= GetFrameTime() * 0.5f; // Geschwindigkeit

        if (stars[i].z <= 0.01f) {
            // Star reset
            stars[i].x = ((float)rand() / RAND_MAX - 0.5f) * 2.0f;
            stars[i].y = ((float)rand() / RAND_MAX - 0.5f) * 2.0f;
            stars[i].z = 1.0f;
        }

        // Projektion auf 2D
        float f = 300.0f / stars[i].z;
        float sx = stars[i].x * f + center.x;
        float sy = stars[i].y * f + center.y;

        // optional: Trail
        float px = stars[i].x * (f - 10) + center.x;
        float py = stars[i].y * (f - 10) + center.y;

        // Linienflug
        DrawLine(sx, sy, px, py, WHITE);
    }
}


void Background::draw(float time)
{
    Vector2 projected[8];
    for (int i = 0; i < 8; i++) {
        Vector3 rotated = rotateY(cube[i], time);
        rotated = rotateX(rotated, time);
        projected[i] = project(rotated, 4.0f);
    }

    for (auto & edge : edges) {
        Vector2 a = projected[edge[0]];
        Vector2 b = projected[edge[1]];
        DrawLineV(a, b, WHITE);
    }
    drawTunnelLines(time);
}