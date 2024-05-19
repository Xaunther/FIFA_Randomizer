#pragma once

#include <string>
#include <fstream>
#include <map>

enum PlayerPos
{
    GK,
    DF,
    MF,
    FW
};
class player;
using players = std::map<unsigned int, player>;

class player
{
public:
    player() {} //Default constructor
    player(std::string &line);
    unsigned int GetPlayerID() { return m_playerid; }
    unsigned int GetPosition() { return m_preferredposition1; }
    unsigned int GetRoughPosition();

private:
    int m_birthdate;
    int m_playerjointeamdate;
    int m_shoetypecode;
    int m_haircolorcode;
    int m_facialhairtypecode;
    int m_curve;
    int m_jerseystylecode;
    int m_agility;
    int m_accessorycode4;
    int m_gksavetype;
    int m_positioning;
    int m_hairtypecode;
    int m_standingtackle;
    int m_faceposercode;
    int m_preferredposition3;
    int m_longpassing;
    int m_penalties;
    int m_animfreekickstartposcode;
    int m_animpenaltieskickstylecode;
    int m_isretiring;
    int m_longshots;
    int m_gkdiving;
    int m_interceptions;
    int m_shoecolorcode2;
    int m_crossing;
    int m_potential;
    int m_gkreflexes;
    int m_finishingcode1;
    int m_reactions;
    int m_vision;
    int m_contractvaliduntil;
    int m_finishing;
    int m_dribbling;
    int m_slidingtackle;
    int m_accessorycode3;
    int m_accessorycolourcode1;
    int m_headtypecode;
    int m_firstnameid;
    int m_sprintspeed;
    int m_height;
    int m_hasseasonaljersey;
    int m_preferredposition2;
    int m_strength;
    int m_preferredposition1;
    int m_ballcontrol;
    int m_shotpower;
    int m_trait1;
    int m_socklengthcode;
    int m_weight;
    int m_hashighqualityhead;
    int m_gkglovetypecode;
    int m_balance;
    int m_gkkicking;
    int m_lastnameid;
    int m_internationalrep;
    int m_animpenaltiesmotionstylecode;
    int m_shortpassing;
    int m_freekickaccuracy;
    int m_skillmoves;
    int m_usercaneditname;
    int m_attackingworkrate;
    int m_finishingcode2;
    int m_aggression;
    int m_acceleration;
    int m_headingaccuracy;
    int m_eyebrowcode;
    int m_runningcode2;
    int m_gkhandling;
    int m_eyecolorcode;
    int m_jerseysleevelengthcode;
    int m_accessorycolourcode3;
    int m_accessorycode1;
    int m_headclasscode;
    int m_defensiveworkrate;
    int m_nationality;
    int m_preferredfoot;
    int m_sideburnscode;
    int m_weakfootabilitytypecode;
    int m_jumping;
    int m_skintypecode;
    int m_gkkickstyle;
    int m_stamina;
    int m_playerid;
    int m_marking;
    int m_accessorycolourcode4;
    int m_gkpositioning;
    int m_trait2;
    int m_skintonecode;
    int m_shortstyle;
    int m_overallrating;
    int m_jerseyfit;
    int m_accessorycode2;
    int m_shoedesigncode;
    int m_playerjerseynameid;
    int m_shoecolorcode1;
    int m_commonnameid;
    int m_bodytypecode;
    int m_animpenaltiesstartposcode;
    int m_runningcode1;
    int m_preferredposition4;
    int m_volleys;
    int m_accessorycolourcode2;
    int m_facialhaircolorcode;
};