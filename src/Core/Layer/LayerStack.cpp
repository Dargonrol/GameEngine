//
// Created by Dargonrol on 27.10.2025.
//

#include "LayerStack.h"

namespace Core {

    void LayerStack::update()
    {
        const auto renderer = renderer_.lock(); \
        if (!renderer) return;

        for (const std::unique_ptr<Layer> layer: layerStack_)
        {
            for (RenderData data: layer->renderDataCommandQueue)
            {
                data.ID.layerID = layer->ID;
                switch (data.command)
                {
                    case OBJ_Command::REGISTER:
                        renderer->RegisterRenderable(data);
                    case OBJ_Command::UNREGISTER:
                        renderer->UnRegisterRenderable(data);
                    case OBJ_Command::UPDATE:
                        renderer->UpdateRenderable(data);
                }
            }
        }
    }

} // Core