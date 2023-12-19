#include "GaussianBlurFilter.h"

const double COLOR_MAX = 255.0;

double GaussianBlurFilter::GaussianFunction(int32_t x) const {
    return (std::exp(-x * x / (2 * sigma_ * sigma_)) / std::sqrt(2 * M_PI * sigma_ * sigma_));
}

GaussianBlurFilter::GaussianBlurFilter(double sigma) : sigma_(sigma) {
}

void GaussianBlurFilter::ApplyFilter(Image& img) {
    int32_t half_kernel = static_cast<int32_t>(std::ceil(3 * sigma_));
    auto& vector_of_pixels = img.GetImageVector();
    int32_t height = static_cast<int32_t>(img.GetHeight());
    int32_t width = static_cast<int32_t>(img.GetWidth());
    int32_t ind_f = 0;
    int32_t ind_s = 0;
    std::vector<std::vector<Color>> vector_of_pixels_new(height, std::vector<Color>(width));
    std::vector<double> empty_vector(0);
    gaussian_filter_matrix_.assign(half_kernel, empty_vector);
    double s_red = 0;
    double s_green = 0;
    double s_blue = 0;
    double buff = 0;

    for (int32_t i = half_kernel - 1; i >= 0; --i) {
        buff = GaussianFunction(i);
        gaussian_filter_matrix_[half_kernel - i - 1] = {buff};
    }

    for (int32_t i = half_kernel - 2; i >= 0; --i) {
        gaussian_filter_matrix_.push_back(gaussian_filter_matrix_[i]);
    }

    for (size_t i = 1; i < gaussian_filter_matrix_.size(); ++i) {
        gaussian_filter_matrix_[0].push_back(gaussian_filter_matrix_[i][0]);
    }
    gaussian_filter_matrix_.resize(1);

    for (int32_t y = 0; y < height; ++y) {
        for (int32_t x = 0; x < width; ++x) {
            s_red = 0;
            s_green = 0;
            s_blue = 0;

            for (int32_t i = 0; i < static_cast<int32_t>(gaussian_filter_matrix_.size()); ++i) {
                for (int32_t j = 0; j < static_cast<int32_t>(gaussian_filter_matrix_[0].size()); ++j) {
                    ind_f = std::max(
                        0, std::min(static_cast<int32_t>(y) - static_cast<int32_t>(gaussian_filter_matrix_.size() / 2) +
                                        static_cast<int32_t>(i),
                                    static_cast<int32_t>(height) - 1));
                    ind_s = std::max(0, std::min(static_cast<int32_t>(x) -
                                                     static_cast<int32_t>(gaussian_filter_matrix_[0].size() / 2) +
                                                     static_cast<int32_t>(j),
                                                 static_cast<int32_t>(width) - 1));

                    s_red += static_cast<double>(vector_of_pixels[ind_f][ind_s].red) * gaussian_filter_matrix_[i][j];
                    s_green +=
                        static_cast<double>(vector_of_pixels[ind_f][ind_s].green) * gaussian_filter_matrix_[i][j];
                    s_blue += static_cast<double>(vector_of_pixels[ind_f][ind_s].blue) * gaussian_filter_matrix_[i][j];
                }
            }

            vector_of_pixels_new[y][x].red = static_cast<uint8_t>(std::max(0.0, std::min(COLOR_MAX, round(s_red))));
            vector_of_pixels_new[y][x].green = static_cast<uint8_t>(std::max(0.0, std::min(COLOR_MAX, round(s_green))));
            vector_of_pixels_new[y][x].blue = static_cast<uint8_t>(std::max(0.0, std::min(COLOR_MAX, round(s_blue))));
        }
    }

    vector_of_pixels = std::move(vector_of_pixels_new);
}
