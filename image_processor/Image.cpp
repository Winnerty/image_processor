#include "Image.h"

std::vector<std::vector<Color>>& Image::GetImageVector() {
    return image_vector_;
}

Image::BmpHeader& Image::GetBmpHeader() {
    return bmp_header_;
}

Image::DibHeader& Image::GetDibHeader() {
    return dib_header_;
}

const uint32_t Image::GetWidth() const {
    return dib_header_.bitmap_width;
}

const uint32_t Image::GetHeight() const {
    return dib_header_.bitmap_height;
}

void Image::SetWidth(uint32_t new_width) {
    dib_header_.bitmap_width = new_width;
}

void Image::SetHeight(uint32_t new_height) {
    dib_header_.bitmap_height = new_height;
}
