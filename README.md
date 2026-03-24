# QuestsFramework

A C++ prototype demonstrating a node-based quest system with complex interdependencies. This framework allows developers to manage quest progression, prerequisites, and world states efficiently.

## Key Components

The framework is divided into several core modules to maintain a clean separation of concerns:

* **Quest Nodes (`Node.h/cpp`):** The individual building blocks of a quest. Each node represents a specific task or stage.
* **Quest Manager (`manager.h/cpp`):** The central controller that tracks active quests, handles transitions, and checks for completion logic.
* **World State (`ws.h/cpp`):** Manages the global variables and "flags" that quests rely on to trigger (e.g., `has_key = true`).
* **Behavior Handler (`bhandler.h`):** Defines the logic for how quests react to different game events.

## How It Works

1.  **Initialization:** The `Manager` loads the required `Nodes`.
2.  **State Checking:** The system queries the `WorldState` to see which quests are eligible to begin.
3.  **Progression:** As the user interacts with the `main.cpp` entry point, the `Manager` updates the status of each `Node` from *Locked* to *Active* or *Completed*.

## Technical Implementation

This project utilizes:
* **Object-Oriented Programming (OOP):** Encapsulation of quest data within classes.
* **Dependency Management:** A logical flow where certain nodes cannot be accessed until prerequisite flags are set in the world state.
