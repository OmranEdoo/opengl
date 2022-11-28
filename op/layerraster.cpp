#include "layerraster.h"
#include <iostream>
#include "cpl_conv.h" // for CPLMalloc()


LayerRaster::LayerRaster(std::string filePath)
{
    this->filePath = filePath;
    
    //this->colors = { glm::vec3(0.0f, 0.6f, 0.4f) };

    openGeotiff();

    // initialisation of width/height/bands
    this->widthTIFF = getGeotiffSize()[0];
    this->heightTIFF = getGeotiffSize()[1];
    this->numberOfBands = getGeotiffSize()[2];

    createIndexTable();
    createVerticesVector();
}


void LayerRaster::openGeotiff()
{
    /* Connexion to GeoTIFF using GDAL */

    GDALAllRegister();
    this->geotiffData = (GDALDataset*)GDALOpen(this->filePath.c_str(), GA_ReadOnly);
}


void LayerRaster::createIndexTable()
{
    // IndexTable is a table that'll store indexBuffer data associated to dataTIFF to create triangles
    int tableSize = (8 + (this->widthTIFF + this->heightTIFF - 4 + (this->widthTIFF - 1) * (this->heightTIFF - 1)) * 6) * this->numberOfBands;
    std::vector<unsigned int> indexTable;
    std::vector<unsigned int> indexColor;
    // the loop will store each time 6 values of IndexTable for 2 triangles
    for (int i = 0; i < this->heightTIFF - 1; i++) {
        for (int j = 0; j < this->widthTIFF; j++) {
            // first triangle
            // point in line i and column j, 6 means each time the values restart from the 7th value and k if there are different raster bands
            indexTable.push_back( i * this->widthTIFF + j );
            // point in line i+1 and column j
            indexTable.push_back( (i + 1) * this->widthTIFF + j );
            // point in line i+1 and column j+1
            indexTable.push_back( (i + 1) * this->widthTIFF + j + 1);

            // second triangle
            // point in line i and column j
            indexTable.push_back( i * this->widthTIFF + j );
            // point in line i and column j+1
            indexTable.push_back( i * this->widthTIFF + j + 1 );
            // point in line i+1 and column j+1
            indexTable.push_back( (i + 1) * this->widthTIFF + j + 1 );

            // Colors
            indexColor.push_back(0);
            indexColor.push_back(0);
            indexColor.push_back(0);
            indexColor.push_back(0);
            indexColor.push_back(0);
            indexColor.push_back(0);
        }
    }

    this->indexTable = indexTable;
    this->indexColor = indexColor;
}


void LayerRaster::createVerticesVector() {
    // result defines a list of GeoTIFF pixel data
    // new float[this->widthTIFF * this->heightTIFF * this->numberOfBands];
    GDALRasterBand* rasterBand = this->geotiffData->GetRasterBand(1);

    float* pafScanline;
    pafScanline = (float*)CPLMalloc(sizeof(float) * this->widthTIFF * this->heightTIFF);

    this->maxZ = 0;

    // RasterIO function browse the raster bands and store the data in the pafscanline
    if (rasterBand->RasterIO(GF_Read, 0, 0, this->widthTIFF, this->heightTIFF, pafScanline, this->widthTIFF, this->heightTIFF, GDT_Float32, 0, 0) == CE_None) {
        // Construct a height map based on the xres and yres for each group of four dots
        for (int i = 0; i < this->heightTIFF; i++)
        {
            for (int j = 0; j < this->widthTIFF; j++)
            {
                if (pafScanline[i * this->widthTIFF + j] > 0) {
                    this->verticesVector.push_back({ i, j, pafScanline[i * this->widthTIFF + j] });
                    this->colors.push_back(glm::vec3(0.0f, 0.6f, 0.4f));

                    if (this->maxZ < pafScanline[i * this->widthTIFF + j]) {
                        this->maxZ = pafScanline[i * this->widthTIFF + j];
                        this->maxX = i;
                        this->maxY = j;
                    }
                }
                else // values can not be negative
                    this->verticesVector.push_back({ i, j, 0 });
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
    if (this->geotiffData == NULL)
    {
        std::cout << "Fail to open the GeoTIFF" << std::endl;
        return NULL;
    }

    int* dataArray = new int[3];
    // Dimensions
    dataArray[0] = this->geotiffData->GetRasterXSize();
    dataArray[1] = this->geotiffData->GetRasterYSize();
    // Nb of Bands
    dataArray[2] = this->geotiffData->GetRasterCount();

    return dataArray;
}


float* LayerRaster::getGeotiffOrigin()
{
    double adfGeoTransform[6];

    if (this->geotiffData->GetGeoTransform(adfGeoTransform) != CE_None)
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

    if (this->geotiffData->GetGeoTransform(adfGeoTransform) != CE_None)
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
    if (this->geotiffData == NULL)
    {
        std::cout << "Fail to open the GeoTIFF" << std::endl;
        return 0;
    }
    const char* projection = this->geotiffData->GetProjectionRef();

    return projection;
}
