//
// Created by snaiperskaya on 03/12/17.
//

#include <fstream>
#include <algorithm>
#include "File.h"
#ifdef WIN32
#include <Windows.h>
#else
#include <zconf.h>
#include <sys/param.h>
#endif

#include <Utils/String/String.h>


std::string File::GetTextFromFile(std::string FilePath)
{
    std::ifstream FileStream(FilePath);
    if (!FileStream.good()) {
        return "";
    }

    return std::string(std::istreambuf_iterator<char>(FileStream), std::istreambuf_iterator<char>());
}

std::string File::CreatePath(std::string FromPath)
{
    std::replace(FromPath.begin(), FromPath.end(), '\\', Separator);
    std::replace(FromPath.begin(), FromPath.end(), '/', Separator);

    return FromPath;
}

std::string File::GetExecutableDir()
{

    auto SplitPath = String::Split(GetExecutablePath(), Separator);
    SplitPath.pop_back();

    return String::Join(SplitPath, Separator) + Separator;
}

std::string File::GetExecutablePath()
{
    char Buffer[FILENAME_MAX];
    memset(Buffer, ' ', FILENAME_MAX);

#ifdef WIN32
    if (GetModuleFileName(nullptr, Buffer, FILENAME_MAX) == 0) {
        return "";
    }
#else
    char Pid[32];
    sprintf(Pid, "/proc/%d/exe", getpid());
    if(MIN(readlink(Pid, Buffer, FILENAME_MAX), FILENAME_MAX - 1) >= 0)
        Buffer[FILENAME_MAX] = '\0';
#endif
    return String::RightTrimCopy(std::string(Buffer, FILENAME_MAX));
}


