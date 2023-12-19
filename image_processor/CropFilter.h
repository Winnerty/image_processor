#pragma once
#include <vector>
#include "BaseFilter.h"
#include "Image.h"

class CropFilter : public BaseFilter {
public:
    CropFilter(uint32_t new_width, uint32_t new_height);
    CropFilter() = default;
    void ApplyFilter(Image& new_img) override;

private:
    uint32_t new_width_;
    uint32_t new_height_;
};
