//
// Created by Marco on 04/01/2021.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include <memory>
#include <random>
#include "ship.h"
#include "board.h"

class Player{
protected:
    unique_ptr<Destroyer> destroyer;
    unique_ptr<Submarine> submarine1;
    unique_ptr<Submarine> submarine2;
    unique_ptr<Battleship> battleship;
    unique_ptr<Carrier> carrier;
    Board board, board_adv;
public:
    bool check_position(int count, bool dir, int coords[2]);
    int launch(int a, int b);
    bool check_limits(int ship_type, bool dir, int coords[2]);
    bool hasLost();
};

class Me: public Player{

public:
    Me();
    void play_game(Player *ad);
};

class Adversary: public Player{
private:
    int guessed_pos[2]{-1, -1};
    int tried_dirs[4];
    bool direction[2]{false, false};
    bool found_first_attack_point{false};
    vector<tuple<int, int>> possible_next_attack_points;
public:
    Adversary();
    void play_game(Player *ad);
    int move(int tried_dirs[4]);
};
#endif //UNTITLED_PLAYER_H
