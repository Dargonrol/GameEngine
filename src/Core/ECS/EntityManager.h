#pragma once
#include <string>
#include <unordered_map>
#include <vector>

#include "Components.h"
#include "../Entity.h"
#include "../ErrorCodes.h"

namespace Pong::ECS
{
    class EntityManager
    {
    public:
        EntityManager() = default;
        ~EntityManager() = default;

        /**
         * Adds an entity to the Level. The Entity must have a unique identifier. If the identifier already exists, an error-code is returned and nothing get's added.
         * @param entity the entity to add
         * @param identifier a unique identifier to access the entity
         * @return error code, 0
         */
        ERROR add_entity(Entity entity, const std::string& identifier);
        ERROR remove_entity(const std::string& identifier);
        ERROR remove_entity(Entity* entity);
        Entity* get_entity(const std::string& identifier);

        template<typename C>
        Component* modifyEntityComponent(const std::string& identifier);

        int get_entity_cap() const;
        void change_entity_cap(int cap);

    private:
        int entity_cap_ = 100;
        std::vector<Entity> entities_;
        std::unordered_map<std::string, size_t> identifier_to_index_ = {};
        std::unordered_map<size_t, std::string> index_to_identifier = {};
        std::unordered_map<Entity*, size_t> reference_to_index = {};
        std::unordered_map<size_t, Entity*> index_to_reference = {};

        std::vector<Transform> transforms_;
        std::unordered_map<>
        std::vector<Velocity> velocities_;
    };
}

