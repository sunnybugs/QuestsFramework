#include <iostream>
#include "manager.h"
using namespace std;

void InterdependencyManager::addQuest(const QuestNode& quest)
{
    quests.push_back(quest);
}
vector<int> InterdependencyManager::getAvailable(const WorldState& state)
{
    vector<int> available;
    for (int i = 0; i < quests.size(); i++)
    {
        if (quests[i].condition(state))
            available.push_back(i);
    }
    return available;
}

void InterdependencyManager::showAvailable(const vector<int>& list)
{
    cout << "\nAvailable Quests\n";
    for (int i = 0; i < list.size(); i++)
    {
        cout << i << " : " << quests[list[i]].name << endl;
    }
}
void InterdependencyManager::resolve(int index, WorldState& state, Outcome outcome)
{
    quests[index].effect(state, outcome);
}
QuestNode& InterdependencyManager::getQuest(int index)
{
    return quests[index];
}