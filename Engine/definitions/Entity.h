//
// Created by Badi on 3/2/2026.
//

#ifndef UNTITLED_BULLSHIT_ENTITY_H
#define UNTITLED_BULLSHIT_ENTITY_H

#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include "Ability.h"
#include "Effect.h"

struct Stats{
    int max_HP;
    int attack;
    int defense;
    int speed;
};

class Entity {
private:
    std::string name;
    Stats base_stats {};
    int current_HP;
    std::vector<std::unique_ptr<Effect>> active_effects;
    std::vector<std::unique_ptr<Ability>> skill_list;

public:
    Entity(std::string name, int max_HP, int attack, int defense, int speed)
    {
        this->name = std::move(name);
        this->base_stats.max_HP = max_HP;
        this->current_HP = max_HP;
        this->base_stats.attack = attack;
        this->base_stats.defense = defense;
        this->base_stats.speed = speed;
    };

    const std::string& getName() const {
        return name;
    }

    int getCurrentHP() const {
        return current_HP;
    }

    bool isEntityAlive() const {
        return current_HP > 0;
    }

    void onTurnStart() {
        for (auto& effect : active_effects) {
            effect->onTurnStart(*this);
        }
    }

    void onTurnEnd() {

        for (auto& ability : skill_list) {
            ability->tickCooldown();
        }

        for (auto& effect : active_effects) {
            effect->onTurnEnd(*this);
            effect->reduceDuration();
        }

        removeExpiredEffects();
    }

    void addAbility(std::unique_ptr<Ability> a) {
        skill_list.push_back(std::move(a));
    }

    size_t abilityCount() const { return skill_list.size(); }

    Ability* chooseAbility(size_t i) const {
        if (i >= skill_list.size()) return nullptr;
        return skill_list[i].get();
    }

    void removeExpiredEffects() {
        active_effects.erase(
                std::remove_if(active_effects.begin(), active_effects.end(),
                               [](const std::unique_ptr<Effect>& effect) {
                                   return effect->isExpired();
                               }),
                active_effects.end()
        );
    }

    void takeDamage(int damage_amount) {
        current_HP -= damage_amount;
        if (current_HP < 0) {
            current_HP = 0;
        }
    }

    void heal(int healing_amount) {
        current_HP += healing_amount;
        if (current_HP > base_stats.max_HP) {
            current_HP = base_stats.max_HP;
        }
    }

    void addEffect(std::unique_ptr<Effect> target_effect) {
        active_effects.push_back(std::move(target_effect));
    }

    int getAttackVal() const {
        int attack_value = base_stats.attack;
        for (const auto& effect:active_effects) {
            attack_value = effect->modifyAttackVal(attack_value);
        }
        return attack_value;
    };

    int getDefVal() const {
        int defense_value = base_stats.defense;
        for (const auto& effect:active_effects) {
            defense_value = effect->modifyDefenseVal(defense_value);
        }
        return defense_value;
    };

    int getSpeVal() const {
        int speed_value = base_stats.speed;
        for (const auto& effect:active_effects) {
            speed_value = effect->modifySpeedVal(speed_value);
        }
        return speed_value;
    };
};


#endif //UNTITLED_BULLSHIT_ENTITY_H
