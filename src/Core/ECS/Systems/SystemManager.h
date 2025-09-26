#pragma once
#include <memory>

#include "../Registry.h"

namespace Core::ECS
{
    class SystemManager
    {
    public:
        explicit SystemManager(const std::shared_ptr<Registry> &registry) : registry_(registry) {}
        ~SystemManager() = default;

        void update(float delta);
        void render();

    private:
        std::weak_ptr<Registry> registry_;
    };

}
