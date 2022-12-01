#include "navigationcontrols.h"
//#include "imgui/imgui.h"

NavigationControls::NavigationControls(GLFWwindow* window, Camera* camera) :Controls(window, camera), lastPosCursor(-1, -1), mode(false)
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    mouseSpeed = 0.02;
}

void NavigationControls::update(float deltaTime, Shader* shader)
{


    // On test d'abord si on est sur la fen�tre imgui ou pas
    if (/*!io.WantCaptureMouse*/true) {

        int state = glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_LEFT);
        double xpos, ypos;
        glfwGetCursorPos(m_Window, &xpos, &ypos);
        if (state == GLFW_PRESS) {
            if (lastPosCursor.x != -1) {
                m_Camera->setHorizontalAngle(m_Camera->getHorizontalAngle() + mouseSpeed * deltaTime * float(xpos - lastPosCursor.x));
                m_Camera->setVerticalAngle(m_Camera->getVerticalAngle() + mouseSpeed * deltaTime * float(ypos - lastPosCursor.y));
            }
            lastPosCursor.x = xpos;
            lastPosCursor.y = ypos;
        }
        else {
            lastPosCursor = glm::vec2(-1, -1);
        }


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


        //
        if (glfwGetKey(m_Window, GLFW_KEY_ENTER) == GLFW_PRESS) {
            if (getMode())
                setMode(false);
            else
                setMode(true);
        }
        // Move forward
        if (glfwGetKey(m_Window, GLFW_KEY_UP) == GLFW_PRESS) {
            m_Camera->setPosition(m_Camera->getPosition() - direction * deltaTime * speed);
        }
        // Move backward
        if (glfwGetKey(m_Window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            m_Camera->setPosition(m_Camera->getPosition() + direction * deltaTime * speed);
        }
        // Strafe right
        if (glfwGetKey(m_Window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            m_Camera->setPosition(m_Camera->getPosition() - right * deltaTime * speed);
        }
        // Strafe left
        if (glfwGetKey(m_Window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            m_Camera->setPosition(m_Camera->getPosition() + right * deltaTime * speed);
        }
        // Move forward
        if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS) {
            m_Camera->setPosition(m_Camera->getPosition() - direction * deltaTime * speed);
        }
        // Move backward
        if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS) {
            m_Camera->setPosition(m_Camera->getPosition() + direction * deltaTime * speed);
        }
        // Strafe right
        if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS) {
            m_Camera->setPosition(m_Camera->getPosition() - right * deltaTime * speed);
        }
        // Strafe left
        if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS) {
            m_Camera->setPosition(m_Camera->getPosition() + right * deltaTime * speed);
        }
        // go up
        if (glfwGetKey(m_Window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            m_Camera->setPosition(m_Camera->getPosition() + up * deltaTime * speed);
        }
        // go down
        if (glfwGetKey(m_Window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            m_Camera->setPosition(m_Camera->getPosition() - up * deltaTime * speed);
        }
    }

}
