//
// Created by snaiperskaya on 03/12/17.
//

#include <fstream>
#include "File.h"

std::string File::GetTextFromFile(std::string FilePath)
{
    std::ifstream FileStream(FilePath);
    if (!FileStream.good()) {
        return "";
    }

    return std::string(std::istreambuf_iterator<char>(FileStream), std::istreambuf_iterator<char>());
}
