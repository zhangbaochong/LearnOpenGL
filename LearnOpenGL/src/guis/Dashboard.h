#pragma once
#include "CommonHeader.h"

class Dashboard
{
public:
    static void initSceneName(std::string sceneName);
    static void draw(float fps);

private:
    static std::string s_sceneName;
};

