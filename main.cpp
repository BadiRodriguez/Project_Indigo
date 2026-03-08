#include <iostream>
#include "Engine/definitions/Entity.h"
#include <memory>

void printDivider() {
    std::cout << "----------------------------------------" << std::endl;
}

void printGrandDivider() {
    std::cout << "--<<(<-|[->{<O>}<-]|-->)>>--" << std::endl;
 }

void printInitiativeResult(const Entity& first, const Entity& second) {
    std::cout << "[INITIATIVE CHECK]" << std::endl;
    std::cout << first.getName() << " speed: " << first.getSpeVal() << std::endl;
    std::cout << second.getName() << " speed: " << second.getSpeVal() << std::endl;

    if (first.getSpeVal() >= second.getSpeVal()) {
        std::cout << "Result: " << first.getName() << " would act first." << std::endl;
    } else {
        std::cout << "Result: " << second.getName() << " would act first." << std::endl;
    }
}

void printSpeedTest(Entity& entity) {
    printDivider();
    std::cout << "[TEMPORARY EFFECT TEST]" << std::endl;
    std::cout << "Target entity: " << entity.getName() << std::endl;

    std::cout << "Base speed: " << entity.getSpeVal() << std::endl;

    entity.addEffect(std::make_unique<Impulse1Effect>());
    std::cout << "After applying Impulse1Effect: " << entity.getSpeVal() << std::endl;

    entity.onTurnEnd();
    std::cout << "After first turn ends: " << entity.getSpeVal() << std::endl;

    entity.onTurnEnd();
    std::cout << "After second turn ends: " << entity.getSpeVal() << std::endl;

    std::cout << "Expected behavior: speed increases temporarily, then returns to base value."
              << std::endl;
}

void printAbilityActivation(Entity& entity) {
    std::cout << "[ABILITY ACTIVATION TEST]" << std::endl;
    std::cout << "Target entity: " << entity.getName() << std::endl;
    std::cout << "Base speed: " << entity.getSpeVal() << std::endl;
    std::cout << "Attempting to cast: Impulse1" << std::endl;
    Impulse1Ability instance = {"Impulse1", 3};
    instance.Execute(&entity, &entity);
    std::cout << "After applying Impulse1Effect: " << entity.getSpeVal() << std::endl;
    entity.onTurnEnd();
    std::cout << "After first turn ends: " << entity.getSpeVal() << std::endl;
    entity.onTurnEnd();
    std::cout << "After second turn ends: " << entity.getSpeVal() << std::endl;
}

void printAbilityActivation_2(Entity& caster, Entity& target, size_t abilityIndex) {
    std::cout << "[ABILITY ACTIVATION TEST 2]\n";
    std::cout << "Caster: " << caster.getName() << " | HP: " << caster.getCurrentHP()
              << " | Speed: " << caster.getSpeVal() << "\n";
    std::cout << "Target: " << target.getName() << " | HP: " << target.getCurrentHP()
              << " | Speed: " << target.getSpeVal() << "\n";

    Ability* ab = caster.chooseAbility(abilityIndex);
    if (!ab) {
        std::cout << "ERROR: caster has no ability at index " << abilityIndex << "\n";
        return;
    }

    auto printAbilityState = [&](const char* label) {
        std::cout << label << " '" << ab->getName() << "'"
                  << " | ready=" << (ab->isReady() ? "yes" : "no")
                  << " | current_cd=" << ab->getCurrentCooldown()
                  << " | base_cd=" << ab->getCooldown()
                  << "\n";
    };

    printAbilityState("Before use:");

    if (!ab->isReady()) {
        std::cout << "Ability not ready; skipping Execute.\n";
    } else {
        std::cout << "Executing...\n";
        ab->Execute(&caster, &target);

        // Start cooldown AFTER a successful use
        ab->startCooldown();
        printAbilityState("After use:");
    }

    // Demonstrate cooldown ticking via onTurnEnd()
    int steps = ab->getCooldown() + 2; // +2 so you can see it return to ready
    for (int turn = 1; turn <= steps; ++turn) {
        caster.onTurnEnd(); // this should call ability->tickCooldown() internally
        std::cout << "After caster.onTurnEnd() tick " << turn << ": ";
        std::cout << "ready=" << (ab->isReady() ? "yes" : "no")
                  << " current_cd=" << ab->getCurrentCooldown()
                  << "\n";
    }

    std::cout << "Final HP | Caster: " << caster.getCurrentHP()
              << " | Target: " << target.getCurrentHP() << "\n";
}

void printBattleSimulation(Entity& entity_1, Entity& entity_2) {
    std::vector<Entity*> player_party;
    std::vector<Entity*> enemy_party;
    player_party.push_back(&entity_1);
    enemy_party.push_back(&entity_2);
}

int main() {
    std::cout << "[ENGINE TEST START]" << std::endl;
    printDivider();

    Entity player("test_player", 100, 18, 14, 20);
    Entity enemy("test_enemy", 85, 9, 10, 25);

    std::cout << "[ENTITY LOAD]" << std::endl;
    std::cout << "Loaded entity: " << player.getName() << std::endl;
    std::cout << "Loaded entity: " << enemy.getName() << std::endl;

    printDivider();
    printInitiativeResult(player, enemy);

    printSpeedTest(player);
    printDivider();

    printAbilityActivation(player);
    printDivider();

    player.addAbility(std::make_unique<Impulse1Ability>("Impulse1", 3));
    player.addAbility(std::make_unique<BasicAttackAbility>("Basic Attack", 0));

    printAbilityActivation_2(player, player, 0); // cast Impulse1 on self
    printAbilityActivation_2(player, enemy, 1);  // basic attack enemy

    printDivider();

    std::cout << "[ENGINE TEST END]" << std::endl;

    return 0;
}