#pragma once

#include <bitset>
#include <stack>
#include <unordered_map>
#include <vector>

#include "Components.h"
#include "Entity.h"

namespace Pong::ECS {
    using Index = size_t;
    using Signature = std::bitset<64>;

    template<typename C>
    struct ComponentArray
    {
        std::vector<C> components;
        std::vector<Entity> entities;
        std::unordered_map<ID, Index> entity_indexes;
    };

    struct Registry {
        int entity_cap = 10000;
        std::vector<Entity> entities;
        std::vector<Signature> signatures;
        std::stack<ID> unused_ids;

        std::unordered_map<ID, Index> id_to_index;
        std::unordered_map<Index, ID> index_to_id;

        ComponentArray<Transform> transforms;
        ComponentArray<Velocity> velocities;
    };

    template<typename C>
    struct ComponentVector
    {
        static ComponentArray<C>& get(Registry* registry)
        {
            static_assert(sizeof(C) == 0, "ComponentVector not specialized for this type!");
            return nullptr;
        }
    };

    template<>
    struct ComponentVector<Transform>
    {
        static ComponentArray<Transform>& get(Registry& reg) { return reg.transforms; }
    };

}
