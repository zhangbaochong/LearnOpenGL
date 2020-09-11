#pragma once
#include <vector>
#include "CommonHeader.h"

class DebugPanel
{
public:
    static void draw();
    static void LogError(std::string content);
    static void LogWarn(std::string content);
    static void LogInfo(std::string content);

private:
    static std::vector<std::string> s_logs;
    static float s_position[3];
};

