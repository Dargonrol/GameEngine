#include "EntityManager.h"

#include <utility>

namespace Pong::ECS {
    ERROR EntityManager::add_entity(Entity entity, const std::string& identifier)
    {
        size_t size = entities_.size();
        if (size >= entity_cap_) return ERROR::ENTITY_CAP_REACHED;
        auto it = identifier_to_index_.find(identifier);
        if (it != identifier_to_index_.end()) return ERROR::ENTITY_UNKNOWN_ID;
        Entity* entity_ref = &entities_.emplace_back(entity);
        size_t index = size - 1;
        identifier_to_index_.emplace(identifier, size - 1);
        reference_to_index.emplace(entity_ref, size - 1);
        index_to_identifier.emplace(index, identifier);
        index_to_reference.emplace(index, entity_ref);
        return ERROR::NONE;
    }

    ERROR EntityManager::remove_entity(Entity *entity)
    {
        auto it_RtI = reference_to_index.find(entity);
        if (it_RtI == reference_to_index.end()) return ERROR::ENTITY_UNKNOWN_ID;

        size_t index = it_RtI->second;
        size_t last_index = entities_.size() - 1;

        if (index != last_index)
        {
            // Swap last element with the one to delete
            std::swap(entities_[index], entities_[last_index]);

            Entity* moved_entity = &entities_[index];
            auto it_moved_ref = reference_to_index.find(moved_entity);
            it_moved_ref->second = index;

            auto it_moved_id = identifier_to_index_.find(index_to_identifier[last_index]);
            it_moved_id->second = index;

            index_to_reference[index] = moved_entity;
            index_to_identifier[index] = index_to_identifier[last_index];
        }

        Entity* last_entity = &entities_[last_index];
        auto it_last_ref = reference_to_index.find(last_entity);
        reference_to_index.erase(it_last_ref);

        std::string last_identifier = index_to_identifier[last_index];
        auto it_last_id = identifier_to_index_.find(last_identifier);
        identifier_to_index_.erase(it_last_id);

        index_to_identifier.erase(last_index);
        index_to_reference.erase(last_index);

        entities_.pop_back();

        return ERROR::NONE;
    }


    ERROR EntityManager::remove_entity(const std::string &identifier)
    {
        auto it = identifier_to_index_.find(identifier);
        if (it == identifier_to_index_.end()) return ERROR::ENTITY_UNKNOWN_ID;
        return remove_entity(index_to_reference[it->second]);
    }


    Entity* EntityManager::get_entity(const std::string& identifier)
    {
        auto it = identifier_to_index_.find(identifier);
        if (it == identifier_to_index_.end()) return nullptr;
        return &entities_[it->second];
    }

    int EntityManager::get_entity_cap() const
    {
        return entity_cap_;
    }

    void EntityManager::change_entity_cap(int cap)
    {
        entity_cap_ = cap;
    }

    template<typename C>
    Component *EntityManager::modifyEntityComponent(const std::string &identifier)
    {

    }

}