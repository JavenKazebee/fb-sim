#ifndef Team_hpp
#define Team_hpp

#include <stdio.h>
#include <string>
using namespace std;

class Team {
public:
    int id;
    int run, pass;
    string name;
    Team(int pId, string n);
};

#endif