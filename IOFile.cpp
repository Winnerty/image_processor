#include "IOFile.h"

const uint16_t BMP_HEADER_NAME = 0x4D42;
const std::string BMP_FILE_ERROR = "This is not a BMP file.";
const std::string OPEN_ERROR = "Error opening your file.";

const uint8_t PADDING_COEFF_4 = 4;
const uint8_t PADDING_COEFF_3 = 3;

void IOFile::Download(Image &img) {
    std::ifstream file_stream;
    try {
        file_stream.open(input_path_, std::ios::binary);
    } catch (...) {
        throw OPEN_ERROR;
    }

    auto &bmp_header = img.GetBmpHeader();
    auto &dib_header = img.GetDibHeader();

    file_stream.read(reinterpret_cast<char *>(&bmp_header.header_field), sizeof(uint16_t));
    file_stream.read(reinterpret_cast<char *>(&bmp_header.bmp_size), sizeof(uint32_t));
    file_stream.read(reinterpret_cast<char *>(&bmp_header.reserved_field1), sizeof(uint16_t));
    file_stream.read(reinterpret_cast<char *>(&bmp_header.reserved_field2), sizeof(uint16_t));
    file_stream.read(reinterpret_cast<char *>(&bmp_header.offset), sizeof(uint32_t));

    if (bmp_header.header_field != BMP_HEADER_NAME) {
        throw BMP_FILE_ERROR;
    }

    file_stream.read(reinterpret_cast<char *>(&dib_header.header_size), sizeof(uint32_t));
    file_stream.read(reinterpret_cast<char *>(&dib_header.bitmap_width), sizeof(uint32_t));
    file_stream.read(reinterpret_cast<char *>(&dib_header.bitmap_height), sizeof(uint32_t));
    file_stream.read(reinterpret_cast<char *>(&dib_header.num_of_color_planes), sizeof(uint16_t));
    file_stream.read(reinterpret_cast<char *>(&dib_header.bits_per_pixel), sizeof(uint16_t));
    file_stream.read(reinterpret_cast<char *>(&dib_header.comp_method), sizeof(uint32_t));
    file_stream.read(reinterpret_cast<char *>(&dib_header.image_size), sizeof(uint32_t));
    file_stream.read(reinterpret_cast<char *>(&dib_header.horizontal_resolution), sizeof(uint32_t));
    file_stream.read(reinterpret_cast<char *>(&dib_header.vertical_resolution), sizeof(uint32_t));
    file_stream.read(reinterpret_cast<char *>(&dib_header.num_of_colors), sizeof(uint32_t));
    file_stream.read(reinterpret_cast<char *>(&dib_header.num_of_important_colors), sizeof(uint32_t));

    auto &vector_of_pixels = img.GetImageVector();
    vector_of_pixels.assign(dib_header.bitmap_height, std::vector<Color>(dib_header.bitmap_width));
    uint32_t padding =
        (PADDING_COEFF_4 - ((dib_header.bitmap_width * PADDING_COEFF_3) % PADDING_COEFF_4)) & PADDING_COEFF_3;

    for (size_t i = 0; i < dib_header.bitmap_height; ++i) {
        for (size_t j = 0; j < dib_header.bitmap_width; ++j) {
            vector_of_pixels[i][j].blue = file_stream.get();
            vector_of_pixels[i][j].green = file_stream.get();
            vector_of_pixels[i][j].red = file_stream.get();
        }
        file_stream.seekg(padding, std::ios::cur);
    }
    file_stream.close();
}

void IOFile::Upload(Image &img) {
    std::ofstream file_stream;
    try {
        file_stream.open(output_path_, std::ios::binary);
    } catch (...) {
        throw OPEN_ERROR;
    }

    auto &bmp_header = img.GetBmpHeader();
    auto &dib_header = img.GetDibHeader();

    file_stream.write(reinterpret_cast<char *>(&bmp_header.header_field), sizeof(uint16_t));
    file_stream.write(reinterpret_cast<char *>(&bmp_header.bmp_size), sizeof(uint32_t));
    file_stream.write(reinterpret_cast<char *>(&bmp_header.reserved_field1), sizeof(uint16_t));
    file_stream.write(reinterpret_cast<char *>(&bmp_header.reserved_field2), sizeof(uint16_t));
    file_stream.write(reinterpret_cast<char *>(&bmp_header.offset), sizeof(uint32_t));
    file_stream.write(reinterpret_cast<char *>(&dib_header.header_size), sizeof(uint32_t));
    file_stream.write(reinterpret_cast<char *>(&dib_header.bitmap_width), sizeof(uint32_t));
    file_stream.write(reinterpret_cast<char *>(&dib_header.bitmap_height), sizeof(uint32_t));
    file_stream.write(reinterpret_cast<char *>(&dib_header.num_of_color_planes), sizeof(uint16_t));
    file_stream.write(reinterpret_cast<char *>(&dib_header.bits_per_pixel), sizeof(uint16_t));
    file_stream.write(reinterpret_cast<char *>(&dib_header.comp_method), sizeof(uint32_t));
    file_stream.write(reinterpret_cast<char *>(&dib_header.image_size), sizeof(uint32_t));
    file_stream.write(reinterpret_cast<char *>(&dib_header.horizontal_resolution), sizeof(uint32_t));
    file_stream.write(reinterpret_cast<char *>(&dib_header.vertical_resolution), sizeof(uint32_t));
    file_stream.write(reinterpret_cast<char *>(&dib_header.num_of_colors), sizeof(uint32_t));
    file_stream.write(reinterpret_cast<char *>(&dib_header.num_of_important_colors), sizeof(uint32_t));

    auto &vector_of_pixels = img.GetImageVector();
    uint32_t padding =
        (PADDING_COEFF_4 - ((dib_header.bitmap_width * PADDING_COEFF_3) % PADDING_COEFF_4)) & PADDING_COEFF_3;

    for (size_t i = 0; i < dib_header.bitmap_height; ++i) {
        for (size_t j = 0; j < dib_header.bitmap_width; ++j) {
            file_stream.write(reinterpret_cast<char *>(&vector_of_pixels[i][j].blue), sizeof(uint8_t));
            file_stream.write(reinterpret_cast<char *>(&vector_of_pixels[i][j].green), sizeof(uint8_t));
            file_stream.write(reinterpret_cast<char *>(&vector_of_pixels[i][j].red), sizeof(uint8_t));
        }
        for (size_t j = 0; j < padding; ++j) {
            file_stream.write(reinterpret_cast<char *>(&dib_header.spam), sizeof(uint8_t));
        }
    }
    file_stream.close();
}
