#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float width, float height, float near, float far) :
m_position(position),
m_up(up),
m_world_up(up),
m_yaw(yaw),
m_pitch(pitch),
m_width(width),
m_height(height),
m_near(near),
m_far(far)
{
    m_front = glm::vec3(0.0f, 0.0f, -1.0f);
    m_max_speed = 2.5f;
    m_zoom = 45.0f;
    m_sensitivity = 0.1f;

    update_vectors_from_yaw_and_pitch();
}

Camera::Camera(float x, float y, float z, float up_x, float up_y, float up_z, float yaw, float pitch, float width, float height, float near, float far) : 
Camera(glm::vec3(x, y, z), glm::vec3(up_x, up_y, up_z), yaw, pitch, width, height, near, far) {}

glm::mat4 Camera::view_matrix()
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Camera::projection_matrix()
{
    return glm::perspective(glm::radians(m_zoom), m_width/m_height, m_near, m_far);
}

void Camera::move(movement_direction direction, float dt)
{
    float velocity = m_max_speed * dt;
    if (direction == movement_direction::forward)
        m_position += m_front * velocity;
    if (direction == movement_direction::back)
        m_position -= m_front * velocity;
    if (direction == movement_direction::left)
        m_position -= m_right * velocity;
    if (direction == movement_direction::right)
        m_position += m_right * velocity;
}

void Camera::process_pan(float xoffset, float yoffset, bool constrain_pitch)
{
    xoffset *= m_sensitivity;
    yoffset *= m_sensitivity;

    m_yaw   += xoffset;
    m_pitch += yoffset;

    if (constrain_pitch)
    {
        if (m_pitch > 89.0f)
            m_pitch = 89.0f;
        if (m_pitch < -89.0f)
            m_pitch = -89.0f;
    }

    update_vectors_from_yaw_and_pitch();
}

void Camera::process_zoom(float yoffset)
{
    m_zoom -= (float)yoffset;
    if (m_zoom < 1.0f)
        m_zoom = 1.0f;
    if (m_zoom > 45.0f)
        m_zoom = 45.0f; 
}

void Camera::update_vectors_from_yaw_and_pitch()
{
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);

    m_right = glm::normalize(glm::cross(m_front, m_world_up));
    m_up    = glm::normalize(glm::cross(m_right, m_front));
}