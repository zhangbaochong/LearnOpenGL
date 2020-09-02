#include "Camera.h"

Camera::Camera(): m_FOV(60.f), m_near(0.3f), m_far(1000.f)
{
    m_postion = glm::vec3(0.f, 0.f, 10.f);
    m_backgroudColor = glm::vec4(0.1f, 0.2f, 0.3f, 0.5f);
}

Camera::~Camera()
{}