#include <iostream>
#include <algorithm>
// 0 1 1 0 1 
// 1 1 1 1 1 
// 1 1 1 1 1 
// 1 1 1 1 1 
// 1 0 0 0 0

// 0 1 1 0 1
// 1 1 2 1 1
// 1 2 2 2 2
// 1 2 3 3 3
// 1 0 0 0 0

int main() {
    int N = 0;
    std::cin >> N;

    if (N == 1) {
        int tmp;
        std::cin >> tmp;
        std::cout << tmp;
        return 0; 
    }

    int* prev = new int[N]();
    int* cur  = new int[N]();


    for (int it = 0; it < N; ++it) {
        std::cin >> prev[it];
    }

    int mx = 0;
    for (int row = 0; row < (N-1); ++row) {
        for (int col = 0; col < N; ++col)
            std::cin >> cur[col];
        
        for (int col = 1; col < N; ++col) {
            if (cur[col] == 0) continue;

            cur[col] = std::min(std::min(cur[col - 1], prev[col - 1]), prev[col]) + 1;
            mx = std::max(mx, cur[col]);
        }

        std::swap(prev, cur);
    }

    std::cout << mx;

    return 0;
}
