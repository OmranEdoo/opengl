#ifndef NAVIGATIONCONTROLS_H
#define NAVIGATIONCONTROLS_H

#include "controls.h"

class NavigationControls : public Controls
{
public:
    NavigationControls(GLFWwindow* window, Camera* camera);
    void update(float deltaTime, Shader* shader);
    bool getMode() { return this->mode; };
    void setMode(bool mode) { this->mode = mode; };

private:
    glm::vec2 lastPosCursor;
    bool mode;
};

#endif // NAVIGATIONCONTROLS_H
