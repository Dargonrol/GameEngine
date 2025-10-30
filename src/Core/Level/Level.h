#pragma once

#include <functional>
#include <memory>
#include <string>
#include <utility>

#include "../ECS/ECS.h"

namespace Core {

class Level {
public:
    explicit Level(std::string name) : name(std::move(name))
    {
        ecs_ = std::make_unique<ECS::ECS>();
    }
    virtual ~Level() = default;

    virtual void Init() = 0;
    virtual void Shutdown() = 0;

    virtual bool Is_end_condition_met() = 0;

    virtual void Update(float delta) = 0;

    void SetRenderDataCommandQueue(std::queue<RenderData>* renderDataCommandQueue) const
    {
        ecs_->SetRenderDataCommandQueue(renderDataCommandQueue);
    }

    void UnregisterAllRenderablesCommandIssue() const
    {
        ecs_->UnregisterAllRenderablesCommandIssue();
    }

    void RegisterAllRenderablesCommandIssue() const
    {
        ecs_->RegisterAllRenderablesCommandIssue();
    }


public:
    const std::string name;
    std::function<void(Level&)> level_start_callback = nullptr;
    std::function<void(Level&)> level_end_callback = nullptr;

private:
    std::unique_ptr<ECS::ECS> ecs_;
};

}