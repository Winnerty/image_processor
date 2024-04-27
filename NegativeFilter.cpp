#include "NegativeFilter.h"

const uint32_t RGB_MAX = 255;

void NegativeFilter::ApplyFilter(Image& img) {
    uint32_t width = img.GetWidth();
    uint32_t height = img.GetHeight();
    auto& vector_of_pixels = img.GetImageVector();

    for (uint32_t i = 0; i < height; ++i) {
        for (uint32_t j = 0; j < width; ++j) {
            vector_of_pixels[i][j].red = RGB_MAX - vector_of_pixels[i][j].red;
            vector_of_pixels[i][j].green = RGB_MAX - vector_of_pixels[i][j].green;
            vector_of_pixels[i][j].blue = RGB_MAX - vector_of_pixels[i][j].blue;
        }
    }
}