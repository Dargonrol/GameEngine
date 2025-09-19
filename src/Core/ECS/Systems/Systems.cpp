#include "Systems.h"

#include "CollisionSystem.h"

namespace Pong::ECS
{
    void Systems::update(float delta)
    {
        CollisionSystem::update(registry_, delta);
    }
}
