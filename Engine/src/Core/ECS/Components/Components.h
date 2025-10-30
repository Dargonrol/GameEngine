#pragma once
#include <string>
#include <unordered_map>


namespace Core::ECS
{
    using ComponentType = size_t;
    inline ComponentType next_component_type = 0;

    template<typename C>
    ComponentType get_component_type_index() {
        static ComponentType type_index = next_component_type++;
        return type_index;
    }

    struct Component
    {

    };

    struct MetaComponent : Component
    {
        std::pmr::unordered_map<std::string, std::string> data;
    };

    struct Transform : Component
    {
        float x, y;
        float rotation;
        float scaleX, scaleY;
    };

    struct Velocity : Component
    {
        float vx, vy;
        float ax, ay;
    };

    struct Gravity : Component
    {
        float strength;
        // Vector2 direction;
    };

    struct CollisionAABB : Component
    {
        float width, height; // hitbox
        bool noclip;
    };

    struct Health : Component
    {
        int current;
        int max;
        bool invincible;
    };

    struct Regeneration : Component
    {
        bool active;
        int rate; // per second
    };

    struct Render : Component
    {
        bool visible;
        // type = Sprite, Rectangle, Circle, Line...
    };
}
