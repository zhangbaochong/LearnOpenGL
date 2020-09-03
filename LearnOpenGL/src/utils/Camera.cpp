#include "Camera.h"

Camera::Camera(glm::vec3 postion = glm::vec3(0.f, 1.f, 10.f)): 
    m_FOV(45.f), 
    m_near(0.3f), 
    m_far(1000.f),
    m_backgroudColor(glm::vec4(0.1f, 0.2f, 0.3f, 0.5f)),
    m_worldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
    m_front(glm::vec3(0.f, 0.f, -1.f)),
    m_yaw(-90.f),
    m_pitch(0.f),
    m_movementSpeed(0.3f),
    m_mouseSensitivity(0.25f),
    m_aspect(1440.f / 900.f)
{
    this->m_position = postion;
}

Camera::~Camera()
{}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Camera::getProjMatrix()
{
    return glm::perspective(m_FOV, m_aspect, m_near, m_far);
}

void Camera::setAspect(float aspect)
{
    this->m_aspect = aspect;
}

void Camera::processKeyboard(Camera_Movement direction, GLfloat deltaTime)
{
    GLfloat velocity = this->m_movementSpeed * deltaTime;
    auto front = this->m_front;
    if (direction == FORWARD)
        this->m_position += front * velocity;
    if (direction == BACKWARD)
        this->m_position -= front * velocity;
    if (direction == LEFT)
        this->m_position -= this->m_right * velocity;
    if (direction == RIGHT)
        this->m_position += this->m_right * velocity;
}

void Camera::processMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch)
{
    xoffset *= this->m_mouseSensitivity;
    yoffset *= this->m_mouseSensitivity;

    this->m_yaw += xoffset;
    this->m_pitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (this->m_pitch > 89.0f)
            this->m_pitch = 89.0f;
        if (this->m_pitch < -89.0f)
            this->m_pitch = -89.0f;
    }

    // Update Front, Right and Up Vectors using the updated Eular angles
    this->updateCameraVectors();
}

void Camera::processMouseScroll(GLfloat yoffset)
{
    if (this->m_FOV >= 1.0f && this->m_FOV <= 60.0f)
        this->m_FOV -= yoffset * Time::deltaTime;
    if (this->m_FOV <= 1.0f)
        this->m_FOV = 1.0f;
    if (this->m_FOV >= 60.0f)
        this->m_FOV = 60.0f;
}


void Camera::updateCameraVectors()
{
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(this->m_yaw)) * cos(glm::radians(this->m_pitch));
    front.y = sin(glm::radians(this->m_pitch));
    front.z = sin(glm::radians(this->m_yaw)) * cos(glm::radians(this->m_pitch));
    this->m_front = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    this->m_right = glm::normalize(glm::cross(this->m_front, this->m_worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    this->m_up = glm::normalize(glm::cross(this->m_right, this->m_front));
}