#include <iostream>
#include "ws.h"
#include "manager.h"
using namespace std;

int main()
{
    WorldState world;
    InterdependencyManager manager;
    // Weapon quest
    QuestNode weaponQuest( "Steal the Captain's Weapon",[](const WorldState& w)
        {
            return !w.weaponQuestCompleted;
        },
        [](WorldState& w, Outcome o)
        {
            if (o == Outcome::Success)
            {
                w.villagerHasWeapon = true;
                w.villageTrust += 4;
                cout << "Weapon delivered to villager\n";
            }
            else if (o == Outcome::Steal)
            {
                w.playerHasWeapon = true;
                w.villageTrust -= 3;
                cout << "You kept the weapon. Villagers distrust you\n";
            }
            else if (o == Outcome::Failure)
            {
                w.villageTrust -= 2;
                cout << "The theft failed\n";
            }
            else
            {
                cout << "Quest abandoned\n";
            }
            w.weaponQuestCompleted = true;
        }
    );

    // Repair walls
    QuestNode repairWalls("Repair Village Walls", [](const WorldState& w)
        {
            return !w.wallsRepaired;
        },
        [](WorldState& w, Outcome o)
        {
            if (o == Outcome::Success)
            {
                w.wallsRepaired = true;
                w.villageTrust += 2;
                cout << "Walls repaired\n";
            }
            else
            {
                cout << "Wall repairs failed\n";
            }
        }
    );

    // Help villagers
    QuestNode helpVillagers("Help Injured Villagers", [](const WorldState& w)
        {return !w.villagersHelped;},
        [](WorldState& w, Outcome o)
        {
            if (o == Outcome::Success)
            {
                w.villagersHelped = true;
                w.villageTrust += 2;
                cout << "Villagers helped\n";
            }
            else if (o == Outcome::Steal)
            {
                w.villageTrust -= 2;
                cout << "You stole supplies from villagers\n";
            }
            else
            {
                cout << "You failed to help the villagers\n";
            }
        }
    );

    // Scout bandits
    QuestNode scoutBandits("Scout Bandit Camp",[](const WorldState& w)
        {
            return !w.banditsScouted;
        },
        [](WorldState& w, Outcome o)
        {
            if (o == Outcome::Success)
            {
                w.banditsScouted = true;
                cout << "Bandit locations discovered\n";
            }
        }
    );

    // Secure food
    QuestNode secureFood("Secure Food Supplies",[](const WorldState& w)
        {
            return w.villagersHelped && !w.foodSupplySecured;
        },
        [](WorldState& w, Outcome o)
        {
            if (o == Outcome::Success)
            {
                w.foodSupplySecured = true;
                cout << "Food supplies secured\n";
            }
        }
    );

    // Form militia
    QuestNode formMilitia( "Form Village Militia",[](const WorldState& w)
        {
            return w.wallsRepaired && w.villagersHelped && !w.militiaFormed;
        },
        [](WorldState& w, Outcome o)
        {
            if (o == Outcome::Success)
            {
                w.militiaFormed = true;
                cout << "Village militia formed\n";
            }
        }
    );

    // Defend village
    QuestNode defendVillage("Defend the Village",[](const WorldState& w)
        {
            return w.militiaFormed &&
                w.banditsScouted &&
                w.foodSupplySecured &&
                !w.villageDefended;
        },
        [](WorldState& w, Outcome o)
        {
            if (o == Outcome::Success)
            {
                w.villageDefended = true;
                w.banditThreat = false;
                w.villageTrust += 6;

                cout << "Village successfully defended\n";
            }
        }
    );

    // Hunt bandits
    QuestNode huntBandits("Hunt Remaining Bandits",[](const WorldState& w)
        {
            return w.villageDefended && !w.banditsHunted;
        },
        [](WorldState& w, Outcome o)
        {
            if (o == Outcome::Success)
            {
                w.banditsHunted = true;
                w.villageTrust += 3;
                cout << "Bandits hunted down\n";
            }
        }
    );

    // Leader fight
    QuestNode defeatLeader("Defeat Bandit Leader",[](const WorldState& w)
        {
            return w.banditsHunted && w.playerHasWeapon && !w.banditLeaderDefeated;
        },
        [](WorldState& w, Outcome o)
        {
            if (o == Outcome::Success)
            {
                w.banditLeaderDefeated = true;
                w.villageTrust += 5;

                cout << "Bandit leader defeated\n";
            }
        }
    );

    // Trade rout
    QuestNode secureTrade("Secure Trade Route",[](const WorldState& w)
        {
            return w.villageDefended && !w.tradeRouteSecured;
        },
        [](WorldState& w, Outcome o)
        {
            if (o == Outcome::Success)
            {
                w.tradeRouteSecured = true;
                cout << "Trade routes secured\n";
            }
        }
    );

    // Alliance
    QuestNode alliance("Form Regional Alliance",[](const WorldState& w)
        {
            return w.tradeRouteSecured &&
                w.villageTrust >= 10 &&
                !w.allianceFormed;
        },
        [](WorldState& w, Outcome o)
        {
            if (o == Outcome::Success)
            {
                w.allianceFormed = true;
                cout << "Alliance formed\n";
            }
        }
    );
    // Champion
    QuestNode champion("Become Village Champion",[](const WorldState& w)
        {
            return w.banditLeaderDefeated &&
                w.villageTrust >= 15 &&
                !w.championDeclared;
        },
        [](WorldState& w, Outcome o)
        {
            if (o == Outcome::Success)
            {
                w.championDeclared = true;
                cout << "You are the village champion\n";
            }
        }
    );
    manager.addQuest(weaponQuest);
    manager.addQuest(repairWalls);
    manager.addQuest(helpVillagers);
    manager.addQuest(scoutBandits);
    manager.addQuest(secureFood);
    manager.addQuest(formMilitia);
    manager.addQuest(defendVillage);
    manager.addQuest(huntBandits);
    manager.addQuest(defeatLeader);
    manager.addQuest(secureTrade);
    manager.addQuest(alliance);
    manager.addQuest(champion);

    while (true)
    {
        printWorldState(world);
        auto available = manager.getAvailable(world);
        manager.showAvailable(available);
        cout << "\nSelect quest (-1 exit): ";
        int choice;
        cin >> choice;

        if (choice == -1)
            break;
        int questIndex = available[choice];
        cout << "\nChoose outcome\n0 Success\n1 Failure\n2 Steal\n3 Abandon\n";
        int outcome;
        cin >> outcome;
        manager.resolve(questIndex, world, static_cast<Outcome>(outcome));
    }
    return 0;
}