#include "BaseScene.h"

BaseScene::BaseScene()
{
    this->m_screenWidth = 1440;
    this->m_screenHeight = 900;
}

BaseScene::~BaseScene() {}

void BaseScene::handleInput(GLFWwindow* wnd)
{
    GLfloat deltaTime = Timer::deltaTime;
    if (glfwGetKey(wnd, GLFW_KEY_W))
    {
        MainCamera::getInstance()->processKeyboard(FORWARD, deltaTime);
    }
    else if (glfwGetKey(wnd, GLFW_KEY_S))
    {
        MainCamera::getInstance()->processKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(wnd, GLFW_KEY_A))
    {
        MainCamera::getInstance()->processKeyboard(LEFT, deltaTime);
    }
    else if (glfwGetKey(wnd, GLFW_KEY_D))
    {
        MainCamera::getInstance()->processKeyboard(RIGHT, deltaTime);
    }
}

void BaseScene::onMouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (Mouse::isFisrtMove())
    {
        Mouse::setLastXY(xpos, ypos);
        Mouse::setFirstMove(false);
    }

    GLfloat xoffset = xpos - Mouse::getLastX();
    GLfloat yoffset = Mouse::getLastY() - ypos;  // Reversed since y-coordinates go from bottom to left

    Mouse::setLastXY(xpos, ypos);

    MainCamera::getInstance()->processMouseMovement(xoffset, yoffset);
}

void BaseScene::onMouseScrollCallBack(GLFWwindow* window, double xoffset, double yoffset)
{
    MainCamera::getInstance()->processMouseScroll(yoffset);
}

int BaseScene::getWidth()
{
    return this->m_screenWidth;
}

int BaseScene::getHeight()
{
    return this->m_screenHeight;
}