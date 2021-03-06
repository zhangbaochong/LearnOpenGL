#pragma once
#include <string>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

class Dashboard
{
public:
    static void initSceneName(std::string sceneName);
    static void draw(float fps);
    static void setEnabledCursor(bool status);

public:
    static std::string s_sceneName;
    static bool s_enabledCursor;
};

