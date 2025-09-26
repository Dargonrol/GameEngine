#pragma once

namespace Core::ECS
{
    class System
    {
    public:
        System() = default;
        virtual ~System() = 0;

        virtual void update(float delta) = 0;
        virtual void render() = 0;
    };
}