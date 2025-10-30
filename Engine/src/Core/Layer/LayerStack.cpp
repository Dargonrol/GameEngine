#include "LayerStack.h"

#include <utility>

namespace Core {
    LayerStack::LayerStack() {}

    LayerStack::~LayerStack() {}

    template<typename T> requires (std::is_base_of_v<Layer, T>)
    void LayerStack::PushLayer()
    {
        if (HasLayer<T>()) { return; }

        auto layer = std::make_unique<T>();
        layer->ID = layerStack_.size();
        layerStack_.emplace_back(std::move(layer));
    }

    void LayerStack::PopLayer()
    {
        const auto& layer = layerStack_.back();

        layer->CollectUnregisterCommands();

        dispatch_commands_in_queue(layer.get());

        layerStack_.pop_back();
    }

    template<typename T> requires (std::is_base_of_v<Layer, T>)
    Result<void> LayerStack::InsertLayer(const size_t index)
    {
        if (index > layerStack_.size()) { return {ERROR::INDEX_OUT_OF_RANGE}; }
        if (HasLayer<T>()) { return {ERROR::ALREADY_EXISTS}; }

        // issue UnRegister Commands to renderer with all entities with old IDs
        // insert layer and update every ID
        // issue Register commands to renderer with all entities with new IDs

        for (size_t i = index; i < layerStack_.size(); ++i)
        {
            layerStack_[i]->CollectUnregisterCommands();
            dispatch_commands_in_queue(layerStack_[i].get());
        }

        auto layer = std::make_unique<T>();
        layer->ID = index;
        layerStack_.insert(layerStack_.begin() + index, std::move(layer));

        for (size_t i = index + 1; i < layerStack_.size(); ++i)
        {
            layerStack_[i]->ID += 1;
            layerStack_[i]->CollectRegisterCommands();
            dispatch_commands_in_queue(layerStack_[i].get());
        }

        return {ERROR::NONE};
    }

    template<typename T> requires (std::is_base_of_v<Layer, T>)
    void LayerStack::RemoveLayer(size_t index)
    {
        if (index >= layerStack_.size()) { return; }

        layerStack_[index]->CollectUnregisterCommands();
        dispatch_commands_in_queue(layerStack_[index].get());
        layerStack_.erase(layerStack_.begin() + index);

        for (size_t i = index; i < layerStack_.size(); ++i)
        {
            layerStack_[i]->CollectUnregisterCommands();
            dispatch_commands_in_queue(layerStack_[i].get());
            layerStack_[i]->ID = i;
            layerStack_[i]->CollectRegisterCommands();
            dispatch_commands_in_queue(layerStack_[i].get());
        }
    }

    template<typename T> requires (std::is_base_of_v<Layer, T>)
    void LayerStack::SuspendLayer() const
    {
        for (const auto& layer : layerStack_)
        {
            if (typeid(*layer) == typeid(T))
            {
                std::queue<RenderData> empty;
                std::swap(layer->GetCommandQueue(), empty);
                layer->suspend();
                dispatch_commands_in_queue(layer.get());
                return;
            }
        }
    }

    template<typename T> requires (std::is_base_of_v<Layer, T>)
    void LayerStack::ActivateLayer() const
    {
        for (const auto& layer : layerStack_)
        {
            if (typeid(*layer) == typeid(T))
            {
                layer->activate();
                dispatch_commands_in_queue(layer.get());
                return;
            }

        }
    }

    void LayerStack::update(float delta) const
    {
        for (const std::unique_ptr<Layer>& layer: layerStack_)
        {
            if (layer->IsSuspended())
                continue;

            layer->update(delta);
            dispatch_commands_in_queue(layer.get());
        }
    }

    template<typename T> requires (std::is_base_of_v<Layer, T>)
    bool LayerStack::HasLayer() const
    {
        for (const auto& layer : layerStack_)
        {
            if (typeid(*layer) == typeid(T))
                return true;
        }
        return false;
    }

    void LayerStack::dispatch_commands_in_queue(Layer *layer) const
    {
        const auto renderer = renderer_.lock(); \
        if (!renderer) return;

        std::queue<RenderData>& queue = layer->GetCommandQueue();
        while (!queue.empty())
        {
            RenderData data = queue.front();
            queue.pop();

            data.ID.layerID = layer->ID;
            switch (data.command)
            {
                case OBJ_Command::REGISTER:
                    renderer->RegisterRenderable(data);
                    break;
                case OBJ_Command::UNREGISTER:
                    renderer->UnRegisterRenderable(data);
                    break;
                case OBJ_Command::UPDATE:
                    renderer->UpdateRenderable(data);
                    break;
            }
        }
    }

    void LayerStack::SetRenderer(std::weak_ptr<Renderer::IRenderer> renderer)
    {
        renderer_ = std::move(renderer);
    }


}