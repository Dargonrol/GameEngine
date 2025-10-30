#include "Layer.h"

namespace Core
{
    void Layer::RegisterAllRenderablesCommandIssue() const
    {
        levelManager_->RegisterAllRenderablesCommandIssue();
    }

    void Layer::suspend() {}

    void Layer::activate() {}

    void Layer::onAttach() {}

    void Layer::onDetach() {}

    void Layer::update() {}

    void Layer::onEvent() {}

    void Layer::UnregisterAllRenderablesCommandIssue() const
    {
        levelManager_->UnRegisterAllRenderablesCommandIssue();
    }


}