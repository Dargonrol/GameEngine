#pragma once
#include "../Registry.h"

namespace Pong::ECS
{
    struct CollisionSystem
    {
        static void update(Registry* registry, float delta);
    };
}
