#include "camera.h"
#include "renderer.h"

Camera::Camera(float width, float height) :position(0, 0, 5), positionObject(0, 0, 0), horizontalAngle(3.14), verticalAngle(0), FoV(45)
{
    computeMatrices(width, height);
}

void Camera::computeMatrices(float width, float height)
{

    glm::vec3 direction(
        cos(getVerticalAngle()) * sin(getHorizontalAngle()),
        sin(getVerticalAngle()),
        cos(getVerticalAngle()) * cos(getHorizontalAngle())
    );

    // Right vector
    glm::vec3 right = glm::vec3(
        sin(getHorizontalAngle() - 3.14f / 2.0f),
        0,
        cos(getHorizontalAngle() - 3.14f / 2.0f)
    );

    // Up vector : perpendicular to both direction and right
    glm::vec3 up = glm::cross(right, direction);


    // Projection matrix : 45&deg; Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    projectionMatrix = glm::perspective(glm::radians(FoV), width / height, 0.1f, 100.0f);
    // Camera matrix
    viewMatrix = glm::lookAt(
        getPosition(),           // Camera is here
        getPosition()+direction, // and looks here : at the same position, plus "direction"
        up                  // Head is up (set to 0,-1,0 to look upside-down)
    );

}

const glm::mat4& Camera::getViewMatrix() const
{
    return viewMatrix;
}

const glm::mat4& Camera::getProjectionMatrix() const
{
    return this->projectionMatrix;
}

void Camera::Bind(Shader* shader)
{
    shader->setUniform3fv("camPosition", getPosition());
}

void Camera::lookAtCube() {
    setViewMatrix( glm::lookAt(
        getPosition(),
        getPositionObject(),
        glm::vec3(0,0,1)
    ) );
}

