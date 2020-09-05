#include "MainCamera.h"

MainCamera* MainCamera::s_instance = nullptr;

MainCamera::MainCamera(glm::vec3 position) : Camera(position)
{
}

MainCamera* MainCamera::getInstance()
{
    if (s_instance == nullptr)
    {
        s_instance = new MainCamera();
    }
    return s_instance;
}