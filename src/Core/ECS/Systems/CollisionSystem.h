#pragma once
#include "../Registry.h"

namespace Core::ECS
{
    struct CollisionSystem
    {
        static void update(Registry* registry, float delta);
    };
}
