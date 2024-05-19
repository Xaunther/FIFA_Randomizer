#include <fstream>
#include <string>
#include <algorithm>
#include "playerlink.h"
#include "StringTools.h"
#include "team.h"
#include "league.h"

playerlink::playerlink(std::string &line) : m_transferred(false)
{
    auto splitline = SplitString(line, "\t");

    m_leaguegoals = std::stoi(splitline[0]);
    m_isamongtopscorers = std::stoi(splitline[1]);
    m_yellows = std::stoi(splitline[2]);
    m_isamongtopscorersinteam = std::stoi(splitline[3]);
    m_jerseynumber = std::stoi(splitline[4]);
    m_position = std::stoi(splitline[5]);
    m_artificialkey = std::stoi(splitline[6]);
    m_teamid = std::stoi(splitline[7]);
    m_injury = std::stoi(splitline[8]);
    m_leagueappearances = std::stoi(splitline[9]);
    m_prevform = std::stoi(splitline[10]);
    m_istopscorer = std::stoi(splitline[11]);
    m_playerid = std::stoi(splitline[12]);
    m_form = std::stoi(splitline[13]);
    m_reds = std::stoi(splitline[14]);
}

void playerlink::Save(std::ofstream &outf)
{
    outf << m_leaguegoals << "\t";
    outf << m_isamongtopscorers << "\t";
    outf << m_yellows << "\t";
    outf << m_isamongtopscorersinteam << "\t";
    outf << m_jerseynumber << "\t";
    outf << m_position << "\t";
    outf << m_artificialkey << "\t";
    outf << m_teamid << "\t";
    outf << m_injury << "\t";
    outf << m_leagueappearances << "\t";
    outf << m_prevform << "\t";
    outf << m_istopscorer << "\t";
    outf << m_playerid << "\t";
    outf << m_form << "\t";
    outf << m_reds << std::endl;
}

bool playerlink::IsEuropeanClub(teams &ts)
{
    auto leagueID = ts[m_teamid].GetLeagueID();
    std::vector<unsigned int> euroIDs = euro_leagueID;
    if (std::find(std::begin(euroIDs), std::end(euroIDs), leagueID) != std::end(euroIDs))
        return true;
    else
        return false;
}