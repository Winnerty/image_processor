#pragma once
#include "BaseFilter.h"
#include "Image.h"

class EdgeDetectionFilter : public BaseFilter {
public:
    explicit EdgeDetectionFilter(uint8_t threshold);
    EdgeDetectionFilter() = default;
    void ApplyFilter(Image& img) override;

private:
    uint8_t threshold_;
};
