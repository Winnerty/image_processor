#pragma once
#include <algorithm>
#include <cmath>
#include "BaseFilter.h"

class GaussianBlurFilter : public BaseFilter {
public:
    explicit GaussianBlurFilter(double sigma);
    double GaussianFunction(int32_t x) const;
    void ApplyFilter(Image& img) override;

private:
    double sigma_;
    std::vector<std::vector<double>> gaussian_filter_matrix_;
};
