#include "navigationcontrols.h"
//#include "imgui/imgui.h"

NavigationControls::NavigationControls(GLFWwindow* window, Camera* camera, Object* object) : Controls(window, camera, object), lastPosCursor(-1, -1), mode(1), jumpingMode(0)
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
                //m_Camera->setPositionObject({ lastPosCursor.x, lastPosCursor.y, 0 });
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

        if (glfwGetKey(m_Window, GLFW_KEY_1) == GLFW_PRESS) {
            if (getMode() != 1)
                setMode(1);
        }
        if (glfwGetKey(m_Window, GLFW_KEY_2) == GLFW_PRESS) {
            if (getMode() != 2)
                setMode(2);
        }
        if (glfwGetKey(m_Window, GLFW_KEY_3) == GLFW_PRESS) {
            if (getMode() != 3)
                setMode(3);
        }
        if (getMode() == 1) {
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
        }

        if (getMode() == 3) {
            //glfwGetCursorPos(m_Window, &xpos, &ypos);
            //m_Camera->setPositionObject({ xpos, ypos, m_Object->getPosition()[2]});
            // Move forward
            if (glfwGetKey(m_Window, GLFW_KEY_UP) == GLFW_PRESS) {
                m_Object->setPosition(m_Object->getPosition() + direction * deltaTime * speed);
                m_Camera->setPosition(m_Camera->getPosition() + direction * deltaTime * speed);
            }
            // Move backward
            if (glfwGetKey(m_Window, GLFW_KEY_DOWN) == GLFW_PRESS) {
                m_Object->setPosition(m_Object->getPosition() - direction * deltaTime * speed);
                m_Camera->setPosition(m_Camera->getPosition() - direction * deltaTime * speed);
            }
            // Strafe right
            if (glfwGetKey(m_Window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
                m_Object->setPosition(m_Object->getPosition() + right * deltaTime * speed);
                m_Camera->setPosition(m_Camera->getPosition() + right * deltaTime * speed);
            }
            // Strafe left
            if (glfwGetKey(m_Window, GLFW_KEY_LEFT) == GLFW_PRESS) {
                m_Object->setPosition(m_Object->getPosition() - right * deltaTime * speed);
                m_Camera->setPosition(m_Camera->getPosition() - right * deltaTime * speed);
            }
            // Move forward
            if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS) {
                m_Object->setPosition(m_Object->getPosition() + direction * deltaTime * speed);
                m_Camera->setPosition(m_Camera->getPosition() + direction * deltaTime * speed);
            }
            // Move backward
            if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS) {
                m_Object->setPosition(m_Object->getPosition() - direction * deltaTime * speed);
                m_Camera->setPosition(m_Camera->getPosition() - direction * deltaTime * speed);
            }
            // Strafe right
            if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS) {
                m_Object->setPosition(m_Object->getPosition() + right * deltaTime * speed);
                m_Camera->setPosition(m_Camera->getPosition() + right * deltaTime * speed);
            }
            // Strafe left
            if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS) {
                m_Object->setPosition(m_Object->getPosition() - right * deltaTime * speed);
                m_Camera->setPosition(m_Camera->getPosition() - right * deltaTime * speed);
            }
            // go up
            if (glfwGetKey(m_Window, GLFW_KEY_SPACE) == GLFW_PRESS && getJumpingMode() == 0) {
                setJumpingMode(1);
                //m_Object->setPosition(m_Object->getPosition() + up * deltaTime * speed);
                //m_Camera->setPosition(m_Camera->getPosition() + up * deltaTime * speed);
            }
            // go down
            if (glfwGetKey(m_Window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
                m_Object->setPosition(m_Object->getPosition() - up * deltaTime * speed);
                m_Camera->setPosition(m_Camera->getPosition() - up * deltaTime * speed);
            }
        }
    }
}
