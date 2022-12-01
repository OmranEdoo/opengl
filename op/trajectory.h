#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <cmath>

#include "glm/glm.hpp"
#include "layerraster.h"


class Trajectory
{

public:
    Trajectory();
    ~Trajectory();

    glm::vec3 computePositions(int radius, float angle, LayerRaster mntLayer);
};

#endif // TRAJECTORY_H