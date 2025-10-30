#include "Layer.h"

namespace Core
{
    void Layer::RegisterAllRenderablesCommandIssue() const
    {
        levelManager_->RegisterAllRenderablesCommandIssue();
    }

    void Layer::UnregisterAllRenderablesCommandIssue() const
    {
        levelManager_->UnRegisterAllRenderablesCommandIssue();
    }


}