#pragma once
#include "Image.h"

class BaseFilter {
public:
    virtual void ApplyFilter(Image& img) = 0;
    virtual ~BaseFilter() = default;
};
