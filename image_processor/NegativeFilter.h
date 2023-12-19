#pragma once
#include "BaseFilter.h"
#include "Image.h"

class NegativeFilter : public BaseFilter {
public:
    void ApplyFilter(Image& img) override;
};
