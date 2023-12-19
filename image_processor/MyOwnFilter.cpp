#include "MyOwnFilter.h"

const int32_t COLOR_MAX = 255;

MyOwnFilter::MyOwnFilter(double saturation_value) : saturation_value_(saturation_value) {
}

void MyOwnFilter::ApplyFilter(Image& img) {
    auto& vector_of_pixels = img.GetImageVector();
    uint32_t height = img.GetHeight();
    uint32_t width = img.GetWidth();
    double max_val = 0;
    double min_val = 0;
    double delta = 0;
    double lum = 0;
    double sat = 0;
    double alpha = 0;

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            max_val = std::max(std::max(vector_of_pixels[i][j].red, vector_of_pixels[i][j].green),
                               vector_of_pixels[i][j].blue);
            min_val = std::min(std::min(vector_of_pixels[i][j].red, vector_of_pixels[i][j].green),
                               vector_of_pixels[i][j].blue);
            delta = max_val - min_val;

            if (delta > 0) {
                lum = (max_val + min_val) / 2;
                sat = delta / (1 - std::abs(static_cast<double>(2) * lum - 1));
                alpha = saturation_value_ - 1;

                vector_of_pixels[i][j].red =
                    std::min(std::max(static_cast<int32_t>(vector_of_pixels[i][j].red +
                                                           (vector_of_pixels[i][j].red - lum) * alpha * sat),
                                      0),
                             COLOR_MAX);
                vector_of_pixels[i][j].green =
                    std::min(std::max(static_cast<int32_t>(vector_of_pixels[i][j].green +
                                                           (vector_of_pixels[i][j].green - lum) * alpha * sat),
                                      0),
                             COLOR_MAX);
                vector_of_pixels[i][j].blue =
                    std::min(std::max(static_cast<int32_t>(vector_of_pixels[i][j].blue +
                                                           (vector_of_pixels[i][j].blue - lum) * alpha * sat),
                                      0),
                             COLOR_MAX);
            }
        }
    }
}
