#include "controls.h"

Controls::Controls(GLFWwindow* window, Camera* camera, Object* object) :m_Camera(camera), m_Object(object), m_Window(window), speed(6), mouseSpeed(0.05)
{
    glfwGetWindowSize(window, &width, &height);
}

void Controls::setSpeed(float newSpeed)
{
    speed = newSpeed;
}

void Controls::setMouseSpeed(float newMouseSpeed)
{
    mouseSpeed = newMouseSpeed;
}

