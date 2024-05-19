#include <iostream>
#include <fstream>
#include <filesystem>
#include <map>
#include <list>
#include <stdlib.h>
#include <time.h>
#include <optional>
#include "league.h"
#include "team.h"
#include "player.h"
#include "playerlink.h"

//Macros
#define leaguetxt "leagues.txt"
#define leagueteamtxt "leagueteamlinks.txt"
#define playertxt "players.txt"
#define teamplayertxt "teamplayerlinks.txt"

//Aliases

//Function index
void PrintWelcome();
void DetectInputFiles();
playerlinks ReadPlayerlinks();
players ReadPlayers();
teams ReadTeams();
leagues ReadLeagues();
void LinkPlayersToTeams(players &pls, teams &ts);
void LinkTeamsToLeagues(teams &ts, leagues &ls);
void RandomizeEuropeanExchanges(players &ps, playerlinks &pls, teams &ts, leagues &ls);
std::optional<unsigned int> GetRandomPlayerFrom(team &t, players &ps, PlayerPos pos);
unsigned int GetRandomEuropeanTeam(leagues &ls);
void SavePlayerlinks(playerlinks &pls);
int main();

//Welcome message
void PrintWelcome()
{
    std::cout << "Welcome to FIFA 13 randomizer by Xaunder" << std::endl;
    std::cout << "The script takes the player-team link table, team-league link table and leagues table to perform exchanges of players between european clubs" << std::endl;
    std::cout << "It only swaps players of similar roles, for which we define 4: GKs, DFs, MFs and FWs" << std::endl;
}

//Detection of necessary inputs
void DetectInputFiles()
{
    bool ok = true;
    ok *= std::filesystem::exists(leaguetxt);
    ok *= std::filesystem::exists(leagueteamtxt);
    ok *= std::filesystem::exists(teamplayertxt);
    ok *= std::filesystem::exists(playertxt);
    if (!ok)
        throw std::runtime_error("Necessary txt files not found: {" + std::string(leaguetxt) + "}, {" + std::string(playertxt) + "}, {" + std::string(leagueteamtxt) + "} and {" + std::string(teamplayertxt) + "}");
}

playerlinks ReadPlayerlinks()
{
    //Open file
    std::ifstream infile;
    infile.open(teamplayertxt);

    playerlinks pls;
    std::string basura;
    std::getline(infile, basura); //Remove header line
    std::getline(infile, basura);
    while (basura != "")
    {
        playerlink pl(basura);
        pls[std::pair(pl.GetPlayerID(), pl.GetTeamID())] = pl;
        std::getline(infile, basura);
    }
    //Close File
    infile.close();

    return pls;
}

players ReadPlayers()
{
    //Open file
    std::ifstream infile;
    infile.open(playertxt);

    players ps;
    std::string basura;
    std::getline(infile, basura); //Remove header line
    std::getline(infile, basura);
    while (basura != "")
    {
        player p(basura);
        ps[p.GetPlayerID()] = p;
        std::getline(infile, basura);
    }
    //Close File
    infile.close();

    return ps;
}

teams ReadTeams()
{
    //Open file
    std::ifstream infile;
    infile.open(leagueteamtxt);

    teams ts;
    std::string basura;
    std::getline(infile, basura); //Remove header line
    std::getline(infile, basura);
    while (basura != "")
    {
        team t(basura);
        ts[t.GetTeamID()] = t;
        std::getline(infile, basura);
    }
    //Close File
    infile.close();

    return ts;
}
leagues ReadLeagues()
{
    //Open file
    std::ifstream infile;
    infile.open(leaguetxt);

    leagues ls;
    std::string basura;
    std::getline(infile, basura); //Remove header line
    std::getline(infile, basura);
    while (basura != "")
    {
        league l(basura);
        ls[l.GetLeagueID()] = l;
        std::getline(infile, basura);
    }
    //Close File
    infile.close();

    return ls;
}

void LinkPlayersToTeams(playerlinks &pls, teams &ts)
{
    //Run over list of players, get their team and add to it
    for (auto pl : pls)
        ts[pl.second.GetTeamID()].AddPlayer(pl.second.GetPlayerID());
}

void LinkTeamsToLeagues(teams &ts, leagues &ls)
{
    //Go over list of teams and add to leagues
    for (auto t : ts)
        ls[t.second.GetLeagueID()].AddTeam(t.first);
}

