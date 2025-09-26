#pragma once
#include <memory>

#include "Entity/EntityManager.h"
#include "Systems/SystemManager.h"


namespace Core::ECS {

class ECS {


private:
    std::unique_ptr<EntityManager> entity_manager_;
    std::unique_ptr<SystemManager> system_manager_;
    std::shared_ptr<Registry> registry_;
};