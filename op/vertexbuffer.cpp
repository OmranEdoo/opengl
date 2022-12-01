#include "vertexbuffer.h"
#include "renderer.h"

unsigned int VertexBuffer::getSize() const
{
    return bufferSize;
}

unsigned int VertexBuffer::getCount() const
{
    return bufferCount;
}

VertexBuffer::VertexBuffer(const std::vector<glm::vec3>& bufferData, const std::vector<unsigned int> indexData) : bufferSize(bufferData.size() * sizeof(glm::vec3)), indexSize(indexData.size() * sizeof(unsigned int))
{
    bufferCount = bufferSize / sizeof(bufferData[0]);
    (glGenBuffers(1, &m_rendererID));
    (glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
    (glBufferData(GL_ARRAY_BUFFER, bufferSize, &bufferData[0], GL_STATIC_DRAW));
    
    // Generate a buffer for the indices
    indexCount = indexSize / sizeof(indexData[0]);
    glGenBuffers(1, &m_indexID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, &indexData[0], GL_STATIC_DRAW);

}


VertexBuffer::~VertexBuffer() {
    (glDeleteBuffers(1, &m_rendererID));
    (glDeleteBuffers(1, &m_indexID));
}

void VertexBuffer::Bind(int index) const {
    (glEnableVertexAttribArray(index));
    (glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
    (glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexID));
    (glVertexAttribPointer(
        index,                  // l'index du point � modifier.
        3,                  // taille d'un point
        GL_FLOAT,           // type de valeur
        GL_FALSE,           // normalisation?
        0,                  // taille des valeurs suppl�mentaires dans le vertexbuffer
        (void*)0            // offset : est-ce qu'on commence � un autre indice que 0
    ));
}

void VertexBuffer::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
