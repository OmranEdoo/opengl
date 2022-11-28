#include "vertexarray.h"
#include "renderer.h"

VertexArray::VertexArray()
{
    (glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
    (glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::Bind() const
{
    (glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
    (glBindVertexArray(0));
}
