#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

enum movement_direction {
    forward,
    back,
    left,
    right,
    up,
    down
};

class Camera
{
private:
    glm::vec3 m_position, m_front, m_up, m_right, m_world_up;
    float m_yaw, m_pitch;
    float m_max_speed, m_sensitivity, m_zoom;
    float m_width, m_height, m_near, m_far;

    void update_vectors_from_yaw_and_pitch();
public:
    Camera(
        float x = 0.0f,
        float y = 0.0f,
        float z = 0.0f,
        float up_x = 0.0f,
        float up_y = 1.0f,
        float up_z = 0.0f,
        float yaw = -90.0f,
        float pitch = 0.0f,
        float width = 800.0f,
        float height = 600.0f,
        float near = 0.1f,
        float far = 100.0f
    );
    Camera(
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = -90.0f,
        float pitch = 0.0f,
        float width = 800.0f,
        float height = 600.0f,
        float near = 0.1f,
        float far = 100.0f
    );
    ~Camera() {}

    glm::vec3 position() { return m_position; }
    void set_position(glm::vec3 position) { m_position = position; }
    void set_position(float x, float y, float z) { m_position = glm::vec3(x, y, z); }

    glm::vec3 front() { return m_front; }
    void set_front(glm::vec3 front) { m_front = front; }
    void set_front(float x, float y, float z) { m_front = glm::vec3(x, y, z); }

    glm::vec3 up() { return m_up; }
    void set_up(glm::vec3 up) { m_up = up; }
    void set_up(float x, float y, float z) { m_up = glm::vec3(x, y, z); }

    glm::vec3 right() { return m_right; }
    void set_right(glm::vec3 right) { m_right = right; }
    void set_right(float x, float y, float z) { m_right = glm::vec3(x, y, z); }

    glm::vec3 world_up() { return m_world_up; }
    void set_world_up(glm::vec3 world_up) { m_world_up = world_up; }
    void set_world_up(float x, float y, float z) { m_world_up = glm::vec3(x, y, z); }

    float yaw() { return m_yaw; }
    void set_yaw(float yaw) { m_yaw = yaw; }

    float pitch() { return m_pitch; }
    void set_pitch(float pitch) { m_pitch = pitch; }

    float max_speed() { return m_max_speed; }
    void set_max_speed(float max_speed) { m_max_speed = max_speed; }

    float sensitivity() { return m_sensitivity; }
    void set_sensitivity(float sensitivity) { m_sensitivity = sensitivity; }

    float zoom() { return m_zoom; }
    void set_zoom(float zoom) { m_zoom = zoom; }

    float width() { return m_width; }
    void set_width(float width) { m_width = width; }

    float height() { return m_height; }
    void set_height(float height) { m_height = height; }

    float near() { return m_near; }
    void set_near(float near) { m_near = near; }
    
    float far() { return m_far; }
    void set_far(float far) { m_far = far; }
    
    glm::mat4 view_matrix();

    glm::mat4 projection_matrix();

    void move(movement_direction direction, float dt);

    void process_zoom(float yoffset);

    void process_pan(float xoffset, float yoffset, bool constrain_pitch = true);
};