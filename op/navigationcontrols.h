#ifndef NAVIGATIONCONTROLS_H
#define NAVIGATIONCONTROLS_H

#include "controls.h"
#include "object.h"


class NavigationControls : public Controls
{
public:
    NavigationControls(GLFWwindow* window, Camera* camera, Object* object);
    void update(float deltaTime, Shader* shader);
    int getMode() { return this->mode; };
    void setMode(int mode) { this->mode = mode; };

private:
    glm::vec2 lastPosCursor;
    int mode;
};

#endif // NAVIGATIONCONTROLS_H
