//
// Created by Badi on 3/8/2026.
//

#ifndef UNTITLED_BULLSHIT_ACTION_H
#define UNTITLED_BULLSHIT_ACTION_H

#include "Entity.h"

enum class ActionType { Attack, Ability };

struct Action {
    Entity* actor;
    Entity* target;      // can be null for self-target later
    Ability* ability;    // null for basic attack if you want
    int priority;        // higher goes first
    int speedSnapshot;   // actor speed at planning time
    int tieBreaker;      // increasing counter to keep stable order
};



#endif //UNTITLED_BULLSHIT_ACTION_H
