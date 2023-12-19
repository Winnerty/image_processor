#include "ArgParsing.h"
#include "FiltersController.h"
#include "Image.h"
#include "IOFile.h"

int main(int argc, char** argv) {
    auto args_parsed = ArgParsing::Parsing(argc, argv);

    Image image;
    IOFile input_output(args_parsed);
    input_output.Download(image);

    auto filters = ArgParsing::ApplyFilters(args_parsed);
    if (filters.empty()) {
        return 0;
    }

    FiltersController filters_controller;
    filters_controller.Control(image, filters);

    input_output.Upload(image);
    return 0;
}
