#pragma once
#include "BaseFilter.h"
#include "Image.h"

class GrayscaleFilter : public BaseFilter {
public:
    void ApplyFilter(Image& img) override;
};
