//
// Created by Badi on 3/3/2026.
//

#ifndef UNTITLED_BULLSHIT_BATTLECONTEXT_H
#define UNTITLED_BULLSHIT_BATTLECONTEXT_H

#include <iostream>
#include <vector>
#include <memory>
#include "Entity.h"
#include "../managers/TurnManager.h"

enum class Rank {
    S,
    A,
    B,
    C,
    D,
    F
};

class BattleContext {
private:
    int turn_count = 0;
    Rank rank;
    bool escape_success = false;

    std::vector<Entity*> allied_party;
    std::vector<Entity*> enemy_party;
    TurnManager manager;

    BattleContext() = default;

    bool isEntityInBattle(const Entity* entity) const {
        if (!entity) return false;

        for (const Entity* ally : allied_party) {
            if (ally == entity) return true;
        }
        for (const Entity* enemy : enemy_party) {
            if (enemy == entity) return true;
        }
        return false;
    }

    bool hasLivingAllies() const {
        for (const Entity* ally : allied_party) {
            if (ally && ally->isEntityAlive()) {
                return true;
            }
        }
        return false;
    }

    bool hasLivingEnemies() const {
        for (const Entity* enemy : enemy_party) {
            if (enemy && enemy->isEntityAlive()) {
                return true;
            }
        }
        return false;
    }

    void resolveAttack(Entity* actor, Entity* target) {
        if (!target || !target->isEntityAlive()) {
            std::cout << "[INFO] Attack skipped: invalid or dead target.\n";
            return;
        }

        std::cout << actor->getName() << " attacks " << target->getName() << "!\n";

        int damage = actor->getAttackVal() - target->getDefVal();
        if (damage < 1) damage = 1;

        target->takeDamage(damage);

        std::cout << damage << " damage dealt to " << target->getName() << ".\n";
    }

    void resolveDefend(Entity* actor) {
        std::cout << actor->getName() << " takes a defensive stance!\n";
        actor->addEffect(std::make_unique<GuardEffect>());
    }

    void resolveAbility(Entity* actor, Entity* target, Ability* used_ability) {
        if (!used_ability) {
            std::cout << "[ERROR] Ability action has null ability.\n";
            return;
        }

        if (!target || !target->isEntityAlive()) {
            std::cout << "[INFO] Ability skipped: invalid or dead target.\n";
            return;
        }

        std::cout << actor->getName();

        if (used_ability->getAbilityType() == AbilityType::Physical) {
            std::cout << " wells up their stamina!\n";
            std::cout << actor->getName() << " performs " << used_ability->getName() << "!\n";
        }
        else if (used_ability->getAbilityType() == AbilityType::Magical) {
            std::cout << " channels their mana!\n";
            std::cout << actor->getName() << " casts " << used_ability->getName() << "!\n";
        }
        else if (used_ability->getAbilityType() == AbilityType::Primordial) {
            std::cout << " calls upon their soul.\n";
            std::cout << actor->getName() << " manifests " << used_ability->getName() << "!\n";
        }

        used_ability->execute(actor, target);
    }

    void resolveEscape(Entity* actor) {
        std::cout << actor->getName() << " attempts to escape!\n";
        escape_success = true;
    }

public:
    static BattleContext& getInstance() {
        static BattleContext instance;
        return instance;
    }

    void resetBattle() {
        turn_count = 0;
        rank = Rank::B;
        escape_success = false;
        allied_party.clear();
        enemy_party.clear();
        manager = TurnManager();
    }

    void addAllyActor(Entity* actor) {
        if (actor) allied_party.push_back(actor);
    }

    void addEnemyActor(Entity* actor) {
        if (actor) enemy_party.push_back(actor);
    }

    bool isBattleFinished() const {
        return escape_success || !hasLivingAllies() || !hasLivingEnemies();
    }

    bool didAlliesWin() const {
        return hasLivingAllies() && !hasLivingEnemies();
    }

    bool didEnemiesWin() const {
        return !hasLivingAllies() && hasLivingEnemies();
    }

    bool didEscapeSucceed() const {
        return escape_success;
    }

    void resolveAction(const Action& queued_action) {
        ActionType type = queued_action.getActionType();
        Ability* used_ability = queued_action.getAbility();
        Entity* actor = queued_action.getActor();
        Entity* target = queued_action.getTarget();

        if (!actor) {
            std::cout << "[ERROR] Null actor in action.\n";
            return;
        }

        if (!isEntityInBattle(actor)) {
            std::cout << "[INFO] Action skipped: actor is not part of this battle.\n";
            return;
        }

        if (!actor->isEntityAlive()) {
            std::cout << "[INFO] Action skipped: " << actor->getName() << " is already defeated.\n";
            return;
        }

        if (type == ActionType::Attack) {
            resolveAttack(actor, target);
        }
        else if (type == ActionType::Defend) {
            resolveDefend(actor);
        }
        else if (type == ActionType::Ability) {
            resolveAbility(actor, target, used_ability);
        }
        else if (type == ActionType::Escape) {
            resolveEscape(actor);
        }
        else {
            std::cout << "[ERROR] Illegal ActionType value.\n";
        }
    }

    void processTurn() {
        if (isBattleFinished()) return;

        turn_count++;
        std::cout << "\n===== TURN " << turn_count << " =====\n";

        manager.buildExecutionQueue();

        while (manager.hasActions() && !isBattleFinished()) {
            Action current_action = manager.popNextAction();
            resolveAction(current_action);
        }

        for (Entity* ally : allied_party) {
            if (ally && ally->isEntityAlive()) {
                ally->onTurnEnd();
            }
        }

        for (Entity* enemy : enemy_party) {
            if (enemy && enemy->isEntityAlive()) {
                enemy->onTurnEnd();
            }
        }
    }

    int getTurnCount() const {
        return turn_count;
    }

    Rank getRank() const {
        return rank;
    }

    TurnManager& getTurnManager() {
        return manager;
    }

    const std::vector<Entity*>& getAlliedParty() const {
        return allied_party;
    }

    const std::vector<Entity*>& getEnemyParty() const {
        return enemy_party;
    }
};

#endif //UNTITLED_BULLSHIT_BATTLECONTEXT_H
