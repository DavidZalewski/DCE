#pragma once


class PsychologicalProfile {
public:
    float currentStress;
    float stressTolerance;
    float stressRecoveryRate;

    PsychologicalProfile(float currentStress, float stressTolerance, float stressRecoveryRate)
        : currentStress(currentStress), stressTolerance(stressTolerance), stressRecoveryRate(stressRecoveryRate) {}
};