#include "Image.h"
#include "Framebuffer.h"
#include <fstream>
#include <iostream>

Image::~Image()
{
    delete[] buffer;
}

bool Image::Load(const std::string& filename, uint8_t alpha)
{
    std::ifstream stream(filename, std::ios::binary);
    if (stream.fail())
    {
        std::cout << "Error: Cannot open file: " << filename << std::endl;
        return false;
    }

    uint8_t header[54];
    stream.read((char*)header, 54);

    uint16_t id = *((uint16_t*)(header));
    if (id != 'MB')
    {
        std::cout << "Error: Invalid file format: " << filename << std::endl;
        return false;
    }

    // get the image width and height
    width = *((int*)(&header[18]));
    height = *((int*)(&header[22]));

    // set the image pitch (uses color_t (RGBA) for pixel)
    int pitch = width * sizeof(color_t);

    // create the image buffer 
    buffer = new uint8_t[width * pitch];

    // get bits per pixel and bytes per pixel
    uint16_t bitsPerPixel = *((uint16_t*)(&header[28]));
    uint16_t bytesPerPixel = bitsPerPixel / 8;

    // calculate size of images (width * height * bytes per pixel)
    size_t size = width * height * bytesPerPixel;

    // create data buffer to read image from file
    uint8_t* data = new uint8_t[size];

    // read file into data buffer
    stream.read((char*)data, size);
       
    for (int i = 0; i < width * height; i++)
    {
        color_t color;

        // colors in bmp data are stored (BGR)
        int index = i * bytesPerPixel;
        color.b = data[index];
        color.g = data[index + 1];
        color.r = data[index + 2];
        color.a = alpha;

        ((color_t*)(buffer))[i] = color;
    }

    delete[] data;
    stream.close();

    return true;
}

void Image::Flip()
{
    // set the pitch (width * number of bytes per pixel)
    int pitch = width * sizeof(color_t);
    
    // create temporary line to store data
    uint8_t* temp = new uint8_t[pitch];
    
    for (int i = 0; i < height / 2; i++)
    {
        uint8_t* line1 = &((buffer)[i * pitch]);
        uint8_t* line2 = &((buffer)[((height - 1) - i) * pitch]);
        memcpy(temp, line1, pitch);
        memcpy(line1, line2, pitch);
        memcpy(line2, temp, pitch);
    }
    delete[] temp;
}