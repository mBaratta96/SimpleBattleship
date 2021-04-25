//
// Created by Marco on 04/01/2021.
//
#include "board.h"
// create grid of empty spaces
Board::Board(){
    for(int i=0; i<10; i++)
        for(int j=0; j<10; j++)
            grid[i][j] = free;
}

void Board::print_grid(){
    cout << "   ";
    for(int i=0; i<10; i++) {
        char n = '0'+i;
        char s[4] = {' ', n, ' ', '\0'};
        cout << s;
    }
    cout << '\n';
    for(int i=0; i<10; i++) {
        char n = '0'+i;
        char s[4] = {' ', n, ' ', '\0'};
        cout << s;
        for (int j = 0; j < 10; j++) {
            char s[4] = {'[', grid[i][j], ']', '\0'};
            cout << s;
        }
        cout << '\n';
    }
    cout << '\n';
}
//ship is added by using its length as identifier 
bool Board::add_ship(Ship* s){
    bool dir_s = s->get_dir();
    int *start_s = s->get_start();
    int len_s = s->get_len();
    bool is_free = true;

    for(int i=0; i<len_s; i++)
        is_free = is_free * (grid[start_s[0]+i*(!dir_s)][start_s[1]+i*dir_s]==free);
    if (is_free)
        for(int i=0; i<len_s; i++)
            grid[start_s[0]+i*(!dir_s)][start_s[1]+i*dir_s] = '0'+len_s;
    return is_free;
}

int Board::check_coord(int a, int b){
    if (grid[a][b] != free) {
        cout << "HIT!" << endl;
        int ship_n = (int) (grid[a][b] - '0');
        grid[a][b] = hit;
        return ship_n;
    }
    cout << "MISS!" << endl;
    return 0;
}

void Board::hit_ship(int a, int b){
    grid[a][b] = hit;
}

void Board::missed_ship(int a, int b){
    grid[a][b] = miss;
}

bool Board::isHit(int a, int b) {
    return grid[a][b]==hit;
}

bool Board::isMiss(int a, int b) {
    return grid[a][b]==hit;
}
