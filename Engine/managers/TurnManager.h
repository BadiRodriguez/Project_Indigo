//
// Created by Badi on 3/7/2026.
//

#ifndef UNTITLED_BULLSHIT_TURNMANAGER_H
#define UNTITLED_BULLSHIT_TURNMANAGER_H

#include <vector>
#include <string>
#include <list>
#include <queue>
#include "../definitions/Entity.h"
#include "../definitions/Action.h"

class Ability;

class TurnManager {
private:
    std::vector<Entity*> combatants;
    std::vector<Action> pending_actions;
    std::queue<Action> action_queue;
    int next_tie_breaker = 0;
public:
    void addCombatant(Entity* combatant) {
        combatants.push_back(combatant);
    }

    void queuePlannedAction(Action action) {
        pending_actions.emplace_back(action);
    }

    void buildExecutionQueue();

    bool hasActions() const {
        return !action_queue.empty();
    }

    Action popNextAction() {
        Action next = action_queue.front();
        action_queue.pop();
        return next;
    }
};


#endif //UNTITLED_BULLSHIT_TURNMANAGER_H
