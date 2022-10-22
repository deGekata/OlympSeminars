#include <iostream>
#include <algorithm>

int main() {
    int cnt = 0;
    std::cin >> cnt;

    int* winpos = new int[cnt + 10];
    for (int it = 0; it < cnt + 10; ++it) {
        winpos[it] = 0;
    }
    winpos[1] = 1;
    winpos[0] = 1;

    for (int pos = 2; pos <= cnt; ++pos) {
        int cur_win = 0;
        
        for (int cur_pos = 1; cur_pos*cur_pos <= pos; ++cur_pos) {
            cur_win = std::max(cur_win, winpos[pos - cur_pos]);
        }

        winpos[pos] = (cur_win == 2) ? 1 : 2;
    }

    if (winpos[cnt] == 1)  {
        std::cout << "First";
    } else {
        std::cout << "Second";
    }

    return 0;
}