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
    void PushLayer(); //has to set LayerID

    template<typename T>
    void SuspendLayer()
    {
        static_assert(std::is_base_of_v<Layer, T>, "T must inherit from Layer");
        // empties command queue and calls suspend on layer then for a last time works through queue which will be filled with unregister commands.
    }

private:
    std::vector<std::unique_ptr<Layer>> layerStack_;
    std::weak_ptr<Renderer::IRenderer> renderer_;

};

}

#endif //LAYERSTACK_H
