#ifndef Game_hpp
#define Game_hpp

#include "Team.hpp"
#include <stdio.h>

class Game {
    // Stores the teams involved
    Team t1, t2;
    // Game status variables
    int score1, score2, ballPos, down, ytg, possession;
    // Simulation control variables
    int rLossChance = 20, rShortChance = 50, rMedChance = 20, rLongChance = 10;
    int pLossChance, pShortChance, pMedChance, pLongChance, pIncompleteChance, pInterceptChance;
    // Game loop control
    bool playing;
public:
    void sim();
    int runPlay();
    int puntPlay();
    void passPlay();
    void swapPossession();
    void score(Team t, int points);
    Game(Team pT1, Team pT2);
};

#endif