#pragma once
namespace Pong
{
    enum ERROR
    {
        NONE = 0,
        FILE_NOT_FOUND,
        ENTITY_UNKNOWN_ID,
        ENTITY_ID_NOT_UNIQUE,
        ENTITY_CAP_REACHED,
        COMPONENT_UNKNOWN
    };
}