#ifndef LAYERRASTER_H
#define LAYERRASTER_H

#include "gdal_priv.h"
#include <glm/glm.hpp>

#include <string>
#include <vector>

class LayerRaster
{
public:
    LayerRaster(std::string filePath);
    void openGeotiff(); // file loader function
    int* getGeotiffSize();
    float* getGeotiffOrigin();
    float* getPixelSize();
    std::vector<glm::vec3> verticesVector; // data that will be put in the vertexBuffer
    std::vector<unsigned int> indexTable; // data that will be put in the indexBuffer
    std::vector<glm::vec3> colors; // data that will be put in the vertexBuffer
    std::vector<unsigned int> indexColor; // data that will be put in the indexBuffer
    int widthTIFF;
    int heightTIFF;
    int numberOfBands; // number of raster bands
    const char* getGeotiffProjection();
    void createIndexTable();
    void createVerticesVector();
    int maxX;
    int maxY;
    int maxZ;

private:
    std::string filePath;
    GDALDataset* geotiffData; // data in the GDALDataset format
};

#endif // LAYERRASTER_H
