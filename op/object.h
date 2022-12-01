#ifndef OBJECT_H
#define OBJECT_H

#include <string>

#include <glm/glm.hpp>

#include "vertexbuffer.h"
#include "vertexarray.h"
#include "texture.h"
#include "uvbuffer.h"
#include "colorbuffer.h"


class Object
{
public:
    Object(std::vector< glm::vec3 > vertices, std::vector<unsigned int> indexs, std::vector< glm::vec2 > uvs, std::vector< glm::vec3 > colors, std::string texturePath);
    ~Object();
    void Bind() const;
    void Unbind() const;
    void Draw() const;
    unsigned int indexCount;

    glm::mat4 getModelMatrix();
    glm::vec3 getPosition() { return this->position; };
    glm::vec3 getRotationAngles() { return this->rotationAngles; };

    void setPosition( glm::vec3 position) { this->position = position; };
    void setRotationAngles( glm::vec3 rotationAngles ) { this->rotationAngles = rotationAngles; };

private:
    VertexBuffer* m_vb;
    UVBuffer* m_uvsb;
    Texture* m_texture;
    ColorBuffer* m_vc;

    glm::vec3 position;
    glm::vec3 rotationAngles;


    //Texture* m_texture;


};

#endif // OBJECT_H
