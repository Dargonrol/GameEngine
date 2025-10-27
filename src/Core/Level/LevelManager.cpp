#include "LevelManager.h"

namespace Core
{
    void LevelManger::RegisterLevel(std::unique_ptr<Level> level, const std::string &identifier)
    {
        level->SetRenderDataCommandQueue(renderDataCommandQueue_);
        level_map_.emplace(
            identifier,
            std::move(level)
        );
    }

    std::unique_ptr<Level> LevelManger::UnregisterLevel(const std::string &identifier)
    {
        const auto it = level_map_.find(identifier);
        if (it == level_map_.end())
            return nullptr;
        std::unique_ptr<Level> level = std::move(it->second);
        level_map_.erase(it);
        return level;
    }

    std::vector<std::string> LevelManger::GetAllLevelNames() const
    {
        std::vector<std::string> names;
        names.reserve(level_map_.size());
        for (auto const& map : level_map_)
        {
            names.push_back(map.first);
        }
        return names;
    }

    std::string LevelManger::GetCurrentLevelName()
    {
       if (current_level_name_.empty())
           return "none";
        return current_level_name_;

    }

    Level &LevelManger::GetCurrentLevel() const
    {
        return *current_level_;
    }

    ERROR LevelManger::ChangeLevel(const std::string &identifier)
    {
        const auto it = level_map_.find(identifier);
        if (it == level_map_.end())
            return ERROR::LEVEL_UNKNOWN;

        current_level_ = it->second.get();
        return ERROR::NONE;
    }


}