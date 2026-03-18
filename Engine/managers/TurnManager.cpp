//
// Created by Badi on 3/7/2026.
//

#include "TurnManager.h"

struct ActionOrder {
    bool operator()(const Action& a, const Action& b) const {
        if (a.getPriority() != b.getPriority()) {
            return a.getPriority() < b.getPriority(); // higher priority first
        }
        if (a.getSpeedSnapshot() != b.getSpeedSnapshot()) {
            return a.getSpeedSnapshot() < b.getSpeedSnapshot(); // higher speed first
        }
        if (a.getTieBreaker() != b.getTieBreaker()) {
            return a.getTieBreaker() > b.getTieBreaker(); // smaller tie_breaker wins
        }
        return a.getActor() > b.getActor(); // deterministic fallback
    }
};

void TurnManager::buildExecutionQueue() {

    std::sort(pending_actions.begin(), pending_actions.end(),
              [](const Action& a, const Action& b) {
                  if (a.getPriority() != b.getPriority()) {
                      return a.getPriority() > b.getPriority();
                  }
                  if (a.getSpeedSnapshot() != b.getSpeedSnapshot()) {
                      return a.getSpeedSnapshot() > b.getSpeedSnapshot();
                  }
                  if (a.getTieBreaker() != b.getTieBreaker()) {
                      return a.getTieBreaker() < b.getTieBreaker();
                  }
                  return a.getActor() < b.getActor();
              });

    for (const Action& action : pending_actions) {
        action_queue.push(action);
    }

    pending_actions.clear();
}