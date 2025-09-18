#pragma once

namespace Pong
{
    namespace ECS
    {
        struct Component
        {

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

        struct Gravity : Component { };

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
}