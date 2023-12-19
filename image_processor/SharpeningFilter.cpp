#include "SharpeningFilter.h"

const int COLOR_MAX = 255;
const int COLOR_MIN = 0;
const int SHARPENING_COEFF_3 = 3;
const int SHARPENING_COEFF_4 = 4;
const int SHARPENING_COEFF_5 = 5;

void SharpeningFilter::ApplyFilter(Image& img) {
    uint32_t height = img.GetHeight();
    uint32_t width = img.GetWidth();
    auto& vector_of_pixels = img.GetImageVector();
    std::vector<std::vector<Color>> vector_of_pixels_new(height, std::vector<Color>(width));

    vector_of_pixels_new[0][0].red =
        std::min(COLOR_MAX, std::max(COLOR_MIN, SHARPENING_COEFF_3 * vector_of_pixels[0][0].red -
                                                    vector_of_pixels[1][0].red - vector_of_pixels[0][1].red));
    vector_of_pixels_new[0][0].green =
        std::min(COLOR_MAX, std::max(COLOR_MIN, SHARPENING_COEFF_3 * vector_of_pixels[0][0].green -
                                                    vector_of_pixels[1][0].green - vector_of_pixels[0][1].green));
    vector_of_pixels_new[0][0].blue =
        std::min(COLOR_MAX, std::max(COLOR_MIN, SHARPENING_COEFF_3 * vector_of_pixels[0][0].blue -
                                                    vector_of_pixels[1][0].blue - vector_of_pixels[0][1].blue));

    vector_of_pixels_new[0][width - 1].red =
        std::min(COLOR_MAX, std::max(COLOR_MIN, -vector_of_pixels[0][width - 2].red +
                                                    SHARPENING_COEFF_3 * vector_of_pixels[0][width - 1].red -
                                                    vector_of_pixels[1][width - 1].red));
    vector_of_pixels_new[0][width - 1].green =
        std::min(COLOR_MAX, std::max(COLOR_MIN, -vector_of_pixels[0][width - 2].green +
                                                    SHARPENING_COEFF_3 * vector_of_pixels[0][width - 1].green -
                                                    vector_of_pixels[1][width - 1].green));
    vector_of_pixels_new[0][width - 1].blue =
        std::min(COLOR_MAX, std::max(COLOR_MIN, -vector_of_pixels[0][width - 2].blue +
                                                    SHARPENING_COEFF_3 * vector_of_pixels[0][width - 1].blue -
                                                    vector_of_pixels[1][width - 1].blue));

    vector_of_pixels_new[height - 1][0].red =
        std::min(COLOR_MAX, std::max(COLOR_MIN, -vector_of_pixels[height - 2][0].red +
                                                    SHARPENING_COEFF_3 * vector_of_pixels[height - 1][0].red -
                                                    vector_of_pixels[height - 1][1].red));
    vector_of_pixels_new[height - 1][0].green =
        std::min(COLOR_MAX, std::max(COLOR_MIN, -vector_of_pixels[height - 2][0].green +
                                                    SHARPENING_COEFF_3 * vector_of_pixels[height - 1][0].green -
                                                    vector_of_pixels[height - 1][1].green));
    vector_of_pixels_new[height - 1][0].blue =
        std::min(COLOR_MAX, std::max(COLOR_MIN, -vector_of_pixels[height - 2][0].blue +
                                                    SHARPENING_COEFF_3 * vector_of_pixels[height - 1][0].blue -
                                                    vector_of_pixels[height - 1][1].blue));

    vector_of_pixels_new[height - 1][width - 1].red =
        std::min(COLOR_MAX, std::max(COLOR_MIN, -vector_of_pixels[height - 2][width - 1].red -
                                                    vector_of_pixels[height - 1][width - 2].red +
                                                    SHARPENING_COEFF_3 * vector_of_pixels[height - 1][width - 1].red));
    vector_of_pixels_new[height - 1][width - 1].green = std::min(
        COLOR_MAX, std::max(COLOR_MIN, -vector_of_pixels[height - 2][width - 1].green -
                                           vector_of_pixels[height - 1][width - 2].green +
                                           SHARPENING_COEFF_3 * vector_of_pixels[height - 1][width - 1].green));
    vector_of_pixels_new[height - 1][width - 1].blue =
        std::min(COLOR_MAX, std::max(COLOR_MIN, -vector_of_pixels[height - 2][width - 1].blue -
                                                    vector_of_pixels[height - 1][width - 2].blue +
                                                    SHARPENING_COEFF_3 * vector_of_pixels[height - 1][width - 1].blue));

    for (size_t i = 1; i < height - 1; ++i) {
        vector_of_pixels_new[i][0].red =
            std::min(COLOR_MAX, std::max(COLOR_MIN, -vector_of_pixels[i - 1][0].red +
                                                        SHARPENING_COEFF_4 * vector_of_pixels[i][0].red -
                                                        vector_of_pixels[i][1].red - vector_of_pixels[i + 1][0].red));
        vector_of_pixels_new[i][0].green = std::min(
            COLOR_MAX,
            std::max(COLOR_MIN, -vector_of_pixels[i - 1][0].green + SHARPENING_COEFF_4 * vector_of_pixels[i][0].green -
                                    vector_of_pixels[i][1].green - vector_of_pixels[i + 1][0].green));
        vector_of_pixels_new[i][0].blue =
            std::min(COLOR_MAX, std::max(COLOR_MIN, -vector_of_pixels[i - 1][0].blue +
                                                        SHARPENING_COEFF_4 * vector_of_pixels[i][0].blue -
                                                        vector_of_pixels[i][1].blue - vector_of_pixels[i + 1][0].blue));
        vector_of_pixels_new[i][width - 1].red = std::min(
            COLOR_MAX,
            std::max(COLOR_MIN, -vector_of_pixels[i - 1][width - 1].red - vector_of_pixels[i][width - 2].red +
                                    SHARPENING_COEFF_5 * vector_of_pixels[i][width - 1].red -
                                    vector_of_pixels[i][width - 1].red - vector_of_pixels[i + 1][width - 1].red));
        vector_of_pixels_new[i][width - 1].green = std::min(
            COLOR_MAX,
            std::max(COLOR_MIN, -vector_of_pixels[i - 1][width - 1].green - vector_of_pixels[i][width - 2].green +
                                    SHARPENING_COEFF_5 * vector_of_pixels[i][width - 1].green -
                                    vector_of_pixels[i][width - 1].green - vector_of_pixels[i + 1][width - 1].green));
        vector_of_pixels_new[i][width - 1].blue = std::min(
            COLOR_MAX,
            std::max(COLOR_MIN, -vector_of_pixels[i - 1][width - 1].blue - vector_of_pixels[i][width - 2].blue +
                                    SHARPENING_COEFF_5 * vector_of_pixels[i][width - 1].blue -
                                    vector_of_pixels[i][width - 1].blue - vector_of_pixels[i + 1][width - 1].blue));
    }

    for (size_t i = 1; i < width - 1; ++i) {
        vector_of_pixels_new[0][i].red = std::min(
            COLOR_MAX,
            std::max(COLOR_MIN, -vector_of_pixels[0][i - 1].red + SHARPENING_COEFF_4 * vector_of_pixels[0][i].red -
                                    vector_of_pixels[1][i + 1].red - vector_of_pixels[0][i + 1].red));
        vector_of_pixels_new[0][i].green = std::min(
            COLOR_MAX,
            std::max(COLOR_MIN, -vector_of_pixels[0][i - 1].green + SHARPENING_COEFF_4 * vector_of_pixels[0][i].green -
                                    vector_of_pixels[1][i + 1].green - vector_of_pixels[0][i + 1].green));
        vector_of_pixels_new[0][i].blue = std::min(
            COLOR_MAX,
            std::max(COLOR_MIN, -vector_of_pixels[0][i - 1].blue + SHARPENING_COEFF_4 * vector_of_pixels[0][i].blue -
                                    vector_of_pixels[1][i + 1].blue - vector_of_pixels[0][i + 1].blue));
        vector_of_pixels_new[height - 1][i].red = std::min(
            COLOR_MAX,
            std::max(COLOR_MIN, -vector_of_pixels[height - 1][i - 1].red - vector_of_pixels[height - 2][i].red +
                                    SHARPENING_COEFF_5 * vector_of_pixels[height - 1][i].red -
                                    vector_of_pixels[height - 1][i + 1].red - vector_of_pixels[height - 1][i].red));
        vector_of_pixels_new[height - 1][i].green = std::min(
            COLOR_MAX,
            std::max(COLOR_MIN, -vector_of_pixels[height - 1][i - 1].green - vector_of_pixels[height - 2][i].green +
                                    SHARPENING_COEFF_5 * vector_of_pixels[height - 1][i].green -
                                    vector_of_pixels[height - 1][i + 1].green - vector_of_pixels[height - 1][i].green));
        vector_of_pixels_new[height - 1][i].blue = std::min(
            COLOR_MAX,
            std::max(COLOR_MIN, -vector_of_pixels[height - 1][i - 1].blue - vector_of_pixels[height - 2][i].blue +
                                    SHARPENING_COEFF_5 * vector_of_pixels[height - 1][i].blue -
                                    vector_of_pixels[height - 1][i + 1].blue - vector_of_pixels[height - 1][i].blue));
    }

    for (size_t i = 1; i < height - 1; ++i) {
        for (size_t j = 1; j < width - 1; ++j) {
            vector_of_pixels_new[i][j].red = std::min(
                COLOR_MAX, std::max(COLOR_MIN, -vector_of_pixels[i][j - 1].red - vector_of_pixels[i - 1][j].red +
                                                   SHARPENING_COEFF_5 * vector_of_pixels[i][j].red -
                                                   vector_of_pixels[i + 1][j].red - vector_of_pixels[i][j + 1].red));
            vector_of_pixels_new[i][j].green =
                std::min(COLOR_MAX,
                         std::max(COLOR_MIN, -vector_of_pixels[i][j - 1].green - vector_of_pixels[i - 1][j].green +
                                                 SHARPENING_COEFF_5 * vector_of_pixels[i][j].green -
                                                 vector_of_pixels[i + 1][j].green - vector_of_pixels[i][j + 1].green));
            vector_of_pixels_new[i][j].blue = std::min(
                COLOR_MAX, std::max(COLOR_MIN, -vector_of_pixels[i][j - 1].blue - vector_of_pixels[i - 1][j].blue +
                                                   SHARPENING_COEFF_5 * vector_of_pixels[i][j].blue -
                                                   vector_of_pixels[i + 1][j].blue - vector_of_pixels[i][j + 1].blue));
        }
    }

    vector_of_pixels = std::move(vector_of_pixels_new);
}
