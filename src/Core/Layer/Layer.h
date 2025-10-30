#ifndef LAYER_H
#define LAYER_H
#include "../Level/Level.h"
#include "../Level/LevelManager.h"

namespace Core {

using LayerID = size_t;

enum class OBJ_Command
{
    REGISTER,
    UNREGISTER,
    UPDATE
};


struct RenderObjID {
    LayerID layerID;
    size_t entityID;
};

struct RenderData
{
    OBJ_Command command;
    RenderObjID ID;
    // Mesh mesh // copy not reference
    // Texture tex;
    // Transform trsf;
};

class Layer {

public:
    Layer() : levelManager_(std::make_unique<LevelManger>(&renderDataCommandQueue)) {}
    ~Layer();

    void suspend(); // ecs.get_every_renderabel_entity() -> issue unregister command
    void activate(); // vise versa

    void onAttach();
    void onDetach();

    void update();

    void onEvent();

    [[nodiscard]] std::queue<RenderData>& GetCommandQueue() { return renderDataCommandQueue; }


public:
    size_t ID{};

private:
    std::unique_ptr<LevelManger> levelManager_;
    std::queue<RenderData> renderDataCommandQueue;
    bool suspended = false;
};

} // Core

#endif //LAYER_H
