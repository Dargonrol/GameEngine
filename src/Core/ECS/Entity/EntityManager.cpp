#include "EntityManager.h"

#include <utility>

namespace Core::ECS {
    EntityManager::EntityManager(const std::shared_ptr<Registry>& registry) : registry_(registry) {}

    ID EntityManager::RegisterEntity() const
    {
        WITH_REGISTRY_OR_RETURN(0)

        if (reg->entities.size() >= reg->entity_cap) return 0;
        ID id = 0;
        if (!reg->unused_ids.empty())
        {
            id = reg->unused_ids.top();
            reg->unused_ids.pop();
        } else
        {
            id = reg->entities.size() + 1;
        }
        reg->entities.emplace_back(id);
        reg->signatures.emplace_back(0);
        size_t index = reg->entities.size() - 1;
        reg->id_to_index.emplace(id, index);
        reg->index_to_id.emplace(index, id);
        return id;
    }

    ERROR EntityManager::UnregisterEntity(const ID id) const
    {
        WITH_REGISTRY_OR_RETURN(ERROR::REGISTRY_IS_NULLPTR)

        const auto it_del = reg->id_to_index.find(id);
        if (it_del == reg->id_to_index.end()) return ERROR::ENTITY_UNKNOWN_ID;

        const size_t size = reg->entities.size();
        const size_t last_index = size - 1;

        if (const size_t index = it_del->second; index != last_index)
        {
            // swap with last element
            std::swap(reg->entities[index], reg->entities.back());
            reg->id_to_index[reg->index_to_id[last_index]] = index;
            reg->index_to_id[index] = reg->index_to_id[last_index];
        }

        reg->id_to_index.erase(it_del);
        reg->index_to_id.erase(reg->index_to_id.find(last_index));

        if (id != size) reg->unused_ids.push(id);
        reg->entities.pop_back();
        reg->signatures.pop_back();

        return ERROR::NONE;
    }

    template<typename C>
    requires(std::is_base_of_v<Component, C>)
    ERROR EntityManager::AddEntityComponent(ID id, const C& component)
    {
        WITH_REGISTRY_OR_RETURN(ERROR::REGISTRY_IS_NULLPTR)

        if (!ID_exists(id))
            return ERROR::ENTITY_UNKNOWN_ID;
        auto& comp_arr = ComponentVector<C>::get(*reg);
        comp_arr.entity_indexes.emplace(id, comp_arr.components.size());
        comp_arr.components.emplace_back(component);
        comp_arr.entities.emplace_back(id);

        reg->signatures[reg->id_to_index[id]].set(get_component_type_index<C>(), true);

        return ERROR::NONE;
    }

    template<typename C>
    requires(std::is_base_of_v<Component, C>)
    ERROR EntityManager::AddEntityComponent(ID id)
    {
        return AddEntityComponent(id, C());
    }

    template<typename C>
    requires(std::is_base_of_v<Component, C>)
    ERROR EntityManager::RemoveEntityComponent(ID id)
    {
        WITH_REGISTRY_OR_RETURN(ERROR::REGISTRY_IS_NULLPTR)

        if (!ID_exists(id))
            return ERROR::ENTITY_UNKNOWN_ID;
        ComponentArray<C>& comp_arr = ComponentVector<C>::get(*reg);
        auto it = comp_arr.entity_indexes.find(id);
        if (it == comp_arr.entity_indexes.end())
            return ERROR::COMPONENT_UNKNOWN;

        Index index = it->second;
        size_t size = comp_arr.components.size();
        if (index != size - 1)
        {
            std::swap(comp_arr.components[index], comp_arr.components[size - 1]);
            std::swap(comp_arr.entities[index], comp_arr.entities[size - 1]);
            comp_arr.entity_indexes[comp_arr.entities[index]] = index;
        }
        comp_arr.entities.pop_back();
        comp_arr.components.pop_back();
        comp_arr.entity_indexes.erase(it);

        reg->signatures[reg->id_to_index[id]].set(get_component_type_index<C>(), false);

        return ERROR::NONE;
    }

    template<typename C>
    requires(std::is_base_of_v<Component, C>)
    Component *EntityManager::GetEntityComponent(ID id)
    {
        WITH_REGISTRY_OR_RETURN(nullptr)

        if (!ID_exists(id))
            return nullptr;

        auto comp_arr = ComponentVector<C>::get(*reg);

        auto it = comp_arr.entity_indexes.find(id);
        if (it == comp_arr.entity_indexes.end())
            return nullptr;

        return &comp_arr.components[it->second];
    }

    int EntityManager::GetEntityCap() const
    {
        WITH_REGISTRY_OR_RETURN(0)
        return reg->entity_cap;
    }

    void EntityManager::ChangeEntityCap(const int cap) const
    {
        WITH_REGISTRY_OR_RETURN()
        reg->entity_cap = cap;
    }

    bool EntityManager::ID_exists(const ID id) const
    {
        WITH_REGISTRY_OR_RETURN(false)
        return reg->id_to_index.contains(id);
    }
}