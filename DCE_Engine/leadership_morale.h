#pragma once


class LeadershipMorale {
public:
    float currentOpinion;
    float decisiveness;
    float decisionMaking;
    float hesitation;
    float offense;

    LeadershipMorale(float currentOpinion, float decisiveness, float decisionMaking, float hesitation, float offense)
        : currentOpinion(currentOpinion), decisiveness(decisiveness), decisionMaking(decisionMaking), hesitation(hesitation), offense(offense) {}
};