void RandomizeEuropeanExchanges(players &ps, playerlinks &pls, teams &ts, leagues &ls)
{
    //Let's go over the list of player links, one by one
    for (auto &pl : pls)
    {
        //Check if this link correspond to european CLUB, skip otherwise
        if (!pl.second.IsEuropeanClub(ts))
        {
            //std::cout << "Skipping (" << pl.first.first << ", " << pl.first.second << "). Not a link to a european club" << std::endl;
            continue;
        }
        //Do nothing if it has been transferred already before
        else if (pl.second.IsTransferred())
        {
            //std::cout << "Skipping (" << pl.first.first << ", " << pl.first.second << "). It has been transferred already" << std::endl;
            continue;
        }
        else
        {
            //std::cout << "Reading (" << pl.first.first << ", " << pl.first.second << "). Euro link" << std::endl;
        }

        //First, let's roll a random european club
        auto target_teamID = GetRandomEuropeanTeam(ls);
        //std::cout << "Target team: " << target_teamID << std::endl;

        //Second, select target player to exchange.
        //Must be same line: GK, DF, MF, FW
        auto target_playerID = GetRandomPlayerFrom(ts[target_teamID], ps, (PlayerPos)ps[pl.second.GetPlayerID()].GetRoughPosition());
        if (!target_playerID.has_value())
        {
            //std::cout << "Skipping (" << pl.first.first << ", " << pl.first.second << "). Target club cannot trade" << std::endl;
            continue; //No match
        }
        //Update vector of players of each team
        ts[target_teamID].swap_playerID(target_playerID.value(), pl.second.GetPlayerID());
        ts[pl.second.GetTeamID()].swap_playerID(pl.second.GetPlayerID(), target_playerID.value());

        //Adapt their team positions (exchange)
        unsigned int temppos = pl.second.GetPosition();
        pl.second.SetPosition(pls[std::pair(target_playerID.value(), target_teamID)].GetPosition());
        pls[std::pair(target_playerID.value(), target_teamID)].SetPosition(temppos);

        //Adapt their shirt numbers (exchange)
        temppos = pl.second.GetNumber();
        pl.second.SetNumber(pls[std::pair(target_playerID.value(), target_teamID)].GetNumber());
        pls[std::pair(target_playerID.value(), target_teamID)].SetNumber(temppos);

        //Proceed to the exchange, also change map key
        pls[std::pair(target_playerID.value(), target_teamID)].SetTeamID(pl.second.GetTeamID()); //Bring target player
        pls[std::pair(target_playerID.value(), target_teamID)].SetTransferred();
        auto node = pls.extract(std::pair(target_playerID.value(), target_teamID));
        node.key() = std::pair(target_playerID.value(), pl.second.GetTeamID());
        pls.insert(std::move(node));

        pl.second.SetTeamID(target_teamID); //Send this player over
        pl.second.SetTransferred();
        node = pls.extract(pl.first);
        node.key() = std::pair(pl.second.GetPlayerID(), target_teamID);
        pls.insert(std::move(node));
    }
}

unsigned int GetRandomEuropeanTeam(leagues &ls)
{
    //Get list of european leagues IDs
    std::vector<unsigned int> euro_leagueIDs = euro_leagueID;
    //Throw random number to it
    unsigned int rand_league = rand() % euro_leagueIDs.size();
    //std::cout << "Target league: " << rand_league << " (" << ls[euro_leagueIDs[rand_league]].GetNTeams() << ") teams" << std::endl;
    //Now we'll use such vector index to obtain one of the teams
    unsigned int rand_team = rand() % ls[euro_leagueIDs[rand_league]].GetNTeams();
    //Return the ID of the chosen euro team
    return ls[euro_leagueIDs[rand_league]].GetTeam(rand_team);
}

std::optional<unsigned int> GetRandomPlayerFrom(team &t, players &ps, PlayerPos pos)
{
    //Get vector with players from such team within the given position
    auto candidate_players = t.GetRoughPosPlayers(pos, ps);
    if (candidate_players.size() == 0)
        return {};
    unsigned int rand_player = rand() % candidate_players.size();
    return candidate_players[rand_player];
}

void SavePlayerlinks(playerlinks &pls)
{
    std::ofstream outf;
    outf.open(("randomized_" + std::string(teamplayertxt)).c_str());
    outf << "leaguegoals\tisamongtopscorers\tyellows\tisamongtopscorersinteam\tjerseynumber\tposition\tartificialkey\tteamid\tinjury\tleagueappearances\tprevform\tistopscorer\tplayerid\tform\treds" << std::endl;
    for (auto pl : pls)
    {
        pl.second.Save(outf);
    }
    outf.close();
}

int main()
{
    //Initialize RNG
    srand(time(NULL));

    void PrintWelcome();
    void DetectInputFiles();

    //Time to read databases
    std::cout << "Start reading dbs" << std::endl;
    playerlinks pls = ReadPlayerlinks();
    std::cout << "Read playerlinks: " << pls.size() << " entries" << std::endl;
    players ps = ReadPlayers();
    std::cout << "Read players: " << ps.size() << " entries" << std::endl;
    teams ts = ReadTeams();
    std::cout << "Read teams: " << ts.size() << " entries" << std::endl;
    leagues ls = ReadLeagues();
    std::cout << "Read leagues: " << ls.size() << " entries" << std::endl;

    //To avoid running many many times over 10k players, we provide each time with the indices of their players
    LinkPlayersToTeams(pls, ts);
    LinkTeamsToLeagues(ts, ls);

    //Make random exchanges between european teams only, any division.
    RandomizeEuropeanExchanges(ps, pls, ts, ls);

    //Once the players have been randomized, save into new file
    SavePlayerlinks(pls);
}