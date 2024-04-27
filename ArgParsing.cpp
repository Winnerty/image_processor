#include "ArgParsing.h"

const std::string USERS_INF =
    "\n\nThis is the image processor software to work with bmp24 formatted images. "
    "See the list of the filters you can use:\n\n"
    "--CropFilter width height (enter '-crop' and 2 integer arguments)\n"
    "--GrayscaleFilter (enter '-gs')\n"
    "--NegativeFilter (enter '-neg')\n"
    "--SharpFilter (enter '-sharp')\n"
    "--EdgeDetectionFilter threshold (enter '-edge' and 1 integer argument)\n"
    "--GaussianBlurFilter sigma (enter '-blur' and 1 fractional argument)\n"
    "--SaturationFilter (enter '-own' and 1 fractional argument, recommended value from 1.01 to 4.0)\n";

const std::string ARGS_FORMAT_ERROR = "Wrong format of input arguments.";
const std::string S_CROP = "-crop";
const std::string S_GS = "-gs";
const std::string S_NEG = "-neg";
const std::string S_SHARP = "-sharp";
const std::string S_EDGE = "-edge";
const std::string S_BLUR = "-blur";
const std::string S_OWN = "-own";

const std::string_view CROP = S_CROP;
const std::string_view GS = S_GS;
const std::string_view NEG = S_NEG;
const std::string_view SHARP = S_SHARP;
const std::string_view EDGE = S_EDGE;
const std::string_view BLUR = S_BLUR;
const std::string_view OWN = S_OWN;

const uint8_t COLOR_MAX = 255;

std::vector<char *> ArgParsing::Parsing(int argc, char *argv[]) {
    std::vector<char *> args_parsed(argc - 1);
    for (int i = 1; i < argc; ++i) {
        args_parsed[i - 1] = argv[i];
    }
    return args_parsed;
}

std::vector<std::unique_ptr<BaseFilter>> ArgParsing::ApplyFilters(std::vector<char *> args_parsed) {
    std::vector<std::unique_ptr<BaseFilter>> filters;
    bool filters_exist = false;
    for (size_t i = 2; i < args_parsed.size(); ++i) {
        if (args_parsed[i] == CROP) {
            try {
                std::unique_ptr<BaseFilter> ptr =
                    std::make_unique<CropFilter>(atoi(args_parsed[i + 1]), atoi(args_parsed[i + 2]));
                filters.push_back(std::move(ptr));
                filters_exist = true;
            } catch (...) {
                throw ARGS_FORMAT_ERROR;
            }
        }

        else if (args_parsed[i] == GS) {
            std::unique_ptr<BaseFilter> ptr = std::make_unique<GrayscaleFilter>();
            filters.push_back(std::move(ptr));
            filters_exist = true;
        }

        else if (args_parsed[i] == NEG) {
            std::unique_ptr<BaseFilter> ptr = std::make_unique<NegativeFilter>();
            filters.push_back(std::move(ptr));
            filters_exist = true;
        }

        else if (args_parsed[i] == SHARP) {
            std::unique_ptr<BaseFilter> ptr = std::make_unique<SharpeningFilter>();
            filters.push_back(std::move(ptr));
            filters_exist = true;
        }

        else if (args_parsed[i] == EDGE) {
            try {
                std::unique_ptr<BaseFilter> ptr =
                    std::make_unique<EdgeDetectionFilter>(static_cast<uint8_t>(COLOR_MAX * atof(args_parsed[i + 1])));
                filters.push_back(std::move(ptr));
                filters_exist = true;
            } catch (...) {
                throw ARGS_FORMAT_ERROR;
            }
        }

        else if (args_parsed[i] == BLUR) {
            try {
                std::unique_ptr<BaseFilter> ptr =
                    std::make_unique<GaussianBlurFilter>(static_cast<double>(atof(args_parsed[i + 1])));
                filters.push_back(std::move(ptr));
                filters_exist = true;
            } catch (...) {
                throw ARGS_FORMAT_ERROR;
            }
        } else if (args_parsed[i] == OWN) {
            try {
                std::unique_ptr<BaseFilter> ptr =
                    std::make_unique<MyOwnFilter>(static_cast<double>(atof(args_parsed[i + 1])));
                filters.push_back(std::move(ptr));
                filters_exist = true;
            } catch (...) {
                throw ARGS_FORMAT_ERROR;
            }
        }
    }

    if (!filters_exist) {
        std::cout << USERS_INF;
    }

    return filters;
}