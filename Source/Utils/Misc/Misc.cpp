//
// Created by verrignij on 05/12/2017.
//

#ifdef WIN32
#include <Windows.h>
#endif

#include <cstdio>  /* defines FILENAME_MAX */
#include <Utils/String/String.h>
#include <Utils/FileSystem/File.h>
#include "Misc.h"

std::string Misc::GetExecutablePath()
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
        Buffer[bytes] = '\0';
    return bytes;
#endif
    return String::RightTrimCopy(std::string(Buffer, FILENAME_MAX));
}

std::string Misc::GetExecutableDir()
{

    auto SplitPath = String::Split(GetExecutablePath(), Separator);
    SplitPath.pop_back();

    return String::Join(SplitPath, Separator) + Separator;
}
