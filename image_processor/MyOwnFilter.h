#pragma once
#include "BaseFilter.h"

class MyOwnFilter : public BaseFilter {
public:
    explicit MyOwnFilter(double saturation_value);
    void ApplyFilter(Image& img) override;

private:
    double saturation_value_;
};
