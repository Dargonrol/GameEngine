#include "LayerStack.h"

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
        const auto renderer = renderer_.lock();
        if (!renderer) return;

        auto& layer = layerStack_.back();

        layer->UnregisterAllRenderablesCommandIssue();

        for (const auto& data: layer.get()->GetCommandQueue())
        {
            renderer->UnRegisterRenderable(data);
        }
        layerStack_.pop_back();
    }

    template<typename T> requires (std::is_base_of_v<Layer, T>)
    void LayerStack::InsertLayer(const size_t index)
    {
        if (index > layerStack_.size()) { return; }
        if (HasLayer<T>()) { return; }

        const auto renderer = renderer_.lock(); \
        if (!renderer) return;

        // issue UnRegister Commands to renderer with all entities with old IDs
        // insert layer and update every ID
        // issue Register commands to renderer with all entities with new IDs

        for (size_t i = index; i < layerStack_.size(); ++i)
        {
            layerStack_[i]->UnregisterAllRenderablesCommandIssue();
            for (const auto& data: layerStack_[i].get()->GetCommandQueue())
            {
                renderer->UnRegisterRenderable(data);
            }
        }

        auto layer = std::make_unique<T>();
        layer->ID = index;
        layerStack_.insert(layerStack_.begin() + index, std::move(layer));

        for (size_t i = index + 1; i < layerStack_.size(); ++i)
        {
            layerStack_[i]->ID += 1;
            layerStack_[i]->RegisterAllRenderablesCommandIssue();
            for (const auto& data: layerStack_[i].get()->GetCommandQueue())
            {
                renderer->RegisterRenderable(data);
            }
        }

    }

    template<typename T> requires (std::is_base_of_v<Layer, T>)
    void LayerStack::RemoveLayer(size_t index)
    {
        if (index >= layerStack_.size()) { return; }

        const auto renderer = renderer_.lock(); \
        if (!renderer) return;

        layerStack_[index]->UnregisterAllRenderablesCommandIssue();
        for (const auto& data: layerStack_[index].get()->GetCommandQueue())
        {
            renderer->UnRegisterRenderable(data);
        }
        layerStack_.erase(layerStack_.begin() + index);

        for (size_t i = index; i < layerStack_.size(); ++i)
        {
            layerStack_[i]->UnregisterAllRenderablesCommandIssue();
            for (const auto& data: layerStack_[i].get()->GetCommandQueue())
            {
                renderer->UnRegisterRenderable(data);
            }
            layerStack_[i]->ID = i;
            layerStack_[i]->RegisterAllRenderablesCommandIssue();
            for (const auto& data: layerStack_[i].get()->GetCommandQueue())
            {
                renderer->RegisterRenderable(data);
            }
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
                UnRegisterRenderable(layer);
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
                RegisterRenderable(layer);
                return;
            }

        }
    }

    void LayerStack::update() const
    {
        const auto renderer = renderer_.lock(); \
        if (!renderer) return;

        for (const std::unique_ptr<Layer>& layer: layerStack_)
        {
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
    }

    template<typename T> requires (std::is_base_of_v<Layer, T>)
    bool LayerStack::HasLayer() const
    {
        for (const auto& layer : layerStack_)
        {
            if (typeid(*layer) == typeid(T))
            {
                return true;
            }
        }
        return false;
    }

    void LayerStack::UnRegisterRenderable(const std::unique_ptr<Layer> &layer) const
    {
        const auto renderer = renderer_.lock(); \
        if (!renderer) return;

        for (const auto& data: layer.get()->GetCommandQueue())
        {
            renderer->UnRegisterRenderable(data);
        }
    }

    void LayerStack::RegisterRenderable(const std::unique_ptr<Layer> &layer) const
    {
        const auto renderer = renderer_.lock(); \
        if (!renderer) return;

        for (const auto& data: layer.get()->GetCommandQueue())
        {
            renderer->RegisterRenderable(data);
        }
    }

}