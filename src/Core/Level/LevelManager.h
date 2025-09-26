#pragma once
#include "Level.h"

namespace Core
{
    class LevelManger
    {
    public:
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


        // Singleton
        // ------------------------------------------------
    public:
        LevelManger(const LevelManger& obj) = delete;

        static LevelManger* get()
        {
            if (_level_manager_ptr == nullptr)
            {
                _level_manager_ptr = new LevelManger();
            }
            return _level_manager_ptr;
        }

    private:
        static LevelManger* _level_manager_ptr;
        LevelManger() = default;
    };
};