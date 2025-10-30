#pragma once
#include "Level.h"

namespace Core
{
    class LevelManger
    {
    public:
        explicit LevelManger(std::queue<RenderData>* renderDataCommandQueue): renderDataCommandQueue_(renderDataCommandQueue) {}
        ~LevelManger() = default;

        void RegisterLevel(std::unique_ptr<Level> level, const std::string& identifier);
        std::unique_ptr<Level> UnregisterLevel(const std::string& identifier);

        std::vector<std::string> GetAllLevelNames() const;
        Level& GetCurrentLevel() const;
        std::string GetCurrentLevelName();

        ERROR ChangeLevel(const std::string& identifier);

    private:
        std::unordered_map<std::string, std::unique_ptr<Level>> level_map_ = {};
        std::string current_level_name_ = {};
        Level* current_level_ = nullptr;
        std::queue<RenderData>* renderDataCommandQueue_ = nullptr;
    };
};