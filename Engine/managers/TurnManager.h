//
// Created by Badi on 3/7/2026.
//

#ifndef UNTITLED_BULLSHIT_TURNMANAGER_H
#define UNTITLED_BULLSHIT_TURNMANAGER_H

#include <vector>
#include <string>
#include "../definitions/Entity.h"

struct TurnManager {
    std::vector<Entity*> combatants;

    // Build turn order for one round
    std::vector<Entity*> buildOrder() const {
        std::vector<Entity*> order;
        order.reserve(combatants.size());

        for (auto* e : combatants) {
            if (e && e->isEntityAlive()) order.push_back(e);
        }

        std::stable_sort(order.begin(), order.end(),
                         [](Entity* a, Entity* b) {
                             if (a->getSpeVal() != b->getSpeVal())
                                 return a->getSpeVal() > b->getSpeVal();
                             // tie-breaker: keep stable order (or compare names)
                             return a->getName() < b->getName();
                         });

        return order;
    }

    // One full round
    void runRound() {
        auto order = buildOrder();

        for (auto* actor : order) {
            if (!actor->isEntityAlive()) continue;

            actor->onTurnStart();

            // Choose target and ability (hardcode for now)
            // Example: actor uses ability 0 on first alive enemy
            // actor->getAbility(0)->Execute(actor, target);

            actor->onTurnEnd(); // ticks effects (and later cooldowns)
        }
    }

};


#endif //UNTITLED_BULLSHIT_TURNMANAGER_H
