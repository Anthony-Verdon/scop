#include "Camera.hpp"
#include <iostream>
#include "Utils.hpp"

Camera::Camera(const Matrix &position, const Matrix &upDirection, float yaw, float pitch, float roll, float fov, float speed)
{
    Matrix frontDirection(3, 1);
    Matrix rightDirection(3, 1);

    frontDirection.uniform(1.0f);
    rightDirection.uniform(1.0f);
    this->position = position;
    this->frontDirection = frontDirection.uniform(1.0f);
    this->rightDirection = rightDirection.uniform(1.0f);
    this->upDirection = upDirection;
    this->yaw = yaw;
    this->pitch = pitch;
    this->roll = roll;
    this->fov = fov;
    this->speed = speed;
}

Camera::Camera(const Camera &copy)
{
    *this = copy;
}

Camera& Camera::operator=(const Camera &copy)
{
    if (&copy != this)
    {
        position = copy.getPosition();
        frontDirection = copy.getFrontDirection();
        rightDirection = copy.getRightDirection();
        upDirection = copy.getUpDirection();
        yaw = copy.getYaw();
        pitch = copy.getPitch();
        roll = copy.getRoll();
        fov = copy.getFov();
        speed = copy.getSpeed();
    }
    return (*this);
}

Camera::~Camera()
{
}

Matrix Camera::getPosition() const
{
    return (position);
}

Matrix Camera::getFrontDirection() const
{
    return (frontDirection);
}

Matrix Camera::getRightDirection() const
{
    return (rightDirection);
}

Matrix Camera::getUpDirection() const
{
    return (upDirection);
}

float Camera::getYaw() const
{
    return (yaw);
}

float Camera::getPitch() const
{
    return (pitch);
}
float Camera::getRoll() const
{
    return (roll);
}

float Camera::getFov() const
{
    return (fov);
}
float Camera::getSpeed() const
{
    return (speed);
}

void Camera::setPosition(const Matrix &position) 
{
    if (position.getRows() != 3 || position.getColumns() != 1)
        throw(Utils::Exception("CAMERA::SET_POSITION::INVALID_SIZE\n"
        "VECTOR SIZE => " + std::to_string(position.getRows()) + " * " + std::to_string(position.getColumns())));

    this->position = position;
}
void Camera::setFrontDirection(const Matrix &frontDirection)
{
    if (frontDirection.getRows() != 3 || frontDirection.getColumns() != 1)
        throw(Utils::Exception("CAMERA::SET_FRONT_DIRECTION::INVALID_SIZE\n"
        "VECTOR SIZE => " + std::to_string(frontDirection.getRows()) + " * " + std::to_string(frontDirection.getColumns())));

    this->frontDirection = frontDirection;
}

void Camera::setRightDirection(const Matrix &rightDirection)
{
    if (rightDirection.getRows() != 3 || rightDirection.getColumns() != 1)
        throw(Utils::Exception("CAMERA::SET_RIGHT_DIRECTION::INVALID_SIZE\n"
        "VECTOR SIZE => " + std::to_string(rightDirection.getRows()) + " * " + std::to_string(rightDirection.getColumns())));

    this->rightDirection = rightDirection;
}

void Camera::setUpDirection(const Matrix &upDirection)
{
    if (upDirection.getRows() != 3 || upDirection.getColumns() != 1)
        throw(Utils::Exception("CAMERA::SET_UP_DIRECTION::INVALID_SIZE\n"
        "VECTOR SIZE => " + std::to_string(upDirection.getRows()) + " * " + std::to_string(upDirection.getColumns())));

    this->upDirection = upDirection;
}

void Camera::setYaw(float yaw)
{
    this->yaw = yaw;
}

void Camera::setPitch(float pitch)
{
    this->pitch = pitch;
}

void Camera::setRoll(float roll)
{
    this->roll = roll;
}

void Camera::setFov(float fov)
{
    this->fov = fov;
}

void Camera::setSpeed(float speed)
{
    this->speed = speed;
}

void Camera::addToPosition(const Matrix &position)
{
    if (position.getRows() != 3 || position.getColumns() != 1)
        throw(Utils::Exception("CAMERA::ADD_TO_POSITION::INVALID_SIZE\n"
        "VECTOR SIZE => " + std::to_string(position.getRows()) + " * " + std::to_string(position.getColumns())));

    this->position = this->position + position;
}

void Camera::addToYaw(float yaw)
{
    this->yaw += yaw;
}

void Camera::addToPitch(float pitch)
{
    this->pitch += pitch;
}

void Camera::addToFov(float fov)
{
    this->fov += fov;
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
    const float sensitivity = 0.1f;

    static float lastX = 400;
    static float lastY = 300;
    static bool firstIteration = true;

    float xOffset;
    float yOffset;

    Camera *camera = reinterpret_cast<Camera *>(glfwGetWindowUserPointer(window));
    if (firstIteration)
    {
        lastX = xPos;
        lastY = yPos;
        firstIteration = false;
    }
    xOffset = (xPos - lastX) * sensitivity;
    yOffset = (lastY - yPos) * sensitivity;
    lastX = xPos;
    lastY = yPos;
    camera->addToYaw(xOffset);
   camera->addToPitch(yOffset);
    if (camera->getPitch() > 89.0f)
        camera->setPitch(89.0f);
    else if (camera->getPitch() < -89.0f)
        camera->setPitch(-89.0f);
}

void scroll_callback(GLFWwindow *window, double xOffset, double yOffset)
{
    (void)xOffset;

    Camera *camera = reinterpret_cast<Camera *>(glfwGetWindowUserPointer(window));
    camera->addToFov((float)-yOffset);
    if (camera->getFov() > 1.0f)
        camera->setFov(1.0f);
    else if (camera->getFov() < -45.0f)
        camera->setFov(-45.0f);
}