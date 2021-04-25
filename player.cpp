//
// Created by Marco on 04/01/2021.
//

#include "player.h"

bool Player::check_position(int count, bool dir, int coords[2]){
    switch(count){
        case 0:
            destroyer = std::make_unique<Destroyer>(dir, coords);
            return board.add_ship(destroyer.get());
        case 1:
            submarine1 = std::make_unique<Submarine>(dir, coords);
            return board.add_ship(submarine1.get());
        case 2:
            submarine2 = std::make_unique<Submarine>(dir, coords);
            return board.add_ship(submarine2.get());
        case 3:
            battleship = std::make_unique<Battleship>(dir, coords);
            return board.add_ship(battleship.get());
        default:
            carrier = std::make_unique<Carrier>(dir, coords);
            return board.add_ship(carrier.get());
    }
}

int Player::launch(int a, int b){
    bool isSunk;
    int result = board.check_coord(a,b);
    if (!result)
        return 0;
    if (result==2)
        isSunk = destroyer->hit_ship(a,b);
    else if (result==3){
        bool s_dir = submarine1->get_dir();
        int * s_start = submarine1->get_start();
        if(!s_dir && a-s_start[0] >=0 && (a-s_start[0])<submarine1->get_len() || s_dir && b-s_start[1]>=0 && (b-s_start[1])<submarine1->get_len())
            isSunk = submarine1->hit_ship(a,b);
        else
            isSunk = submarine2->hit_ship(a,b);
    }else if (result==4)
        isSunk = battleship->hit_ship(a,b);
    else
        isSunk = carrier->hit_ship(a,b);
    return isSunk ? 1:2;
}

bool Player::check_limits(int ship_type, bool dir, int coords[2]) {
    return ship_type == 0 && (!dir && coords[0] + 1 < 10 || dir && coords[1] + 1 < 10) ||
           ship_type == 1 && (!dir && coords[0] + 2 < 10 || dir && coords[1] + 2 < 10) ||
           (ship_type == 2 || ship_type == 3) && (!dir && coords[0] + 3 < 10 || dir && coords[1] + 3 < 10) ||
           ship_type == 4 && (!dir && coords[0] + 4 < 10 || dir && coords[1] + 4 < 10);
}
bool Player::hasLost() {
    return destroyer->isSunk() && submarine1->isSunk() && submarine2->isSunk() && battleship->isSunk() && carrier->isSunk();
}

int get_input(){
    int input;
    while(!(cin >> input)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input.  Try again: ";
    }
    return input;
}


Me::Me(){
    int a,b,c;
    int coords[2];
    bool dir;
    board.print_grid();
    for(int count=0; count<5; count++) {
        bool done = false;
        do {
            do {
                cout << "insert coords: ";
                do {
                    a = get_input();
                    b = get_input();
                    if (a < 0 || a >= 10 || b < 0 || b >= 10)
                        cout << "Not correct. Retry: ";
                } while (a < 0 || a >= 10 || b < 0 || b >= 10);
                coords[0] = a;
                coords[1] = b;
                cout << "insert direction (0 - Vertical/1 - Horizontal): ";
                do {
                    c = get_input();
                    if (!(c == 0 || c == 1))
                        cout << "Not correct. Retry: ";
                } while (!(c == 0 || c == 1));
                dir = (bool) c;
                if (!check_limits(count, dir, coords))
                    cout << "Not Correct" << endl;
            } while (!check_limits(count, dir, coords));
            done = check_position(count, dir, coords);
            if (!done)
                cout << "Wrong Position" << endl;
        } while (!done);
        board.print_grid();
    }
}

void Me::play_game(Player *ad){
    int a,b, launch_result;
    do {
        cout << "insert coordinates: ";
        do {
            a = get_input();
            b = get_input();
            if (a < 0 || a >= 10 || b < 0 || b >= 10)
                cout << "Not correct. Retry: ";
        } while (a < 0 || a >= 10 || b < 0 || b >= 10);
        if (board_adv.isHit(a,b)||board_adv.isMiss(a,b))
            cout << "Already used. ";
    } while (board_adv.isHit(a,b)||board_adv.isMiss(a,b));
    launch_result = ad->launch(a,b);
    if (launch_result)
        board_adv.hit_ship(a, b);
    else
        board_adv.missed_ship(a, b);
    board_adv.print_grid();
}

Adversary::Adversary(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib_grid(0, 9);
    uniform_int_distribution<> distrib_dir(0,1);
    int coords[2];
    bool dir, done;
    for(int count=0; count<5; count++)
        do {
            coords[0] = distrib_grid(gen);
            coords[1] = distrib_grid(gen);
            dir = (bool) distrib_dir(gen);
            done = check_limits(count, dir, coords) && check_position(count, dir, coords);
        } while (!done);
    //cout << "Adversary Grid" << endl;
    //board.print_grid();
}

