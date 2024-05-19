#pragma once

#include <string>
#include <map>
#include <vector>

#define euro_leagueID                                                                                  \
    {                                                                                                  \
        1, 4, 10, 13, 14, 16, 17, 19, 20, 31, 32, 41, 50, 53, 54, 56, 60, 61, 65, 66, 67, 80, 189, 308 \
    }

class league;
using leagues = std::map<unsigned int, league>;

class league
{
public:
    league() {} //Default constructor
    league(std::string &line);
    unsigned int GetLeagueID() { return m_leagueid; }
    void AddTeam(unsigned int teamID) { m_teamIDs.push_back(teamID); }
    unsigned int GetNTeams() { return m_teamIDs.size(); }
    unsigned int GetTeam(unsigned int ID) { return m_teamIDs[ID]; }

private:
    unsigned int m_countryid;
    std::string m_leaguename;
    unsigned int m_level;
    unsigned int m_leagueid;
    unsigned int m_leaguetimeslice;
    unsigned int m_iswithintransferwindow;

    std::vector<unsigned int> m_teamIDs;
};