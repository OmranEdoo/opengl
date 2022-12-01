#include "object.h"

#include <iostream>
#include "renderer.h"
#include "glm/gtx/transform.hpp"

#include <exception>




Object::Object(std::vector<glm::vec3> vertices, std::vector<unsigned int> indexs, std::vector<glm::vec2> uvs, std::vector< glm::vec3 > colors, std::string texturePath) :m_vb(0), m_uvsb(0), indexCount(indexs.size())
{
    setPosition({ 0, 0, 0 });
    setRotationAngles({ 0, 0, 0 });

    m_vb = new VertexBuffer(vertices, indexs);
    m_uvsb = new UVBuffer(uvs);
    m_vc = new ColorBuffer(colors);

    m_texture = new Texture(texturePath);
}


Object::~Object()
{
    delete m_vb;
    delete m_vc;
    if (m_uvsb) delete m_uvsb;
    if (m_texture) delete m_texture;
}

void Object::Bind() const
{
    m_vb->Bind(0);
    m_vc->Bind(2);
    if (m_uvsb) m_uvsb->Bind(1);
    if (m_texture) m_texture->Bind(0);
}

void Object::Unbind() const
{
    m_vb->Unbind();
    m_vc->Unbind();
    if (m_uvsb) m_uvsb->Unbind();
    if (m_texture) m_texture->Unbind();
}



void Object::Draw() const
{
    glDrawElements(
        GL_TRIANGLES,      // mode
        this->indexCount,    // count
        GL_UNSIGNED_INT,   // type
        (void*)0           // element array buffer offset
    );
}


glm::mat4 Object::getModelMatrix()
{
    glm::mat4 m = glm::rotate(glm::translate(glm::mat4(1), getPosition()), getRotationAngles()[0], glm::vec3(1, 0, 0));
    m = glm::rotate(m, getRotationAngles()[1], glm::vec3(0, 1, 0));
    m = glm::rotate(m, getRotationAngles()[2], glm::vec3(0, 0, 1));
    return m;
}
