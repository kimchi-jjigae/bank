#pragma once
#include "glm.hpp"
#include <string>

struct QuitMessage
{
};

struct ResizeMessage
{
    glm::uvec2 size;
};

struct PlayMusicMessage
{
    std::string name;
    bool loop;
};

struct PlaySoundMessage
{
    std::string name;
    bool loop;
};

struct StopSoundMessage
{
};

struct AdvanceQueueMessage
{
};

struct MissNumberMessage
{
};

struct StartMinigameMessage
{
    std::string name;   
};

struct MouseClickMessage
{
    glm::uvec2 position;
};

struct MouseReleaseMessage
{
    glm::uvec2 position;
};

struct MouseMoveMessage
{
    glm::uvec2 position;
};
