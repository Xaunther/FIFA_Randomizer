#include "StringTools.h"

std::vector<std::string> SplitString(std::string s, std::string delimiter)
{
    //Empty string has no elements, DUH
    if (s == "")
    {
        return {};
    }
    unsigned int pos = 0;
    unsigned int N = CountString(s, delimiter) + 1;
    std::vector<std::string> stringlist;
    for (int i = 0; i < N; i++)
    {
        stringlist.push_back(s.substr(pos, s.find(delimiter, pos) - pos));
        if (i < N - 1)
            pos = s.find(delimiter, pos) + delimiter.size();
    }

    return stringlist;
}

unsigned int CountString(std::string s, std::string pattern)
{
    unsigned int N = 0;
    unsigned int pos = 0;
    while (s.find(pattern, pos) != std::string::npos)
    {
        N++;
        pos = s.find(pattern, pos) + pattern.size();
    }

    return N;
}