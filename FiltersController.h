#pragma once
#include <memory>
#include <string>
#include <vector>
#include "BaseFilter.h"
#include "CropFilter.h"
#include "EdgeDetectionFilter.h"
#include "GrayscaleFilter.h"
#include "Image.h"
#include "NegativeFilter.h"
#include "SharpeningFilter.h"

class FiltersController {
public:
    void Control(Image& img, std::vector<std::unique_ptr<BaseFilter>>& filters);
};
