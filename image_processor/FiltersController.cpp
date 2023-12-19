#include "FiltersController.h"

void FiltersController::Control(Image& img, std::vector<std::unique_ptr<BaseFilter>>& filters) {
    for (auto& filter : filters) {
        filter->ApplyFilter(img);
    }
}
