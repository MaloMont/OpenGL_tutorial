#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

class Camera
{
public:
    Camera(int win_width, int win_height, glm::vec3 _pos = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 _direction = glm::vec3(0.0f, 0.0f, -1.0f));

    void set_pos(glm::vec3 _pos);
    void set_target(glm::vec3 _target);
    void set_direction(glm::vec3 _direction);
    void set_zoom(float _fov);
    void set_angles(float _yaw, float _pitch);
    void inc_angles(float yaw_inc, float pitch_inc);

    void go_straight(const float delta_time);
    void go_back(const float delta_time);
    void go_left(const float delta_time);
    void go_right(const float delta_time);

    glm::mat4 get_view() const;
    glm::mat4 get_projection() const;

private:

    const glm::vec3 y_axis = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::vec3 pos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 direction;
    glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);

    float yaw = -90.0f;
    float pitch = 0.0f;

    // matrix to transpose world coordinate into camera coordinates
    // (where pos is (0, 0, 0), up is the y axis, right the x axis, and rdirection the z axis)
    glm::mat4 view;

    // matrix to apply perspective
    glm::mat4 projection;

    const float speed = 2.5f; // how fast the camera moves
    const float sensitivity = 0.1f; // factor bewteen mouse movment and camera movment
};

#endif