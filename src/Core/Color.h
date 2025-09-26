#pragma once
#include <cstdint>

namespace Core {
    struct Color
        {
            uint8_t r = 255;
            uint8_t g = 255;
            uint8_t b = 255;
            uint8_t a = 255;
        };
}

namespace Core
{
#define RED Color{255, 0, 0, 255}
}