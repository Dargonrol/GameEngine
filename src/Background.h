#pragma once
#include <array>

#include "raylib.h"


class Background
{
public:
    Background();
    ~Background() = default;
    void draw(float time);

private:
    std::array<Vector3, 8> cube =
        {
            Vector3{-1, -1, -1}, Vector3{ 1, -1, -1}, Vector3{ 1, 1, -1}, Vector3{-1, 1, -1}, // back face
            Vector3{-1, -1,  1}, Vector3{ 1, -1,  1}, Vector3{ 1, 1,  1}, Vector3{-1, 1,  1} // front face
        };

    int edges[12][2] = {
        {0,1}, {1,2}, {2,3}, {3,0}, // back
        {4,5}, {5,6}, {6,7}, {7,4}, // front
        {0,4}, {1,5}, {2,6}, {3,7}  // sides
    };
};
