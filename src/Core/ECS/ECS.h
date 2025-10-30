#pragma once
#include <memory>
#include <queue>

#include "Entity/EntityManager.h"
#include "Systems/SystemManager.h"


namespace Core::ECS
{
class ECS {

public:
    explicit ECS() :
    registry_(std::make_unique<Registry>()),
    entity_manager_(std::make_unique<EntityManager>(registry_)),
    system_manager_(std::make_unique<SystemManager>(registry_))
    {

    }

    void SetRenderDataCommandQueue(std::queue<RenderData>* renderDataCommandQueue) const
    {
        entity_manager_->SetRenderDataCommandQueue(renderDataCommandQueue);
    }

    void UnregisterAllRenderablesCommandIssue() const
    {
        entity_manager_->UnregisterAllRenderablesCommandIssue();
    }
    void RegisterAllRenderablesCommandIssue() const
    {
        entity_manager_->RegisterAllRenderablesCommandIssue();
    }


private:
    std::shared_ptr<Registry> registry_;
    std::unique_ptr<EntityManager> entity_manager_;
    std::unique_ptr<SystemManager> system_manager_;
};
}