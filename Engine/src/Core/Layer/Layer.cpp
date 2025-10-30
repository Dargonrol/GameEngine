#include "Layer.h"

namespace Core
{
    void Layer::CollectRegisterCommands() const
    {
        levelManager_->CollectRegisterCommands();
    }

    void Layer::suspend()
    {
        levelManager_->CollectUnregisterCommands();
        suspended = true;
    }

    void Layer::activate()
    {
        levelManager_->CollectRegisterCommands();
        suspended = false;
    }

    void Layer::onAttach() const
    {
        levelManager_->CollectRegisterCommands();
    }

    void Layer::onDetach() const
    {
        levelManager_->CollectUnregisterCommands();
    }

    void Layer::update(float delta)
    {
        levelManager_->GetCurrentLevel().Update(delta);
    }

    void Layer::onEvent() {}

    void Layer::CollectUnregisterCommands() const
    {
        levelManager_->CollectUnregisterCommands();
    }


}