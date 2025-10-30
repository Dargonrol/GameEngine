#pragma once
#include <filesystem>
#include <string>

#include "../Color.h"
#include "../Layer/Layer.h"
#include "RaylibRenderer/Window.h"

namespace Core::Renderer
{
    struct TextureHandle
    {
        unsigned int id;
    };

    class IRenderer {
    public:
        explicit IRenderer(Window* window);
        virtual ~IRenderer() = default;

        virtual void Init(int width, int height, const std::string& title) = 0;
        virtual void Shutdown() = 0;

        virtual void Clear(const Color& color) = 0;
        virtual void Present() = 0;

        virtual TextureHandle LoadTexture(const std::filesystem::path& path) = 0;
        virtual void UnloadTexture(TextureHandle tex) = 0;
        //virtual void DrawTexture(TextureHandle tex, const Vec2& pos) = 0;

        void RegisterRenderable(RenderData& renderData) {};
        void UnRegisterRenderable(RenderData& renderData) {};
        void UpdateRenderable(RenderData& renderData) {};

    protected:
        Window window_ = {};
    };
}

