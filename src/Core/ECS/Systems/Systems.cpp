#include "Systems.h"

#include "CollisionSystem.h"

namespace Core::ECS
{
    void Systems::update(float delta)
    {
        CollisionSystem::update(registry_, delta);
    }
}
