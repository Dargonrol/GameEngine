//
// Created by Dargonrol on 17.09.2025.
//

#include "Level.h"

#include <utility>

namespace Core {
    Level::Level(std::string  name) : name(std::move(name))
    {
        entity_manager_ = std::make_unique<ECS::EntityManager>();
    }



} // Pong