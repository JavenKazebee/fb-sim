#include <iostream>
#include "Game.hpp"
#include "Team.hpp"
#include <thread>

int main() {
    srand((int) time(0));
    // Create test teams and test game
    Team t1(0, "Vikings");
    Team t2(1, "Jaguars");
    Game g(t1, t2);
    g.sim();
}

