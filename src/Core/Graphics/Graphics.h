#pragma once
#include "raylib.h"

Vector2 project(Vector3 point, float fov);

Vector3 rotateY(Vector3 p, float angle);
Vector3 rotateX(Vector3 p, float angle);