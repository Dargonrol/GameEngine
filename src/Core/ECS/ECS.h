#pragma once
#include <memory>
#include <queue>

#include "../Layer/Layer.h"
#include "Entity/EntityManager.h"
#include "Systems/SystemManager.h"


namespace Core::ECS
{
class ECS {

public:
    void SetRenderDataCommandQueue(const std::queue<RenderData>& renderDataCommandQueue) const
    {
        entity_manager_->SetRenderDataCommandQueue(renderDataCommandQueue);
    }

private:
    std::unique_ptr<EntityManager> entity_manager_;
    std::unique_ptr<SystemManager> system_manager_;
    std::shared_ptr<Registry> registry_;
};
}