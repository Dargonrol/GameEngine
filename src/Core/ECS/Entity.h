#pragma once

namespace Pong::ECS
{
    using ID = size_t;

    struct Entity
    {
        explicit Entity(ID id) : id(id) { };
        ID id;
    };
}