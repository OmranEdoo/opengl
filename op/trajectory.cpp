#include "trajectory.h"


Trajectory::Trajectory() {

}

Trajectory::~Trajectory() {

}

glm::vec3 Trajectory::computePositions(int radius, float angle, LayerRaster mntLayer) {
	float x = radius * cos(angle) + mntLayer.getMaxX() - radius / 2;
	float y = radius * sin(angle) + mntLayer.getMaxY() - radius / 2;
	float z = mntLayer.getVerticesVector()[(int)x + (int)y * mntLayer.getWidthTIFF()][2] + 1;
	
	return glm::vec3(x, y, z);
}


