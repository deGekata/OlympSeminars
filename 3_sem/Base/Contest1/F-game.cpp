#include <iostream>
#include <algorithm>

uint8_t find_win_pos(uint8_t** table, int maxX, int maxY, int curX_, int curY_) {
    for (int curX = curX_; curX >= 0; --curX) {
        if (table[curX][curY_] == 2) {
            return 1;
        } 
    }

    for (int curY = curY_; curY >= 0; --curY) {
        if (table[curX_][curY] == 2) {
            return 1;
        } 
    }

    for (; curX_ >= 0 && curY_ >= 0; --curX_, --curY_) {
        if (table[curX_][curY_] == 2) {
            return 1;
        } 
    }

    return 2;
}


int main() {
    int X_, Y_;
    std::cin >> X_ >> Y_;


    uint8_t** winpos = new uint8_t*[X_];
    for (int it = 0; it <= X_; ++it) {
        winpos[it] = new uint8_t[Y_]();
    }

    winpos[0][0] = 1;
    
    for (int x = 0; x <= X_; ++x) {
        for (int y = 0; y <= Y_; ++y) {
            if (x == 0 || y == 0) continue;
            winpos[x][y] = find_win_pos(winpos, X_, Y_, x, y);
        }   
    }

    if (winpos[X_][Y_] == 1) {
        std::cout << "F";
    } else {
        std::cout << "S";
    }


    return 0;
}