#ifndef CONTROLS_H
#define CONTROLS_H

#include "camera.h"
#include "object.h"
#include <GLFW/glfw3.h>
#include "shader.h"

class Controls
{
public:
    Controls(GLFWwindow* window, Camera* camera, Object* object);
    void setSpeed(float newSpeed);

    void setMouseSpeed(float newMouseSpeed);
    virtual void update(float deltaTime, Shader* shader) = 0;

protected:
    Camera* m_Camera;
    Object* m_Object;
    float speed;
    float mouseSpeed;
    int width, height;

    GLFWwindow* m_Window;
};

#endif // CONTROLS_H
