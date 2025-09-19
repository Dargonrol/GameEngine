#include "EntityManager.h"

#include <utility>

namespace Pong::ECS {
    EntityManager::EntityManager()
    = default;

    ID EntityManager::add_entity()
    {
        if (registry_.entities.size() >= registry_.entity_cap) return 0;
        ID id = 0;
        if (!registry_.unused_ids.empty())
        {
            id = registry_.unused_ids.top();
            registry_.unused_ids.pop();
        } else
        {
            id = registry_.entities.size() + 1;
        }
        registry_.entities.emplace_back(id);
        registry_.signatures.emplace_back(0);
        size_t index = registry_.entities.size() - 1;
        registry_.id_to_index.emplace(id, index);
        registry_.index_to_id.emplace(index, id);
        return id;
    }

    ERROR EntityManager::remove_entity(ID id)
    {
        auto it_del = registry_.id_to_index.find(id);
        if (it_del == registry_.id_to_index.end()) return ERROR::ENTITY_UNKNOWN_ID;

        const size_t size = registry_.entities.size();
        const size_t last_index = size - 1;

        if (const size_t index = it_del->second; index != last_index)
        {
            // swap with last element
            std::swap(registry_.entities[index], registry_.entities.back());
            registry_.id_to_index[registry_.index_to_id[last_index]] = index;
            registry_.index_to_id[index] = registry_.index_to_id[last_index];
        }

        registry_.id_to_index.erase(it_del);
        registry_.index_to_id.erase(registry_.index_to_id.find(last_index));

        if (id != size) registry_.unused_ids.push(id);
        registry_.entities.pop_back();
        registry_.signatures.pop_back();

        return ERROR::NONE;
    }

    template<typename C>
    ERROR EntityManager::add_entity_component(ID id, const C& component)
    {
        if (ID_exists(id))
            return ERROR::ENTITY_UNKNOWN_ID;
        auto& comp_arr = ComponentVector<C>::get(registry_);
        comp_arr.entity_indexes.emplace(id, comp_arr.components.size());
        comp_arr.components.emplace_back(component);
        comp_arr.entities.emplace_back(id);

        registry_.signatures[registry_.id_to_index[id]].set(get_component_type_index<C>(), true);

        return ERROR::NONE;
    }

    template<typename C>
    ERROR EntityManager::add_entity_component(ID id)
    {
        return add_entity_component(id, C());
    }

    template<typename C>
    ERROR EntityManager::remove_entity_component(ID id)
    {
        if (!ID_exists(id))
            return ERROR::ENTITY_UNKNOWN_ID;
        ComponentArray<C>& comp_arr = ComponentVector<C>::get(registry_);
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

        registry_.signatures[registry_.id_to_index[id]].set(get_component_type_index<C>(), false);

        return ERROR::NONE;
    }

    template<typename C>
    Component *EntityManager::get_entity_component(ID id)
    {
        if (!ID_exists(id))
            return nullptr;

        auto comp_arr = ComponentVector<C>::get(registry_);

        auto it = comp_arr.entity_indexes.find(id);
        if (it == comp_arr.entity_indexes.end())
            return nullptr;

        return comp_arr.components[it->second];
    }

    int EntityManager::get_entity_cap() const
    {
        return registry_.entity_cap;
    }

    void EntityManager::change_entity_cap(const int cap)
    {
        registry_.entity_cap = cap;
    }

    bool EntityManager::ID_exists(const ID id) const
    {
        return registry_.id_to_index.contains(id);
    }

    Registry *EntityManager::get_registry()
    {
        return &registry_;
    }

}