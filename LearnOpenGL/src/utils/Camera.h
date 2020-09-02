#pragma once
#include "CommonHeader.h"

class Camera
{
public:
    Camera();
    virtual ~Camera();
public:
    glm::vec3 m_postion;
    glm::vec4 m_backgroudColor;
    float m_FOV;
    float m_near;
    float m_far;
};

