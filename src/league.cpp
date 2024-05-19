#include <iostream>
#include "league.h"
#include "StringTools.h"

league::league(std::string &line)
{
    auto splitline = SplitString(line, "\t");

    m_countryid = std::stoi(splitline[0]);
    m_leaguename = splitline[1];
    m_level = std::stoi(splitline[2]);
    m_leagueid = std::stoi(splitline[3]);
    m_leaguetimeslice = std::stoi(splitline[4]);
    m_iswithintransferwindow = std::stoi(splitline[5]);
}