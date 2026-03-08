//
// Created by Badi on 3/2/2026.
//

#include "Ability.h"
#include "Entity.h"
#include <iostream>

void Ability::tickCooldown() {
    if (current_cooldown == 0) {
        return;
    }
    else {
        current_cooldown -= 1;
    }
}

void Ability::resetCooldown() {
    current_cooldown = 0;
}

void Ability::startCooldown() {
    current_cooldown = cooldown;
}

bool Ability::isReady() const {
    return current_cooldown == 0;
}

void BasicAttackAbility::Execute(Entity* caster, Entity* target) {
    int damage = caster->getAttackVal() - target->getDefVal();
    if (damage < 1) {
        damage = 1;
    }

    target->takeDamage(damage);

    std::cout << caster->getName() << " attacks " << target->getName()
              << " for " << damage << " damage.\n";
}

void Impulse1Ability::Execute(Entity* caster, Entity* target) {
    target->addEffect(std::make_unique<Impulse1Effect>(10, 2));
}
