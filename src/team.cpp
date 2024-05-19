#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "team.h"
#include "StringTools.h"
#include "player.h"

team::team(std::string &line)
{
    auto splitline = SplitString(line, "\t");

    m_teamshortform = std::stoi(splitline[0]);
    m_hasachievedobjective = std::stoi(splitline[1]);
    m_yettowin = std::stoi(splitline[2]);
    m_unbeatenallcomps = std::stoi(splitline[3]);
    m_unbeatenleague = std::stoi(splitline[4]);
    m_champion = std::stoi(splitline[5]);
    m_leagueid = std::stoi(splitline[6]);
    m_prevleagueid = std::stoi(splitline[7]);
    m_previousyeartableposition = std::stoi(splitline[8]);
    m_highestpossible = std::stoi(splitline[9]);
    m_teamform = std::stoi(splitline[10]);
    m_highestprobable = std::stoi(splitline[11]);
    m_artificialkey = std::stoi(splitline[12]);
    m_nummatchesplayed = std::stoi(splitline[13]);
    m_teamid = std::stoi(splitline[14]);
    m_gapresult = std::stoi(splitline[15]);
    m_grouping = std::stoi(splitline[16]);
    m_currenttableposition = std::stoi(splitline[17]);
    m_objective = std::stoi(splitline[18]);
    m_actualvsexpectations = std::stoi(splitline[19]);
    m_unbeatenhome = std::stoi(splitline[20]);
    m_lastgameresult = std::stoi(splitline[21]);
    m_unbeatenaway = std::stoi(splitline[22]);
    m_teamlongform = std::stoi(splitline[23]);
}

std::vector<unsigned int> team::GetRoughPosPlayers(PlayerPos pos, players &ps)
{
    std::vector<unsigned int> matches;
    for (auto p : m_playerIDs)
    {
        if (pos == ps[p].GetRoughPosition())
            matches.push_back(p);
    }
    return matches;
}

void team::swap_playerID(unsigned int targetID, unsigned int newID)
{
    auto p = std::find(std::begin(m_playerIDs), std::end(m_playerIDs), targetID);
    *p = newID;
}