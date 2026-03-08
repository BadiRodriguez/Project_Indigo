//
// Created by Badi on 3/2/2026.
//

#ifndef UNTITLED_BULLSHIT_ABILITY_H
#define UNTITLED_BULLSHIT_ABILITY_H

#include <utility>
#include <string>
#include <utility>

class Entity;

class Ability {
protected:
    std::string name;
    int cooldown = 0;
    int current_cooldown = 0;
public:
    virtual void Execute(Entity* caster, Entity* target) = 0;
    void tickCooldown();
    void startCooldown();
    void resetCooldown();

    virtual ~Ability() = default;

    bool isReady() const;
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
    void Execute(Entity* caster, Entity* target) override;
};

class Impulse1Ability : public Ability {
public:
    Impulse1Ability(std::string name, int cooldown) {
        this->name = std::move(name);
        this->cooldown = cooldown;
    }
    void Execute(Entity* caster, Entity* target) override;
};


#endif //UNTITLED_BULLSHIT_ABILITY_H
