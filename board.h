//
// Created by Marco on 04/01/2021.
//

#ifndef BOARD_H
#define BOARD_H
#define HIT 'X'
#define MISS 'O'
#define FREE ' '
#define OCCUPIED 'Y'
#include <iostream>
#include "ship.h"
using namespace std;

class Board{
private:
    char grid[10][10];
public:
    Board();
    void print_grid();
    bool add_ship(Ship* s);
    int check_coord(int a, int b);
    void hit(int a, int b);
    void miss(int a, int b);
    bool isHit(int a, int b);
    bool isMiss(int a, int b);
};


#endif //UNTITLED_BOARD_H
