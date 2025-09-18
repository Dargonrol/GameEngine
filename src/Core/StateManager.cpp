//
// Created by Dargonrol on 17.09.2025.
//

#include "StateManager.h"

namespace Pong {
    int StateManager::register_level(Level* level, const std::string& identifier)
    {
        if (_level_map.contains(identifier)) return -1;
        _level_map.emplace(
            identifier,
            level
            );
        return 0;
    }

    Level* StateManager::get_current_level() const
    {
        auto it = _level_map.find(_current_level);
        if (it == _level_map.end()) return nullptr;
        return it->second.get();
    }

    int StateManager::change_level(const std::string& identifier)
    {
        auto it = _level_map.find(identifier);
        if (it == _level_map.end()) return -1;
        _current_level = it->first;
        return 0;
    }



} // Pong