#include "fpscontrols.h"

FPSControls::FPSControls(GLFWwindow* window, Camera* camera) :Controls(window, camera)
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void FPSControls::update(float deltaTime, Shader* shader)
{
    double xpos, ypos;
    glfwGetCursorPos(m_Window, &xpos, &ypos);


    glfwSetCursorPos(m_Window, width / 2, height / 2);




    m_Camera->setHorizontalAngle(m_Camera->getHorizontalAngle() + mouseSpeed * deltaTime * float(width / 2 - xpos));
    m_Camera->setVerticalAngle(m_Camera->getVerticalAngle() + mouseSpeed * deltaTime * float(height / 2 - ypos));

    glm::vec3 direction(
        cos(m_Camera->getVerticalAngle()) * sin(m_Camera->getHorizontalAngle()),
        sin(m_Camera->getVerticalAngle()),
        cos(m_Camera->getVerticalAngle()) * cos(m_Camera->getHorizontalAngle())
    );

    // Right vector
    glm::vec3 right = glm::vec3(
        sin(m_Camera->getHorizontalAngle() - 3.14f / 2.0f),
        0,
        cos(m_Camera->getHorizontalAngle() - 3.14f / 2.0f)
    );

    // Up vector : perpendicular to both direction and right
    glm::vec3 up = glm::cross(right, direction);


    // Move forward
    if (glfwGetKey(m_Window, GLFW_KEY_UP) == GLFW_PRESS) {
        m_Camera->setPosition(m_Camera->getPosition() + direction * deltaTime * speed);
    }
    // Move backward
    if (glfwGetKey(m_Window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        m_Camera->setPosition(m_Camera->getPosition() - direction * deltaTime * speed);
    }
    // Strafe right
    if (glfwGetKey(m_Window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        m_Camera->setPosition(m_Camera->getPosition() + right * deltaTime * speed);
    }
    // Strafe left
    if (glfwGetKey(m_Window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        m_Camera->setPosition(m_Camera->getPosition() - right * deltaTime * speed);
    }
    // Move forward
    if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS) {
        m_Camera->setPosition(m_Camera->getPosition() + direction * deltaTime * speed);
    }
    // Move backward
    if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS) {
        m_Camera->setPosition(m_Camera->getPosition() - direction * deltaTime * speed);
    }
    // Strafe right
    if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS) {
        m_Camera->setPosition(m_Camera->getPosition() + right * deltaTime * speed);
    }
    // Strafe left
    if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS) {
        m_Camera->setPosition(m_Camera->getPosition() - right * deltaTime * speed);
    }
    // go up
    if (glfwGetKey(m_Window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        m_Camera->setPosition(m_Camera->getPosition() + up * deltaTime * speed);
    }
    // go down
    if (glfwGetKey(m_Window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        m_Camera->setPosition(m_Camera->getPosition() - up * deltaTime * speed);
    }

    shader->setUniform3fv("ambiantLight", glm::vec3(0.1, 0.1, 0.1));

}