int Adversary::move(int tried_dirs[4]) {
    vector<int> possible_idx;
    random_device rd;
    mt19937 gen(rd());
    for (int i = 0; i < 4; i++)
        if (tried_dirs[i]!=0)
            possible_idx.push_back(i);
    if (possible_idx.size()>1){
        uniform_int_distribution<> distrib_try(1, possible_idx.size());
        int idx = distrib_try(gen);
        int try_dir = possible_idx[idx-1];
        return try_dir;
    }
    return possible_idx[0];
}

void Adversary::play_game(Player *ad) {
    random_device rd;
    mt19937 gen(rd());
    int launch_result,a,b;
    uniform_int_distribution<> distrib_grid(0, 1);
    uniform_int_distribution<> distrib_dir(0, 1);
    if (!found_first_attack_point) { //starting point
        do {
            a = distrib_grid(gen);
            b = distrib_grid(gen);
        } while (board_adv.isHit(a,b)||board_adv.isMiss(a,b));
        cout << a << b << endl;
        launch_result = ad->launch(a, b);
        if (launch_result) {
            found_first_attack_point = true;
            guessed_pos[0] = a;
            guessed_pos[1] = b;
            board_adv.hit_ship(a,b);
            if (!(board_adv.isHit(a-1,b)||board_adv.isMiss(a-1,b)) && a-1>=0)
                possible_next_attack_points.push_back(make_tuple(a-1, b));
            if (!(board_adv.isHit(a+1,b)||board_adv.isMiss(a+1,b)) && a+1<10)
                possible_next_attack_points.push_back(make_tuple(a+1, b));
            if (!(board_adv.isHit(a,b-1)||board_adv.isMiss(a,b-1)) && b-1>=0)
                possible_next_attack_points.push_back(make_tuple(a, b-1));
            if (!(board_adv.isHit(a,b+1)||board_adv.isMiss(a,b+1)) && b+1<10)
                possible_next_attack_points.push_back(make_tuple(a, b+1));            /*
            tried_dirs[0] = (int)(!(board_adv.isHit(a-1,b)||board_adv.isMiss(a-1,b)) && a-1>=0);
            tried_dirs[1] = (int)(!(board_adv.isHit(a+1,b)||board_adv.isMiss(a+1,b)) && a+1<10);
            tried_dirs[2] = (int)(!(board_adv.isHit(a,b-1)||board_adv.isMiss(a,b-1)) && b-1>=0);
            tried_dirs[3] = (int)(!(board_adv.isHit(a,b+1)||board_adv.isMiss(a,b+1)) && b+1<10);*/
            for(int i = 0; i < possible_next_attack_points.size(); i++){
                cout << get<0>(possible_next_attack_points[i]) << get<1>(possible_next_attack_points[i]) << endl;
            }
        }else{
            board_adv.missed_ship(a,b);
            cout << "Missed!" << endl;
        }
    /*
    }else{
        cout << "Tried Dirs: "<< endl;
        for(int i=0; i<4;i++)
            cout << tried_dirs[i] << endl;
        int try_dir = move(tried_dirs);
        int a = guessed_pos[0]-(try_dir==0)*tried_dirs[0]+(try_dir==1)*tried_dirs[1];
        int b = guessed_pos[1]-(try_dir==2)*tried_dirs[2]+(try_dir==3)*tried_dirs[3];
        cout << a << b << endl;
        launch_result = ad->launch(a, b);
        if (launch_result) {
            board_adv.hit(a, b);
            tried_dirs[try_dir]++;
            if (!direction_found)
                if (try_dir == 0 || try_dir == 1) {
                    direction_found = 1;
                    tried_dirs[2] = 0;
                    tried_dirs[3] = 0;
                } else if (try_dir == 2 || try_dir == 3) {
                    direction_found = 2;
                    tried_dirs[0] = 0;
                    tried_dirs[1] = 0;
                }

        }else {
            board_adv.miss(a,b);
            tried_dirs[try_dir] = 0;
        }
        if (launch_result==1){
            guessed_pos[0]=-1;
            guessed_pos[1]=-1;
            direction_found = 0;
        }else {
            if (guessed_pos[0] - tried_dirs[0] < 0)
                tried_dirs[0] = 0;
            if (guessed_pos[0] + tried_dirs[1] > 9)
                tried_dirs[1] = 0;
            if (guessed_pos[1] - tried_dirs[2] < 0)
                tried_dirs[2] = 0;
            if (guessed_pos[1] + tried_dirs[3] > 9)
                tried_dirs[3] = 0;
            bool check_zeros = false;
            for (int i = 0; i < 4; i++)
                check_zeros = check_zeros || tried_dirs[i] != 0;
            if (!check_zeros) { //work to do: what if no more directions
                guessed_pos[0]=-1;
                guessed_pos[1]=-1;
                direction_found = 0;
            }
        }
    }*/
    cout << "Visione Computer" << endl;
    board_adv.print_grid();
}

