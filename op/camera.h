#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "shader.h"

class Camera
{
public:
    Camera(float width, float height);
    void computeMatrices(float width, float height);

    const glm::mat4& getViewMatrix() const;
    const glm::mat4& getProjectionMatrix() const;

    void Bind(Shader* shader);

    glm::vec3 getPosition() { return this->position; };
    glm::vec3 getPositionObject() { return this->positionObject; };
    float getHorizontalAngle() { return this->horizontalAngle; };
    float getVerticalAngle() { return this->verticalAngle; };

    void setFoV(float newFoV) { this->FoV = newFoV; };
    void setPosition( glm::vec3 position ) { this->position = position; };
    void setPositionObject( glm::vec3 positionObject ) { this->positionObject = positionObject; };
    void setHorizontalAngle( float horizontalAngle ) { this->horizontalAngle = horizontalAngle; };
    void setVerticalAngle( float verticalAngle ) { this->verticalAngle = verticalAngle; };

private:
    float FoV;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    glm::vec3 position;
    glm::vec3 positionObject;

    float horizontalAngle;
    float verticalAngle;
};

#endif // CAMERA_H
