#include "CropFilter.h"

CropFilter::CropFilter(uint32_t new_width, uint32_t new_height) : new_width_(new_width), new_height_(new_height) {
}

void CropFilter::ApplyFilter(Image& img) {
    uint32_t current_height = img.GetHeight();
    uint32_t current_width = img.GetWidth();

    new_height_ = std::min(new_height_, current_height);
    new_width_ = std::min(new_width_, current_width);

    auto& vector_of_pixels = img.GetImageVector();
    std::vector<std::vector<Color>> vector_of_pixels_new(new_height_, std::vector<Color>(new_width_));

    for (size_t i = current_height - new_height_; i < current_height; ++i) {
        for (size_t j = 0; j < new_width_; ++j) {
            vector_of_pixels_new[i - current_height + new_height_][j].red = vector_of_pixels[i][j].red;
            vector_of_pixels_new[i - current_height + new_height_][j].green = vector_of_pixels[i][j].green;
            vector_of_pixels_new[i - current_height + new_height_][j].blue = vector_of_pixels[i][j].blue;
        }
    }

    vector_of_pixels = std::move(vector_of_pixels_new);
    img.SetHeight(new_height_);
    img.SetWidth(new_width_);
}
