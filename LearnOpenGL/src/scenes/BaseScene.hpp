#pragma once
#include "CommonHeader.h"

class BaseScene 
{
public:
    BaseScene() 
    {
        this->m_screenWidth = 1440;
        this->m_screenHeight = 900;
    }
    virtual ~BaseScene() {}

protected:
    int m_screenWidth;
    int m_screenHeight;

public:
    virtual void onInit() {}
    virtual void onRender() {}
    virtual void onRelease() {}
    virtual void onGUI() {}
    virtual void handleInput(GLFWwindow* wnd) {}
    virtual void onMouseMoveCallback(GLFWwindow* window, double xpos, double ypos) {}
    virtual void onMouseScrollCallBack(GLFWwindow* window, double xoffset, double yoffset) {}

    int getWidth()
    {
        return this->m_screenWidth;
    }

    int getHeight()
    {
        return this->m_screenHeight;
    }
};