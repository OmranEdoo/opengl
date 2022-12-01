#ifndef COLORBUFFER_H
#define COLORBUFFER_H

#include <vector>
#include <glm/glm.hpp>


class ColorBuffer
{
private:
    unsigned int m_rendererID;
    unsigned int size;
    unsigned int count;
public:
    ColorBuffer(const std::vector<glm::vec3>& data);
    virtual ~ColorBuffer();

    void Bind(int index) const;
    void Unbind() const;
    unsigned int getSize() const;
    unsigned int getCount() const;
};

#endif // COLORBUFFER_H
