//
// Created by Dargonrol on 27.10.2025.
//

#include "LayerStack.h"

namespace Core {
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

} // Core