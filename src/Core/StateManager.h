#ifndef STATEMANAGER_H
#define STATEMANAGER_H
#include <memory>
#include <string>
#include <unordered_map>

#include "Level/Level.h"

namespace Pong {

class StateManager { // Singleton
public:
    Level* get_current_level() const;
    int change_level(const std::string& identifier);

    /**
     * Registers a new Level. Checks if the identifier does already exist. If yes returns a non zero value.
     * @param level the level to add
     * @param identifier identifier to reference the level
     * @return Error Code
     */
    int register_level(Level* level, const std::string& identifier);

private:
    std::unordered_map<std::string, std::unique_ptr<Level>> _level_map = {};
    std::string _current_level = {};


    // Singleton
public:
    StateManager(const StateManager& obj) = delete;

    static StateManager* get()
    {
        if (_state_manager_ptr == nullptr)
        {
            _state_manager_ptr = new StateManager();
        }
        return _state_manager_ptr;
    }

private:
    static StateManager* _state_manager_ptr;
    StateManager() = default;
};

} // Pong

#endif //STATEMANAGER_H
