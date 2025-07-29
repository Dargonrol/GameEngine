#pragma once
#include <filesystem>
#include <map>
#include <unordered_map>

#include "raylib.h"

class MusicManager {
public:
    static MusicManager& getInstance();
    MusicManager(const MusicManager&) = delete;
    MusicManager& operator=(const MusicManager&) = delete;

    void init();
    void shutdown();
    void update();

    void registerTrack(const std::filesystem::path& path, const std::string& identifier);
    void unregisterTrack(const std::string& identifier);

    void switchTrack(const std::string& identifier);
    void fadeTrack(const std::string& identifier, float length);

    void setVolume(const std::string& identifier);

    void pauseTrack() const;
    void unpauseTrack() const;

    void stopTrack() const;
    void playTrack(const std::string& identifier);

    void enableLooping(bool enabled);
    [[nodiscard]] bool isMusicRunning();

private:
    MusicManager() = default;
    ~MusicManager() = default;

    [[nodiscard]] inline Music* getTrack(const std::string& identifier);
    [[nodiscard]] inline bool initCheck() const;
    [[nodiscard]] inline bool identifierExists(const std::string& identifier) const;

private:
    std::pmr::unordered_map<std::string, Music> registeredMusic;
    Music* currentMusic = nullptr;
    Music* nextMusic = nullptr;
    double musicTimePlayed = 0;
    bool looping = false;
    bool calledInit = false;
};
