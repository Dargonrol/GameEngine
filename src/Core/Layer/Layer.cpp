#include "Layer.h"

namespace Core
{
    void Layer::CollectRegisterCommands() const
    {
        levelManager_->CollectRegisterCommands();
    }

    void Layer::suspend() {}

    void Layer::activate() {}

    void Layer::onAttach() {}

    void Layer::onDetach() {}

    void Layer::update() {}

    void Layer::onEvent() {}

    void Layer::CollectUnregisterCommands() const
    {
        levelManager_->CollectUnregisterCommands();
    }


}