#pragma once
#include "Camera.h"

class MainCamera : public Camera
{
private:
    MainCamera(glm::vec3 position = glm::vec3(0.f, 3.f, 5.f));

public:
    static MainCamera* getInstance();

private:
    static MainCamera* s_instance;
};
