add_executable(
    image_processor
    image_processor.cpp
        Image.h ArgParsing.cpp ArgParsing.h IOFile.cpp IOFile.h Image.cpp CropFilter.cpp CropFilter.h GrayscaleFilter.cpp GrayscaleFilter.h NegativeFilter.cpp NegativeFilter.h BaseFilter.h FiltersController.cpp FiltersController.h SharpeningFilter.cpp SharpeningFilter.h BaseFilter.cpp EdgeDetectionFilter.cpp EdgeDetectionFilter.h GaussianBlurFilter.cpp GaussianBlurFilter.h MyOwnFilter.cpp MyOwnFilter.h)
