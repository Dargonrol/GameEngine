#pragma once
#include <string>
#include <unordered_map>


namespace Core::ECS
{
    using ComponentType = size_t;
    inline ComponentType next_component_type = 0;

    struct Component
    {
        Component() = delete;
    };

    template<typename C>
    ComponentType get_component_type_index() {
        static ComponentType type_index = next_component_type++;
        return type_index;
    }
}
