#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <vector>
#include "glm/glm.hpp"

class VertexBuffer
{
private:
    unsigned int m_rendererID;
    unsigned int m_indexID;
    unsigned int bufferSize;
    unsigned int indexSize;
    unsigned int bufferCount;
    unsigned int indexCount;

public:
    VertexBuffer(const std::vector<glm::vec3>& data, const std::vector<unsigned int>);
    virtual ~VertexBuffer();

    void Bind(int index) const;
    void Unbind() const;
    unsigned int getSize() const;
    unsigned int getCount() const;
};

#endif // VERTEXBUFFER_H
