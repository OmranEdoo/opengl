#include "layerraster.h"
#include <iostream>
#include "cpl_conv.h" // for CPLMalloc()
#include <stdlib.h>


LayerRaster::LayerRaster(std::string filePath)
{
    setFilePath(filePath);
    
    openGeotiff();

    // initialisation of width/height/bands
    setWidthTIFF(getGeotiffSize()[0]);
    setHeightTIFF(getGeotiffSize()[1]);
    setNumberOfBands(getGeotiffSize()[2]);

    createIndexTable();
    createVerticesVector();

    setVerticesVector(normalizeVector(getVerticesVector(), getMaxZ(), 50));
}


void LayerRaster::openGeotiff()
{
    /* Connexion to GeoTIFF using GDAL */

    GDALAllRegister();
    setGeotiffData((GDALDataset*)GDALOpen(getFilePath().c_str(), GA_ReadOnly));
}


const std::vector<glm::vec3> LayerRaster::normalizeVector(std::vector<glm::vec3> data, int max, int treshhold) {
    
    std::vector<glm::vec3> newData;

    int i = 0;
    
    for (glm::vec3 coordinates : data) {

        i++;

        int normalizedValue = coordinates[2] / max * treshhold;

        newData.push_back(glm::vec3(coordinates[0], coordinates[1], normalizedValue));

        int snowTreshhold = rand() % 6 + 40;
        int rockTreshhold = rand() % 6 + 34;

        if (normalizedValue > snowTreshhold) {
            pushColors({ 1.0f+(1- getUvVector()[i][0]), 1.0f + (1 - getUvVector()[i][0]), 1.0f + (1 - getUvVector()[i][0]) });
        }
        else if (normalizedValue > rockTreshhold) {
            pushColors({ 0.4f, 0.3f, 0.3f });
        }
        else {
            pushColors({ 0.1f, 0.1f, 0.1f });
        }
    }

    return newData;
}


void LayerRaster::createIndexTable()
{
    // IndexTable is a table that'll store indexBuffer data associated to dataTIFF to create triangles
    int tableSize = (8 + (getWidthTIFF() + getHeightTIFF() - 4 + (getWidthTIFF() - 1) * (getHeightTIFF() - 1)) * 6) * getNumberOfBands();
    std::vector<unsigned int> indexTable;
    // the loop will store each time 6 values of IndexTable for 2 triangles
    for (int i = 0; i < getHeightTIFF() - 1; i++) {
        for (int j = 0; j < getWidthTIFF(); j++) {
            // first triangle
            // point in line i and column j, 6 means each time the values restart from the 7th value and k if there are different raster bands
            pushIndexTable( i * getWidthTIFF() + j);
            // point in line i+1 and column j
            pushIndexTable( (i + 1) * getWidthTIFF() + j );
            // point in line i+1 and column j+1
            pushIndexTable( (i + 1) * getWidthTIFF() + j + 1);

            // second triangle
            // point in line i and column j
            pushIndexTable( i * getWidthTIFF() + j );
            // point in line i and column j+1
            pushIndexTable( i * getWidthTIFF() + j + 1 );
            // point in line i+1 and column j+1
            pushIndexTable( (i + 1) * getWidthTIFF() + j + 1 );
        }
    }

    //setIndexTable(indexTable);
}


void LayerRaster::createVerticesVector() {
    // result defines a list of GeoTIFF pixel data
    // new float[this->widthTIFF * this->heightTIFF * this->numberOfBands];
    GDALRasterBand* rasterBand = getGeotiffData()->GetRasterBand(1);

    float* pafScanline;
    pafScanline = (float*)CPLMalloc(sizeof(float) * getWidthTIFF() * getHeightTIFF());

    setMaxZ(0);

    // RasterIO function browse the raster bands and store the data in the pafscanline
    if (rasterBand->RasterIO(GF_Read, 0, 0, getWidthTIFF(), getHeightTIFF(), pafScanline, getWidthTIFF(), getHeightTIFF(), GDT_Float32, 0, 0) == CE_None) {
        // Construct a height map based on the xres and yres for each group of four dots
        for (int i = 0; i < getHeightTIFF(); i++)
        {
            for (int j = 0; j < getWidthTIFF(); j++)
            {
                int value = pafScanline[i * getWidthTIFF() + j];

                    pushVerticesVector({ j, i, value });

                    pushUvVector({(float)j/(getWidthTIFF()-1), (getHeightTIFF()-1 - (float)i) / (getHeightTIFF()-1)});

                    if (getMaxZ() < value) {
                        setMaxZ(value);
                        setMaxX(j);
                        setMaxY(i);
                    }
            }
        }
    }
    else {
        std::cout << "Error: can't read raster bands" << std::endl;
    }

    CPLFree(pafScanline);
}


int* LayerRaster::getGeotiffSize()
{
    if (getGeotiffData() == NULL)
    {
        std::cout << "Fail to open the GeoTIFF" << std::endl;
        return NULL;
    }

    int* dataArray = new int[3];
    // Dimensions
    dataArray[0] = getGeotiffData()->GetRasterXSize();
    dataArray[1] = getGeotiffData()->GetRasterYSize();
    // Nb of Bands
    dataArray[2] = getGeotiffData()->GetRasterCount();

    return dataArray;
}


float* LayerRaster::getGeotiffOrigin()
{
    double adfGeoTransform[6];

    if (getGeotiffData()->GetGeoTransform(adfGeoTransform) != CE_None)
    {
        return NULL;
    }

    float* dataArray = new float[2];
    // Origin location
    dataArray[0] = adfGeoTransform[0];
    dataArray[1] = adfGeoTransform[3];

    return dataArray;
}


float* LayerRaster::getPixelSize()
{
    double adfGeoTransform[6];

    if (getGeotiffData()->GetGeoTransform(adfGeoTransform) != CE_None)
    {
        return NULL;
    }

    float* dataArray = new float[2];
    // Pixel size
    dataArray[0] = adfGeoTransform[1];
    dataArray[1] = adfGeoTransform[5];

    return dataArray;
}


const char* LayerRaster::getGeotiffProjection()
{
    if (getGeotiffData() == NULL)
    {
        std::cout << "Fail to open the GeoTIFF" << std::endl;
        return 0;
    }
    const char* projection = getGeotiffData()->GetProjectionRef();

    return projection;
}
