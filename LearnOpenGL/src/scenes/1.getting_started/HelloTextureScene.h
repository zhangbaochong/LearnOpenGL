#pragma once
#include <memory>
#include "../BaseScene.hpp"
#include "../../utils/shader_m.h"
#include "CommonHeader.h"

class HelloTextureScene : public BaseScene
{
public:
    HelloTextureScene();
    virtual ~HelloTextureScene();

private:
    std::shared_ptr<Shader> m_shader;
    unsigned int m_VBO;
    unsigned int m_VAO;
    unsigned int m_EBO;
    unsigned int m_texture;
    float m_vertices[8 * 4] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int m_indices[6] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

public:
    void onInit();
    void onRender();
    void onRelease();
    void onGUI();
};



