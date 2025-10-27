#ifndef LAYER_H
#define LAYER_H
#include "../Level/Level.h"

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
    void suspend(); // ecs.get_every_renderabel_entity() -> issue unregister command
    void activate(); // vise versa

    void onAttach();
    void onDetach();

    void update();

    void onEvent();


public:
    size_t ID;

public:
    std::unique_ptr<Level> level;
    std::queue<RenderData> renderDataCommandQueue;

private:
    bool suspended = false;
};

} // Core

#endif //LAYER_H
