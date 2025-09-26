#ifndef STATEMANAGER_H
#define STATEMANAGER_H
#include <memory>
#include <string>
#include <unordered_map>

#include "Level/Level.h"

namespace Core {

class StateManager { // Singleton
public:



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
