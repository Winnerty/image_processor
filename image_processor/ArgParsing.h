#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "BaseFilter.h"
#include "CropFilter.h"
#include "EdgeDetectionFilter.h"
#include "GaussianBlurFilter.h"
#include "GrayscaleFilter.h"
#include "MyOwnFilter.h"
#include "NegativeFilter.h"
#include "SharpeningFilter.h"

class ArgParsing {
public:
    static std::vector<char *> Parsing(int argc, char *argv[]);
    static std::vector<std::unique_ptr<BaseFilter>> ApplyFilters(std::vector<char *> args_parsed);
};
