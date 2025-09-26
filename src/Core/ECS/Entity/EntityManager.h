#pragma once

#include <memory>

#include "../Components/Components.h"
#include "../Registry.h"
#include "Entity.h"
#include "../../ErrorCodes.h"

namespace Core::ECS
{
    class EntityManager
    {
    public:
        EntityManager(const std::shared_ptr<Registry>& registry);
        ~EntityManager() = default;

        /**
         * Adds a new empty Entity. Return 0 if entity cap is reached.
         * @return entity ID
         */
        ID RegisterEntity() const;
        ERROR UnregisterEntity(ID id) const;

        template<typename C>
        requires(std::is_base_of_v<Component, C>)
        ERROR AddEntityComponent(ID id, const C& component);
        template<typename C>
        requires(std::is_base_of_v<Component, C>)
        ERROR AddEntityComponent(ID id);

        template<typename C>
        requires(std::is_base_of_v<Component, C>)
        ERROR RemoveEntityComponent(ID id);

        template<typename C>
        requires(std::is_base_of_v<Component, C>)
        Component* GetEntityComponent(ID id);

        [[nodiscard]] int GetEntityCap() const;
        void ChangeEntityCap(int cap) const;

    private:
        [[nodiscard]] bool ID_exists(ID id) const;

    private:
        std::weak_ptr<Registry> registry_;
    };
}

