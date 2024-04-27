#pragma once
#include <algorithm>
#include <cstdint>
#include "BaseFilter.h"
#include "Image.h"

class SharpeningFilter : public BaseFilter {
public:
    void ApplyFilter(Image& img) override;
};
