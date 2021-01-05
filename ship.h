//
// Created by Marco on 04/01/2021.
//

#ifndef SHIP_H
#define SHIP_H
#include <iostream>
using namespace std;

class Ship {
protected:
    int len;
    bool dir;
    int start_point[2];
    bool *hit;
    bool sunk = false;
public:
    Ship(bool a, int b[2]);
    ~Ship();
    bool isSunk();
    int* get_start();
    bool get_dir();
    int get_len();
    bool hit_ship(int a, int b);
};

class Destroyer: public Ship{
public:
    Destroyer(int a, int b[2]);
};

class Submarine: public Ship{
public:
    Submarine(int a, int b[2]);
};

class Battleship: public Ship{
public:
    Battleship(int a, int b[2]);
};

class Carrier: public Ship{
public:
    Carrier(int a, int b[2]);
};
#endif
