#include "Node.h"

QuestNode::QuestNode(
    string n,
    function<bool(const WorldState&)> c,
    function<void(WorldState&, Outcome)> e
)
{
    name = n;
    condition = c;
    effect = e;
}