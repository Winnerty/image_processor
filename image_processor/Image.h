#pragma once
#include <cstdint>
#include <vector>

struct Color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

class Image {
private:
    struct BmpHeader {
        uint16_t header_field;
        uint32_t bmp_size;
        uint16_t reserved_field1;
        uint16_t reserved_field2;
        uint32_t offset;
    };

    struct DibHeader {
        uint32_t header_size;
        uint32_t bitmap_width;
        uint32_t bitmap_height;
        uint16_t num_of_color_planes;
        uint16_t bits_per_pixel;
        uint32_t comp_method;
        uint32_t image_size;
        uint32_t horizontal_resolution;
        uint32_t vertical_resolution;
        uint32_t num_of_colors;
        uint32_t num_of_important_colors;
        uint8_t spam;
    };

    std::vector<std::vector<Color>> image_vector_;
    BmpHeader bmp_header_;
    DibHeader dib_header_;

public:
    std::vector<std::vector<Color>>& GetImageVector();
    BmpHeader& GetBmpHeader();
    DibHeader& GetDibHeader();
    const uint32_t GetWidth() const;
    const uint32_t GetHeight() const;
    void SetWidth(uint32_t new_width);
    void SetHeight(uint32_t new_height);
};
