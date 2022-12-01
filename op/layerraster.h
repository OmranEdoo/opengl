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
    const char* getGeotiffProjection();
    const std::vector<glm::vec3> normalizeVector(std::vector<glm::vec3> data, int max, int treshhold);
    void createIndexTable();
    void createVerticesVector();

    std::string getFilePath() { return this->filePath; };
    GDALDataset* getGeotiffData() { return this->geotiffData; };
    int getMaxX() { return this->maxX; };
    int getMaxY() { return this->maxY; };
    int getMaxZ() { return this->maxZ; };
    int getWidthTIFF() { return this->widthTIFF; };
    int getHeightTIFF() { return this->heightTIFF; };
    int getNumberOfBands() { return this->numberOfBands; };
    std::vector<glm::vec3> getVerticesVector() { return this->verticesVector; };
    std::vector<unsigned int> getIndexTable() { return this->indexTable; };
    std::vector<glm::vec2> getUvVector() { return this->uvVector; };
    std::vector<glm::vec3> getColors() { return this->colors; };

    void setFilePath(std::string filePath) { this->filePath = filePath; };
    void setGeotiffData(GDALDataset* geotiffData) { this->geotiffData = geotiffData; };
    void setMaxX( int maxX ) { this->maxX = maxX; };
    void setMaxY( int maxY ) { this->maxY = maxY; };
    void setMaxZ( int maxZ ) { this->maxZ = maxZ; };
    void setWidthTIFF( int widthTIFF ) { this->widthTIFF = widthTIFF; };
    void setHeightTIFF( int heightTIFF ) { this->heightTIFF = heightTIFF; };
    void setNumberOfBands( int numberOfBands ) { this->numberOfBands = numberOfBands; };
    void setVerticesVector( std::vector<glm::vec3> verticeVector ) { this->verticesVector = verticeVector; };
    void setIndexTable( std::vector<unsigned int> indexTable ) { this->indexTable = indexTable; };
    void setUvVector( std::vector<glm::vec2> uvVector ) { this->uvVector = uvVector; };
    void setColors( std::vector<glm::vec3> colors ) { this->colors = colors; };

    void pushVerticesVector( glm::vec3 vertice ) { this->verticesVector.push_back(vertice); };
    void pushIndexTable( unsigned int index ) { this->indexTable.push_back(index); };
    void pushUvVector( glm::vec2 uv ) { this->uvVector.push_back(uv); };
    void pushColors( glm::vec3 color ) { this->colors.push_back(color); };


private:
    std::string filePath;
    GDALDataset* geotiffData; // data in the GDALDataset format

    int maxX;
    int maxY;
    int maxZ;
    int widthTIFF;
    int heightTIFF;
    int numberOfBands; // number of raster bands
    std::vector<glm::vec3> verticesVector; // data that will be put in the vertexBuffer
    std::vector<unsigned int> indexTable; // data that will be put in the indexBuffer
    std::vector<glm::vec2> uvVector;
    std::vector<glm::vec3> colors;
};

#endif // LAYERRASTER_H
