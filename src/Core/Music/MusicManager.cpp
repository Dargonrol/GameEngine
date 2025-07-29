#include "MusicManager.h"

#include <ranges>


MusicManager &MusicManager::getInstance()
{
    static MusicManager instance;
    return instance;
}

void MusicManager::init()
{
    InitAudioDevice();
    looping = false;
    calledInit = true;
}

void MusicManager::shutdown()
{
    CloseAudioDevice();
    for (const auto &val: registeredMusic | std::views::values)
    {
        UnloadMusicStream(val);
    }
}

void MusicManager::update()
{
    if (currentMusic) {
        UpdateMusicStream(*currentMusic);
        musicTimePlayed = GetMusicTimePlayed(*currentMusic);

        if (looping && musicTimePlayed > GetMusicTimeLength(*currentMusic))
        {
            StopMusicStream(*currentMusic);
            PlayMusicStream(*currentMusic);
        } else
        {
            if (musicTimePlayed > GetMusicTimeLength(*currentMusic) && IsMusicStreamPlaying(*currentMusic))
            {
                StopMusicStream(*currentMusic);
            }
        }
    }
}

void MusicManager::registerTrack(const std::filesystem::path& path, const std::string& identifier)
{
    if (!initCheck()) { return; }
    if (identifierExists(identifier))
    {
        TraceLog(LOG_ERROR, ("Identifier: " + identifier + " already exists!").c_str());
        return;
    }
    registeredMusic.emplace(identifier, LoadMusicStream(path.c_str()));
}

void MusicManager::unregisterTrack(const std::string& identifier)
{
    if (!identifierExists(identifier)) { return; }
    Music* track = getTrack(identifier);
    if (IsMusicStreamPlaying(*track))
    {
        StopMusicStream(*track);
        if (currentMusic == track)
        {
            currentMusic = nullptr;
        }
    }
    UnloadMusicStream(*track);
    registeredMusic.erase(identifier);
}

void MusicManager::switchTrack(const std::string& identifier)
{
    stopTrack();
    playTrack(identifier);
    currentMusic = getTrack(identifier);
}

void MusicManager::pauseTrack()
{
    if (!initCheck()) { return; }
    if (!IsMusicValid(*currentMusic))
    {
        TraceLog(LOG_ERROR, "current Music stream is not valid");
        return;
    }
    PauseMusicStream(*currentMusic);
    paused = true;
}

void MusicManager::unpauseTrack()
{
    if (!initCheck()) { return; }
    if (!IsMusicValid(*currentMusic))
    {
        TraceLog(LOG_ERROR, "current Music stream is not valid");
        return;
    }
    ResumeMusicStream(*currentMusic);
    paused = false;
}

void MusicManager::stopTrack() const
{
    if (!initCheck()) { return; }
    if (!IsMusicValid(*currentMusic))
    {
        TraceLog(LOG_ERROR, "current Music stream is not valid");
        return;
    }
    if (!IsMusicStreamPlaying(*currentMusic))
    {
        TraceLog(LOG_ERROR, "No music stream is currently playing");
        return;
    }
    StopMusicStream(*currentMusic);
}

void MusicManager::playTrack(const std::string& identifier)
{
    if (!initCheck()) { return; }
    if (!identifierExists(identifier)) { return; }
    Music* track = getTrack(identifier);
    if (!IsMusicValid(*track)) { return; }
    PlayMusicStream(*track);
    currentMusic = track;
    paused = false;
}

void MusicManager::enableLooping(bool enabled)
{
    looping = enabled;
}

bool MusicManager::isMusicRunning()
{
    if (currentMusic)
    {
        return IsMusicStreamPlaying(*currentMusic);
    }
    return false;
}

bool MusicManager::isPaused() const
{
    return paused;
}

Music* MusicManager::getTrack(const std::string& identifier)
{
    auto it = registeredMusic.find(identifier);
    if (it != registeredMusic.end()) return &it->second;
    return nullptr;
}

bool MusicManager::initCheck() const
{
    if (calledInit) { return true; }

    TraceLog(LOG_ERROR, "Used MusicManager without called init()");
    return false;
}

bool MusicManager::identifierExists(const std::string &identifier) const
{
    if (!registeredMusic.contains(identifier))
    {
        TraceLog(LOG_ERROR, ("Identifier: " + identifier + " does not exist!").c_str());
        return false;
    }
    return true;
}
