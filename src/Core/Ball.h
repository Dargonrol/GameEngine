#pragma once
#include "raylib.h"

typedef struct Ball {
    Vector2 pos;
    Vector2 vel;
    float acc;
    int radius;
    bool directionIsLeft;
} Ball;
