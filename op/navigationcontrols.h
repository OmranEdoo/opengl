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
    int getJumpingMode() { return this->jumpingMode; };
    void setJumpingMode(int jumpingMode) { this->jumpingMode = jumpingMode; };
    int getCountJumping() { return this->countJumping; };
    void setCountJumping(int countJumping) { this->countJumping = countJumping; };
    void incrCountJumping() { this->countJumping++; };
    int getJumpTreshhold() { return this->jumpTreshhold; };

private:
    glm::vec2 lastPosCursor;
    int mode;
    int jumpingMode;
    int countJumping;
    const int jumpTreshhold = 100;
};

#endif // NAVIGATIONCONTROLS_H
