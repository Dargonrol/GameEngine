#pragma once

#include "Components.h"
#include "Registry.h"
#include "Entity.h"
#include "../ErrorCodes.h"

namespace Core::ECS
{
    class EntityManager
    {
    public:
        EntityManager();
        ~EntityManager() = default;

        /**
         * Adds a new empty Entity. Return 0 if entity cap is reached.
         * @return entity ID
         */
        ID add_entity();
        ERROR remove_entity(ID id);

        template<typename C>
        ERROR add_entity_component(ID id, const C& component);
        template<typename C>
        ERROR add_entity_component(ID id);

        template<typename C>
        ERROR remove_entity_component(ID id);

        template<typename C>
        Component* get_entity_component(ID id);

        int get_entity_cap() const;
        void change_entity_cap(int cap);

        Registry* get_registry();

    private:
        bool ID_exists(ID id) const;

    private:
        Registry registry_ = {};
    };
}

