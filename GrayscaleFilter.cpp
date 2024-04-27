#include "GrayscaleFilter.h"

const double RED_COEFF = 0.299;
const double GREEN_COEFF = 0.587;
const double BLUE_COEFF = 0.114;

void GrayscaleFilter::ApplyFilter(Image& img) {
    uint32_t height = img.GetHeight();
    uint32_t width = img.GetWidth();
    auto& vector_of_pixels = img.GetImageVector();

    uint8_t new_val = 0;

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            new_val = static_cast<uint8_t>(RED_COEFF * vector_of_pixels[i][j].red +
                                           GREEN_COEFF * vector_of_pixels[i][j].green +
                                           BLUE_COEFF * vector_of_pixels[i][j].blue);
            vector_of_pixels[i][j].red = new_val;
            vector_of_pixels[i][j].green = new_val;
            vector_of_pixels[i][j].blue = new_val;
        }
    }
}
