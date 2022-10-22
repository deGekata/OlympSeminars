#include <iostream>
#include <algorithm>

int main() {
    int N = 0;
    std::cin >> N;


    int* cnt = new int[N + 1]();

    cnt[1] = 1;

    for (int it = 1; it * it <= N; ++it) 
        cnt[it * it] = 1;

    for (int it = 1; it <= N; ++it) {
        for (int sq = 1; (sq * sq + it) <= N; ++sq) {
            if (cnt[it + sq*sq] == 0) {
                cnt[it + sq*sq] = cnt[it] + 1;
            } else {
                cnt[it + sq*sq] = std::min(cnt[it] + 1, cnt[it + sq*sq]);
            }
        }
    }

    std::cout << cnt[N];

    return 0;
}