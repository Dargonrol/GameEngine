#pragma once
namespace Core
{
    enum class ERROR
    {
        NONE = 0,

        FILE_NOT_FOUND,

        INDEX_OUT_OF_RANGE,

        ENTITY_UNKNOWN_ID,
        ENTITY_ID_NOT_UNIQUE,
        ENTITY_CAP_REACHED,

        COMPONENT_UNKNOWN,

        REGISTRY_IS_NULLPTR,

        LEVEL_UNKNOWN,

        ALREADY_EXISTS
    };

    template<typename T>
    struct Result {
        T value{};
        ERROR error = ERROR::NONE;

        [[nodiscard]] bool has_error() const { return error != ERROR::NONE; }
        explicit operator bool() const { return !has_error(); }

        T& operator*() { return value; }
        const T& operator*() const { return value; }

        T* operator->() { return &value; }
        const T* operator->() const { return &value; }
    };

    template<>
struct Result<void> {
        ERROR error = ERROR::NONE;

        [[nodiscard]] bool has_error() const { return error != ERROR::NONE; }
        explicit operator bool() const { return !has_error(); }
    };
}