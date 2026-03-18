//
// Created by Badi on 3/3/2026.
//

#ifndef UNTITLED_BULLSHIT_EFFECT_H
#define UNTITLED_BULLSHIT_EFFECT_H

class Entity;

class Effect {
protected:
    int duration{0};
public:
    virtual ~Effect() = default;

    virtual void onTurnStart(Entity& entity) {};
    virtual void onTurnEnd(Entity& entity) {};

    bool isExpired() const {
        return duration <= 0;
    }

    void reduceDuration() {
        if (isExpired()) {
            return;
        }
        else {
            duration--;
        };
    };
    virtual int modifyAttackVal (int current_value) const { return current_value;}
    virtual int modifyDefenseVal (int current_value) const { return current_value;}
    virtual int modifySpeedVal (int current_value) const { return current_value;}

};

class Impulse1Effect : public Effect {
private:
    int speed_bonus;
public:
    Impulse1Effect(int speed_bonus = 10, int turn_duration = 2)
            : speed_bonus(speed_bonus)
    {
        this->duration = turn_duration;
    }

    int modifySpeedVal(int current_value) const override {
        return current_value + speed_bonus;
    }
};

class GuardEffect : public Effect {
public:
    GuardEffect() {
        duration = 1;
    }

    int modifyDefenseVal(int current_value) const override {
        return current_value + (current_value / 4);
    }
};

#endif //UNTITLED_BULLSHIT_EFFECT_H
