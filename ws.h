#ifndef WORLDSTATE_H
#define WORLDSTATE_H

struct WorldState
{
    int villageTrust = 0;

    bool banditThreat = true;

    bool playerHasWeapon = false;
    bool villagerHasWeapon = false;

    bool weaponQuestCompleted = false;

    bool wallsRepaired = false;
    bool villagersHelped = false;
    bool banditsScouted = false;

    bool foodSupplySecured = false;
    bool militiaFormed = false;

    bool villageDefended = false;

    bool banditsHunted = false;
    bool banditLeaderDefeated = false;

    bool tradeRouteSecured = false;
    bool regionalTradeEstablished = false;

    bool allianceFormed = false;
    bool championDeclared = false;
};

void printWorldState(const WorldState& state);

#endif