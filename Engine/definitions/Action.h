//
// Created by Badi on 3/8/2026.
//

#ifndef UNTITLED_BULLSHIT_ACTION_H
#define UNTITLED_BULLSHIT_ACTION_H

class Entity;
class Ability;

enum class ActionType { Attack, Ability, Escape, Defend };

struct Action {
    ActionType action_type;
    Entity* actor;
    Entity* target;
    Ability* ability;
    int priority;
    int speed_snapshot;
    int tie_breaker;

    Action(ActionType action_type, Entity* actor, Entity* target, Ability* ability,
           int priority, int speed_snapshot, int tie_breaker)
            : action_type(action_type),
              actor(actor),
              target(target),
              ability(action_type == ActionType::Attack ? nullptr : ability),
              priority(priority),
              speed_snapshot(speed_snapshot),
              tie_breaker(tie_breaker) {}

    ActionType getActionType() const { return action_type; }
    Entity* getActor() const { return actor; }
    Entity* getTarget() const { return target; }
    Ability* getAbility() const { return ability; }
    int getPriority() const { return priority; }
    int getSpeedSnapshot() const { return speed_snapshot; }
    int getTieBreaker() const { return tie_breaker; }
};


#endif //UNTITLED_BULLSHIT_ACTION_H