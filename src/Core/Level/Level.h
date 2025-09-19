#ifndef LEVEL_H
#define LEVEL_H
#include <functional>
#include <memory>
#include <string>

#include "../ECS/EntityManager.h"

namespace Pong {

class Level {
public:
    explicit Level(std::string name);
    virtual ~Level() = default;

    virtual void init() = 0;
    virtual void shutdown() = 0;

    virtual bool is_end_condition_met() = 0;

    virtual void update(float delta) = 0;
    virtual void render() = 0;

    ECS::EntityManager* getEntityManger();


public:
    const std::string name;
    std::function<void(Level&)> level_start_callback = nullptr;
    std::function<void(Level&)> level_end_callback = nullptr;

private:
    std::unique_ptr<ECS::EntityManager> entity_manager_;
};

} // Pong

#endif //LEVEL_H
