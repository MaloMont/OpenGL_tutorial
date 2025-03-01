#include "Camera.h"

/**
 * @brief creates a camera object
 * @param win_width the width of the screen area
 * @param win_height the height of the screen area
 * @param _pos the position of the camera in world coordinates
 * @param _direction the direction of the camera in world coordinates (will be normalized)
 */
Camera::Camera(int win_width, int win_height, glm::vec3 _pos /* = glm::vec3(0.0f, 0.0f, 3.0f) */, glm::vec3 _direction /* = glm::vec3(0.0f, 0.0f, 0.0f) */)
{
    pos = _pos;
    direction = glm::normalize(_direction);
    target = pos + _direction;

    projection = glm::perspective(glm::radians(45.0f), (float)win_width / (float)win_height, 0.1f, 100.0f);
}

/**
 * @brief set the position of the camera
 * @param _pos the position in world coordinates
 */
void Camera::set_pos(glm::vec3 _pos)
{
    pos = _pos;
    view = glm::lookAt(pos, target, y_axis);
}

/**
 * @brief set the direction of the camera
 * @param _direction the direction in world coordinates
 */
void Camera::set_direction(glm::vec3 _direction)
{
    direction = _direction;
    target = pos + direction;
    view = glm::lookAt(pos, target, y_axis);
}

/**
 * @brief set the direction through a target object
 * @param _target the point in world coordinates to which the camera will look at
 */
void Camera::set_target(glm::vec3 _target)
{
    target = _target;
    direction = glm::normalize(target - pos);

    pitch =  glm::degrees(asin(direction.y));
    yaw   = -glm::degrees(acos(direction.x / cos(glm::radians(pitch))));

    view = glm::lookAt(pos, target, y_axis);
}

/**
 * @brief set camera direction through yaw and pitch angles
 * @param _yaw the yaw angle (in degrees)
 * @param _pitch the pitch angle (in degrees)
 */
void Camera::set_angles(float _yaw, float _pitch)
{
    yaw = _yaw;
    pitch = _pitch;
    pitch = glm::min(pitch,  89.0f);
    pitch = glm::max(pitch, -89.0f);

    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction = glm::normalize(direction);

    target = pos + direction;

    view = glm::lookAt(pos, target, y_axis);

}

/**
 * @brief changes the camera direction by a certain amount for each angle
 * @param yaw_inc how much the direction changes in term of yaw angle (in degrees)
 * @param pitch_inc how much the direction changes in term of pitch angle (in degrees)
 */
void Camera::inc_angles(float yaw_inc, float pitch_inc)
{
    yaw_inc *= sensitivity;
    pitch_inc *= sensitivity;
    set_angles(yaw + yaw_inc, pitch + pitch_inc);
}

/**
 * @brief get the view matrix to transpose world coordinates of an object to camera coordinates
 * @return glm::mat4 the view matrix
 */
glm::mat4 Camera::get_view() const
{
    return view;
}

/**
 * @brief get the projection matrix to apply perspective to the scene
 * @return glm::mat4 the projection matrix
 */
glm::mat4 Camera::get_projection() const
{
    return projection;
}

/**
 * @brief get the world position of the camera
 * @return glm::vec3 
 */
glm::vec3 Camera::get_pos() const
{
    return pos;
}

/**
 * @brief go straight on
 * @param delta_time the time of the last frame, to accord the deplacment amount accordingly
 */
void Camera::go_straight(const float delta_time)
{
    pos += speed * delta_time * direction;
    target = pos + direction;
    view = glm::lookAt(pos, target, y_axis);
}

/**
 * @brief go straight back (without changing the direction the direction is pointing at)
 * @param delta_time the time of the last frame, to accord the deplacment amount accordingly
 */
void Camera::go_back(const float delta_time)
{
    pos -= speed * delta_time * direction;
    target = pos + direction;
    view = glm::lookAt(pos, target, y_axis);
}

/**
 * @brief go to the left (without changing the direction the direction is pointing at)
 * @param delta_time the time of the last frame, to accord the deplacment amount accordingly
 */
void Camera::go_left(const float delta_time)
{
    pos -= speed * delta_time * glm::normalize(glm::cross(direction, y_axis));
    target = pos + direction;
    view = glm::lookAt(pos, target, y_axis);
}

/**
 * @brief go to the right (without changing the direction the direction is pointing at)
 * @param delta_time the time of the last frame, to accord the deplacment amount accordingly
 */
void Camera::go_right(const float delta_time)
{
    pos += speed * delta_time * glm::normalize(glm::cross(direction, y_axis));
    target = pos + direction;
    view = glm::lookAt(pos, target, y_axis);
}
