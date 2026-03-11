//
// Created by Badi on 3/2/2026.
//

#ifndef UNTITLED_BULLSHIT_ABILITY_H
#define UNTITLED_BULLSHIT_ABILITY_H

#include <utility>
#include <string>
#include <utility>

class Entity;

// Ability.h
class Ability {
protected:
    std::string name;
    int cooldown = 0;
    int current_cooldown = 0;

    virtual void doExecute(Entity* caster, Entity* target) = 0;

public:
    virtual ~Ability() = default;

    void Execute(Entity* caster, Entity* target) {
        if (!caster) return;
        if (!isReady()) return;
        doExecute(caster, target);
        startCooldown();
    }

    void tickCooldown() { if (current_cooldown > 0) --current_cooldown; }
    void startCooldown() { current_cooldown = cooldown; }
    void resetCooldown() { current_cooldown = 0; }
    bool isReady() const { return current_cooldown == 0; }

    const std::string& getName() const { return name; }
    int getCooldown() const { return cooldown; }
    int getCurrentCooldown() const { return current_cooldown; }
};

class BasicAttackAbility : public Ability {
public:
    BasicAttackAbility(std::string name, int cooldown) {
        this->name = std::move(name);
        this->cooldown = cooldown;
    };
    void doExecute(Entity* caster, Entity* target) override;
};

class Impulse1Ability : public Ability {
public:
    Impulse1Ability(std::string name, int cooldown) {
        this->name = std::move(name);
        this->cooldown = cooldown;
    }
    void doExecute(Entity* caster, Entity* target) override;
};


#endif //UNTITLED_BULLSHIT_ABILITY_H
