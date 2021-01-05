#include "ship.h"
#include "board.h"
#include "player.h"

int main() {
    Adversary ad;
    Me me;
    cout << "Let's play!!!" << endl;
    while (true){
        me.play_game(&ad);
        ad.play_game(&me);
        if (me.hasLost()||ad.hasLost())
            break;
    }
    if (me.hasLost())
        cout << "YOU LOST" << endl;
    else
        cout << "YOU WIN" << endl;
    return 0;
}
