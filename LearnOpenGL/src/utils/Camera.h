#pragma once
#include "CommonHeader.h"

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
public:
    Camera(glm::vec3 postion=glm::vec3(0.f, 1.f, 10.f));
    virtual ~Camera();
public:
    glm::vec3 m_postion;
    glm::vec4 m_backgroudColor;
    float m_FOV;
    float m_near;
    float m_far;
private:
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_worldUp;
    // Eular Angles
    GLfloat m_yaw;
    GLfloat m_pitch;
    // Camera options
    GLfloat m_movementSpeed;
    GLfloat m_mouseSensitivity;
    float m_aspect;

public:
    glm::mat4 getViewMatrix();
    glm::mat4 getProjMatrix();
    void setAspect(float aspect);

    // Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void processKeyboard(Camera_Movement direction, GLfloat deltaTime);

    // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void processMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);

    // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void processMouseScroll(GLfloat yoffset);

    void updateCameraVectors();
};

