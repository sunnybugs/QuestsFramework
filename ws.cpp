#include <iostream>
#include "ws.h"

using namespace std;

void printWorldState(const WorldState& state)
{
    cout << "\nWorld State\n";
    cout << "Village Trust: " << state.villageTrust << endl;
    cout << "Bandit Threat: " << state.banditThreat << endl;
    cout << "Player Has Weapon: " << state.playerHasWeapon << endl;
    cout << "Villager Has Weapon: " << state.villagerHasWeapon << endl;
}