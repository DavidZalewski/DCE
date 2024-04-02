#pragma once

class WeaponSkill {
public:
    float accuracy;
    float minimumDamage;
    float maximumDamage;
    float currentSkill;

    WeaponSkill(float accuracy, float minimumDamage, float maximumDamage, float currentSkill)
        : accuracy(accuracy), minimumDamage(minimumDamage), maximumDamage(maximumDamage), currentSkill(currentSkill) {}
};