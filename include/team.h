#pragma once

#include <string>
#include <map>
#include <vector>
#include "player.h"

class team;
using teams = std::map<unsigned int, team>;

class team
{
public:
    team() {} //Default constructor
    team(std::string &line);
    //Setters and getters
    unsigned int GetTeamID() { return m_teamid; }
    unsigned int GetLeagueID() { return m_leagueid; }
    void AddPlayer(unsigned int playerID) { m_playerIDs.push_back(playerID); }
    std::vector<unsigned int> GetRoughPosPlayers(PlayerPos pos, players &ps);
    void swap_playerID(unsigned int targetID, unsigned int newID);

private:
    unsigned int m_teamshortform;
    unsigned int m_hasachievedobjective;
    unsigned int m_yettowin;
    unsigned int m_unbeatenallcomps;
    unsigned int m_unbeatenleague;
    unsigned int m_champion;
    unsigned int m_leagueid;
    unsigned int m_prevleagueid;
    unsigned int m_previousyeartableposition;
    unsigned int m_highestpossible;
    unsigned int m_teamform;
    unsigned int m_highestprobable;
    unsigned int m_artificialkey;
    unsigned int m_nummatchesplayed;
    unsigned int m_teamid;
    unsigned int m_gapresult;
    unsigned int m_grouping;
    unsigned int m_currenttableposition;
    unsigned int m_objective;
    unsigned int m_actualvsexpectations;
    unsigned int m_unbeatenhome;
    unsigned int m_lastgameresult;
    unsigned int m_unbeatenaway;
    unsigned int m_teamlongform;

    std::vector<unsigned int> m_playerIDs;
};