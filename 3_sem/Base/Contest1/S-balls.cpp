#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int64_t Hei, Balls;
    std::cin >> Hei >> Balls;
    
    //No balls
    if (Balls == 0 && Hei > 1) {
        std::cout << -1;
        return 0;
    }


    //only one ball, check with delta 1 m
    if (Balls == 1) {
        std::cout << Hei - 1;
        return 0;
    }

    std::vector<std::vector<int64_t>> cache(2);

    bool is_swap = false;

    int64_t cur_floor = 1;
    int64_t sm = 1;
    //base
    cache[is_swap].push_back(cur_floor);
    int64_t cur_balls = Balls + 1;

    for (; sm < Hei;) {
        sm = 0, cur_floor++;
        cur_balls = Balls + 1;

        if (cur_balls != 0) 
            sm++, cur_balls--, cache[not is_swap].push_back(1);

        for (int64_t pref_floor = 1; pref_floor < cur_floor - 1; pref_floor++) {
            cache[not is_swap].push_back(
                                         cache[is_swap][pref_floor] + 
                                         cache[is_swap][pref_floor - 1] 
                                        );

            if (cur_balls != 0) 
                sm = sm + cache[is_swap][pref_floor] + cache[is_swap][pref_floor - 1], cur_balls--;
        }

        if (cur_balls != 0) sm++, cur_balls--, cache[not is_swap].push_back(1);

        cache[is_swap].clear();
        is_swap =  not is_swap;
    }

    std::cout << cur_floor - 1;
}