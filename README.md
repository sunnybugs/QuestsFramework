# QuestsFramework

A C++ prototype implementing a dynamic, interrelated quest framework for RPGs. This system was developed as part of an MSc dissertation titled **"Framework Design for Dynamic and Interrelated Quest Systems in RPGs"** (WMG, University of Warwick, 2026).

The prototype demonstrates how quests can be interconnected, how player actions are remembered across quests through persistent world state, and how success, failure, theft, and abandonment each produce distinct narrative consequences — addressing limitations identified in existing RPG quest generation research.

---

## Research Context

Existing RPG quest systems tend to treat quests as isolated tasks with little memory of past events and no meaningful consequence for failure. This prototype implements a framework designed to address three core problems:

- **Lack of persistence** — quest outcomes are forgotten once a quest ends
- **Isolated quests** — one quest rarely affects another
- **Failure as a dead end** — failing a quest typically stops progress rather than branching the narrative

---

## Framework Modules

The framework maps directly to the four modules described in the dissertation:

| Module | File(s) | Role |
|---|---|---|
| Quest Nodes | `Node.h / Node.cpp` | Individual quest units with conditions and effects |
| Interdependency Manager | `manager.h / manager.cpp` | Controls which quests are available based on world state |
| State Memory Module | `ws.h / ws.cpp` | Persistent world state variables updated after every quest |
| Branching Handler | `bhandler.h` | Defines four outcome types: Success, Failure, Steal, Abandon |

### Quest Nodes (`Node.h / Node.cpp`)
Each node represents a single quest with a condition function (precondition) and an effect function (outcome). Nodes are not isolated — their effects directly update the world state, which gates future quests.

### Interdependency Manager (`manager.h / manager.cpp`)
Scans all quests and returns only those whose preconditions are currently met by the world state. When a quest resolves, the manager applies its effects, which may unlock or block other quests. For example, `Defend the Village` only becomes available after `militiaFormed`, `banditsScouted`, and `foodSupplySecured` are all true.

### State Memory Module (`ws.h / ws.cpp`)
Stores persistent world state variables including:
- `villageTrust` (integer, accumulates across quests — gates later quests e.g. alliance requires trust >= 10)
- Boolean flags: `wallsRepaired`, `militiaFormed`, `villageDefended`, `banditLeaderDefeated` etc.
- Player state: `playerHasWeapon`, `villagerHasWeapon`

These variables persist across all quest interactions and are queried every time the system checks quest availability.

### Branching Handler (`bhandler.h`)
Defines four outcome types that produce different world state changes:
- **Success** — positive state change, usually increases `villageTrust`
- **Failure** — negative state change, may reduce trust or leave flags unset
- **Steal** — alternative negative path (e.g. player keeps weapon instead of giving it to villager, reducing trust by 3)
- **Abandon** — neutral exit with no state change

---

## Quest Network

The prototype includes 12 interconnected quests with real dependency chains:

```
Steal the Captain's Weapon  ─┐
Repair Village Walls         ├─► Form Village Militia ─┐
Help Injured Villagers      ─┤                         │
  └► Secure Food Supplies ───┘                         ▼
Scout Bandit Camp ───────────────────────────► Defend the Village
                                                ├─► Hunt Remaining Bandits
                                                │     └─► Defeat Bandit Leader
                                                │           └─► Become Village Champion (trust >= 15)
                                                └─► Secure Trade Route
                                                      └─► Form Regional Alliance (trust >= 10)
```

`Become Village Champion` requires `banditLeaderDefeated` AND `villageTrust >= 15`, meaning the player must have made consistently positive choices across the entire quest chain.

---

## How It Works

1. **Initialisation** — The Manager loads all Quest Nodes and the initial world state
2. **State Checking** — The system queries the World State to determine which quests are currently available
3. **Player Selection** — The user selects an available quest
4. **Outcome Selection** — The user selects an outcome (Success / Failure / Steal / Abandon)
5. **State Update** — The selected outcome updates the persistent world state
6. **Interdependency Resolution** — On the next loop, the Manager rechecks all conditions and presents newly available quests

---

## Evaluation Scenarios

The following scenarios from the dissertation (Chapter 4) can be reproduced:

- **Scenario 1 — Simple Quest Node:** Run `Steal the Captain's Weapon`. Choose Success to give weapon to villager (+4 trust) or Steal to keep it (-3 trust). Observe world state update.
- **Scenario 2 — Memory Dependent Quest:** Complete early quests then observe how `villageTrust` gates access to `Form Regional Alliance` (trust >= 10) and `Become Village Champion` (trust >= 15).
- **Scenario 3 — Failure Branching:** Choose Failure or Steal outcomes on early quests and observe how reduced trust prevents later quests becoming available.
- **Scenario 4 — Scalability Test:** Play through the full 12-quest chain and observe the complete dependency network maintaining persistent state throughout.

---

