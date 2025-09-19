#pragma once
#include <filesystem>
#include <string>

#include "../Color.h"
#include "RaylibRenderer/Window.h"

namespace Core::Renderer
{
    struct TextureHandle
    {
        unsigned int id;
    };

    class IRenderer {
    public:
        virtual ~IRenderer() = default;

        virtual void Init(int width, int height, const std::string& title) = 0;
        virtual void Shutdown() = 0;

        virtual void Clear(const Color& color) = 0;
        virtual void Present() = 0;

        virtual TextureHandle LoadTexture(const std::filesystem::path& path) = 0;
        virtual void UnloadTexture(TextureHandle tex) = 0;
        //virtual void DrawTexture(TextureHandle tex, const Vec2& pos) = 0;

    protected:
        Window window_;
    };
}

