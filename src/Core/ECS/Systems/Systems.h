#pragma once
#include "../Registry.h"

namespace Pong::ECS
{
    class Systems
    {
    public:
        explicit Systems(Registry* registry) : registry_(registry) {}
        ~Systems() = default;

        void update(float delta);
        void render();

    private:
        Registry* registry_;
    };

}
