//
// Created by verrignij on 05/12/2017.
//

#ifndef OPENMINE_STRING_H
#define OPENMINE_STRING_H

#include <algorithm>
#include <cctype>
#include <locale>
#include <vector>
#include <sstream>

class String
{
public:
    // Trim methods from https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
    // trim from start (in place)
    static inline void LeftTrim(std::string &InString)
    {
        InString.erase(InString.begin(), std::find_if(InString.begin(), InString.end(), [](int Character) {
            return !std::isspace(Character);
        }));
    }

    // trim from end (in place)
    static inline void RightTrim(std::string &InString)
    {
        InString.erase(std::find_if(InString.rbegin(), InString.rend(), [](int Character) {
            return !std::isspace(Character);
        }).base(), InString.end());
    }

    // trim from both ends (in place)
    static inline void Trim(std::string &InString)
    {
        LeftTrim(InString);
        RightTrim(InString);
    }

    // trim from start (copying)
    static inline std::string LeftTrimCopy(std::string InString)
    {
        LeftTrim(InString);
        return InString;
    }

    // trim from end (copying)
    static inline std::string RightTrimCopy(std::string InString)
    {
        RightTrim(InString);
        return InString;
    }

    template<typename Out>
    static inline void Split(const std::string &InString, char Delimitator, Out Result)
    {
        std::stringstream StringStream(InString);
        std::string Item;
        while (std::getline(StringStream, Item, Delimitator)) {
            *(Result++) = Item;
        }
    }

    static inline std::vector<std::string> Split(const std::string &InString, char Delimitator)
    {
        std::vector<std::string> Elements;
        Split(InString, Delimitator, std::back_inserter(Elements));
        return Elements;
    }

    static inline std::string Join(const std::vector<std::string>& InArray, char Delimitator)
    {
        std::string Out;

        for (auto& S : InArray) {
            Out += S;
            Out += Delimitator;
        }

        return Out.substr(0, Out.length() - 1);
    }

};


#endif //OPENMINE_STRING_H
