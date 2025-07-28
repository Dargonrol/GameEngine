#include "Graphics.h"

#include <cmath>
#include <raylib.h>

Vector2 project(Vector3 point, float fov)
{
    float scale = fov / (fov + point.z);
    return (Vector2){
        (float) GetScreenWidth() / 2 + point.x * scale * 100,
        (float) GetScreenHeight() / 2 - point.y * scale * 100
    };
}

Vector3 rotateY(Vector3 p, float angle)
{
    float s = sinf(angle);
    float c = cosf(angle);
    return (Vector3){
        p.x * c - p.z * s,
        p.y,
        p.x * s + p.z * c
    };
}

Vector3 rotateX(Vector3 p, float angle)
{
    float s = sinf(angle);
    float c = cosf(angle);
    return (Vector3){
        p.x,
        p.y * c - p.z * s,
        p.y * s + p.z * c
    };
}