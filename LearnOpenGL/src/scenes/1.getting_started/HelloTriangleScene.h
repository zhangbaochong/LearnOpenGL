#pragma once
#include <memory>
#include "../BaseScene.hpp"
#include "../../utils/shader_m.h"

class HelloTriangleScene : public BaseScene
{
public:
    HelloTriangleScene();
    virtual ~HelloTriangleScene();

private:
    std::shared_ptr<Shader> m_shader;
    unsigned int m_VBO;
    unsigned int m_VAO;

public: 
    void onInit();
    void onRender();
    void onRelease();
    void onGUI();
};

