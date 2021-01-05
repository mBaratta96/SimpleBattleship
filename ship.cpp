
#include "ship.h"


Ship::Ship(bool a, int b[2]){
    dir = a;
    for(int i = 0; i < 2; i++)
        start_point[i] = b[i];
}
Ship::~Ship() {delete[] hit;}
bool Ship::isSunk() {return sunk;}
int* Ship::get_start(){return start_point;}
bool Ship::get_dir(){return dir;}
int Ship::get_len(){return len;}
bool Ship::hit_ship(int a, int b){
    if(!dir)
        hit[a-start_point[0]] = true;
    else
        hit[b-start_point[1]] = true;
    bool check = true;
    for(int i=0; i<len; i++)
        check = check && hit[i];
    if (check){
        cout << "SUNK!" << endl;
        sunk = true;
        return true;
    }
    return false;
}

Destroyer::Destroyer(int a, int b[2]): Ship(a, b){
    len = 2;
    hit = new bool[len];
    for(int i =0; i<len; i++)
        hit[i] = false;
}

Submarine::Submarine(int a, int b[2]): Ship(a,b){
    len = 3;
    hit = new bool [len];
    for(int i =0; i<len; i++)
        hit[i] = false;
}

Battleship::Battleship(int a, int b[2]): Ship(a,b){
    len = 4;
    hit = new bool [len];
    for(int i =0; i<len; i++)
        hit[i] = false;
}

Carrier::Carrier(int a, int b[2]): Ship(a,b){
    len = 5;
    hit = new bool [len];
    for(int i =0; i<len; i++)
        hit[i] = false;
}

