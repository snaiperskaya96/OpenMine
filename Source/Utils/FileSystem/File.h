//
// Created by snaiperskaya on 03/12/17.
//

#ifndef OPENMINE_FILE_H
#define OPENMINE_FILE_H

#include <string>
#ifdef WIN32
#define Separator (char)'\\'
#else
#define Separator (char)'/'
#endif

class File
{
public:
    static std::string GetTextFromFile(std::string FilePath);
};


#endif //OPENMINE_FILE_H
