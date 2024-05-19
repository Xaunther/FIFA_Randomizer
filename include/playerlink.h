#pragma once

#include <string>
#include <fstream>
#include <map>
#include "team.h"

class playerlink;
using playerlinks = std::map<std::pair<unsigned int, unsigned int>, playerlink>;

class playerlink
{
public:
    playerlink() : m_transferred(false) {} //Default constructor
    playerlink(std::string &line);
    unsigned int GetPlayerID() { return m_playerid; }
    unsigned int GetTeamID() { return m_teamid; }
    void SetTeamID(unsigned int ID) { m_teamid = ID; }
    void Save(std::ofstream &outf);
    bool IsEuropeanClub(teams &ts);
    bool IsTransferred() { return m_transferred; }
    void SetTransferred() { m_transferred = true; }
    void SetPosition(unsigned int pos) { m_position = pos; }
    unsigned int GetPosition() { return m_position; }
    unsigned int GetNumber() { return m_jerseynumber; }
    void SetNumber(unsigned int num) { m_jerseynumber = num; }

private:
    unsigned int m_leaguegoals;
    unsigned int m_isamongtopscorers;
    unsigned int m_yellows;
    unsigned int m_isamongtopscorersinteam;
    unsigned int m_jerseynumber;
    unsigned int m_position;
    unsigned int m_artificialkey;
    unsigned int m_teamid;
    unsigned int m_injury;
    unsigned int m_leagueappearances;
    unsigned int m_prevform;
    unsigned int m_istopscorer;
    unsigned int m_playerid;
    unsigned int m_form;
    unsigned int m_reds;

    bool m_transferred;
};