#pragma once
#ifndef INTERDEPENDENCYMANAGER_H
#define INTERDEPENDeNCYMANAGER_H
#include <vector>
#include "Node.h"
using namespace std;

class InterdependencyManager
{
private:
    vector<QuestNode> quests;

public:
    void addQuest(const QuestNode& quest);
    vector<int> getAvailable(const WorldState& state);
    void showAvailable(const vector<int>& list);
    void resolve(int index, WorldState& state, Outcome outcome);
    QuestNode& getQuest(int index);
};

#endif