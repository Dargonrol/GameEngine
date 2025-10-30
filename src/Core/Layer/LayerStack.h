#ifndef LAYERSTACK_H
#define LAYERSTACK_H

#include "Layer.h"
#include "../Renderer/Renderer.h"

namespace Core {

class LayerStack {
public:
    LayerStack();
    ~LayerStack();

    void update() const;

    template<typename T>
    requires(std::is_base_of_v<Layer, T>)
    void PushLayer();

    void PopLayer();

    template<typename T>
    requires(std::is_base_of_v<Layer, T>)
    void InsertLayer(size_t index);

    template<typename T>
    requires(std::is_base_of_v<Layer, T>)
    void RemoveLayer(size_t index);

    template<typename T>
    requires(std::is_base_of_v<Layer, T>)
    void SuspendLayer() const; // empties command queue and calls suspend on layer then for a last time works through queue which will be filled with unregister commands.

    template<typename T>
    requires(std::is_base_of_v<Layer, T>)
    void ActivateLayer() const;

private:
    template<typename T>
    requires(std::is_base_of_v<Layer, T>)
    bool HasLayer() const;
    void UnRegisterRenderable(const std::unique_ptr<Layer> &layer) const;
    void RegisterRenderable(const std::unique_ptr<Layer> &layer) const;

private:
    std::vector<std::unique_ptr<Layer>> layerStack_;
    std::weak_ptr<Renderer::IRenderer> renderer_;

};

}

#endif //LAYERSTACK_H
