#pragma once
#include "CommonHeader.h"
#include "utils/Timer.h"
#include "utils/Mouse.h"
#include "utils/MainCamera.h"

class BaseScene 
{
public:
    BaseScene();
    virtual ~BaseScene();

protected:
    int m_screenWidth;
    int m_screenHeight;

public:
    virtual void onInit() {}
    virtual void onRender() {}
    virtual void onRelease() {}
    virtual void onGUI() {}
    virtual void handleInput(GLFWwindow* wnd);

    virtual void onMouseMoveCallback(GLFWwindow* window, double xpos, double ypos);

    virtual void onMouseScrollCallBack(GLFWwindow* window, double xoffset, double yoffset);

    int getWidth();

    int getHeight();
};