#pragma once
#include <fstream>
#include <iostream>
#include <ostream>
#include "Image.h"

class IOFile {
public:
    explicit IOFile(std::vector<char*> args_parsed) : input_path_(args_parsed[0]), output_path_(args_parsed[1]){};
    void Download(Image& img);
    void Upload(Image& img);

private:
    char* input_path_;
    char* output_path_;
};
