#pragma once
#include <vector>

#include "Items.h"
#include "raylib.h"

typedef struct Player
{
    int score;
    std::vector<Item> items;
    Rectangle bar;
    float speed;
} Player;
