#pragma once
#include <iostream>
#include <imgui\imgui.h>

class BaseScene 
{
public:
    BaseScene() 
    {
        this->m_screenWidth = 1024;
        this->m_screenHeight = 768;
    }
    virtual ~BaseScene() {}

protected:
    int m_screenWidth;
    int m_screenHeight;

public:
    virtual void onInit() = 0;
    virtual void onRender() = 0;
    virtual void onRelease() = 0;
    virtual void onGUI() = 0;

    int getWidth()
    {
        return this->m_screenWidth;
    }

    int getHeight()
    {
        return this->m_screenHeight;
    }
};