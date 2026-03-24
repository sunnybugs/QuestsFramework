#ifndef QUESTNODE_H
#define QUESTNODE_H
#include <string>
#include <functional>
#include "ws.h"
#include "Bhandler.h"
using namespace std;

class QuestNode
{
public:
    string name;
    function<bool(const WorldState&)> condition;
    function<void(WorldState&, Outcome)> effect;
    QuestNode(string n,
        function<bool(const WorldState&)> c,
        function<void(WorldState&, Outcome)> e
    );
};

#endif