#include "Game.hpp"
#include <cstdlib>
#include <iostream>

// Function that handles the actual "playing" of the game
void Game::sim() {
    // Team 1 starts with the ball on their 20 with 1st and 10
    possession = this->t1.id;
    ballPos = 20;
    down = 1;
    ytg = 10;
    
    // Game loop
    playing = true;
    int counter = 0;
    // Trackers for touchdowns and turnovers
    bool td;
    bool to;
    bool punt;
    // Variables for the game log;
    int logYtg, logDown, logBallPos, logPossession;
    while(playing) {
        // PLACEHOLDER slows game speed
        sleep(2);
        // Storage for the game log
        logYtg = ytg;
        logDown = down;
        logBallPos = ballPos;
        logPossession = possession;
        td = false;
        to = false;
        punt = false;
        
        int yards;
        if(down == 4 && ballPos < 80) {
            punt = true;
            to = true;
            yards = puntPlay();
            ytg -= yards;
            ballPos += yards;
            swapPossession();
        } else {
            yards = runPlay();
            ytg -= yards;
            ballPos += yards;
        }
        
        
        
        // Touchdown check
        if(ballPos >= 100) {
            td = true;
            ballPos = 20;
            down = 1;
            ytg = 10;
            if(possession == t1.id) {
                score1 += 7;
                possession = t2.id;
            } else {
                score2 += 7;
                possession = t1.id;
            }
        }
        
        // First down check
        if(ytg < 1) {
            // If it's a first down, reset the down variables
            down = 1;
            ytg = 10;
        } else {
            // If a first down wasn't achieved, increase the down
            down++;
        }
        
        // Fifth down check
        if(down > 4) {
            // Change possession
            to = true;
            swapPossession();
        }
        
        // Game log
        cout << "(" << logDown << " and " << logYtg << " on the " << logBallPos << ") " << (logPossession == t1.id ? t1.name : t2.name) << (punt ? " punt for " : " run for ") << yards << " yards." << endl;
        // If touchdown was scored
        if(td) {
            cout << "TOUCHDOWN! " << score1 << "-" << score2 << endl;
        } else if(to) {
            cout << "Turnover! " << (possession == t1.id ? t1.name : t2.name) << " now has the ball on the " << ballPos << endl;
        }
        
        counter++;
        if(counter >= 100) {
            playing = false;
        }
    }
}

// Called when a team scores
void Game::score(Team t, int points) {
    if(t.id == Game::t1.id) {
        score1 += points;
    } else {
        score2 += points;
    }
}

int Game::runPlay() {
    
    // Random number from 0 - 99 that decides what happens
    int outcome = rand() % 100;
    // If a loss, between -1 and -5 yards
    if(outcome < rLossChance) {
        return -(rand() % 5 + 1);
    }
    // If a short gain, between 0 and 4 yards
    else if(outcome < rLossChance + rShortChance) {
        return rand() % 5;
    }
    // If a medium gain, between 5 and 10 yards
    else if(outcome < rLossChance + rShortChance + rMedChance) {
        return rand() % 6 + 5;
    }
    // If a long gain, between 11 and 25 yards
    else if(outcome < rLossChance + rShortChance + rMedChance + rLongChance) {
        return rand() % 15 + 11;
    }
    return 0;
    
}

int Game::puntPlay() {
    // Random number between 20 and 49
    return rand() % 30 + 20;
}

void Game::swapPossession() {
    down = 1;
    ytg = 10;
    ballPos = 100 - ballPos;
    if(ballPos < 1) {
        ballPos = 1;
    }
    if(possession == t1.id) {
        possession = t2.id;
    } else {
        possession = t1.id;
    }
}

Game::Game(Team pT1, Team pT2) : t1(pT1), t2(pT2) {
    // Initialize score variables
    score1 = 0;
    score2 = 0;
}