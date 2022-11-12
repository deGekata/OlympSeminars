#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <bit>
#include <stdio.h>

std::unordered_map<uint64_t, uint64_t> dp;
int M, N;

inline uint64_t mask_place1x2(uint64_t mask, int min_zero_bit) {
    int x = min_zero_bit % M;
    int y = min_zero_bit / M;
    
    if (x < M - 1 && (mask & (1ull << (y * M + x + 1))) == 0) 
        return (mask | (1ull << (y * M + x + 1)) | (1ull << min_zero_bit));

    return mask;
}

inline uint64_t mask_place2x1(uint64_t mask, int min_zero_bit) {
    int x = min_zero_bit % M;
    int y = min_zero_bit / M;
    
    if (y < N - 1 && (mask & (1ull << ((y + 1) * M + x))) == 0) 
        return (mask | (1ull << ((y + 1) * M + x)) | (1ull << min_zero_bit));

    return mask;
}

inline uint64_t mask_place1x3(uint64_t mask, int min_zero_bit) {
    int x = min_zero_bit % M;
    int y = min_zero_bit / M;
    
    if (x < M - 2 && (mask & (1ull << (y * M + x + 1))) == 0 && (mask & (1ull << (y * M + x + 2))) == 0) 
        return (mask | (1ull << min_zero_bit) | (1ull << (y * M + x + 1)) | (1ull << (y * M + x + 2)));

    return mask;
}

inline uint64_t mask_place3x1(uint64_t mask, int min_zero_bit) {
    int x = min_zero_bit % M;
    int y = min_zero_bit / M;
    
    if (y < N - 2 && (mask & (1ull << ((y + 1) * M + x))) == 0 && (mask & (1ull << ((y + 2) * M + x))) == 0) 
        return (mask | (1ull << min_zero_bit) | (1ull << ((y + 1) * M + x)) | (1ull << ((y + 2) * M + x)));

    return mask;
}

int solve(uint64_t mask, int cur_free) {
    if (cur_free == 0) {
        dp.insert({mask, 1});
    }
    if (dp.contains(mask)) return dp.at(mask);

    uint64_t ans = 0;

    int min_zero_bit = __builtin_ctzll(~mask);

    if (mask != mask_place1x2(mask, min_zero_bit)) {
        ans += solve(mask_place1x2(mask, min_zero_bit), cur_free - 2);
    }

    if (mask != mask_place2x1(mask, min_zero_bit)) {
        ans += solve(mask_place2x1(mask, min_zero_bit), cur_free - 2);
    }

    if (mask != mask_place1x3(mask, min_zero_bit)) {
        ans += solve(mask_place1x3(mask, min_zero_bit), cur_free - 3);
    }

    if (mask != mask_place3x1(mask, min_zero_bit)) {
        ans += solve(mask_place3x1(mask, min_zero_bit), cur_free - 3);
    }

    dp.insert({mask, ans});
    return ans;
}

int main() {
    std::cin >> N >> M;
    uint64_t mask;
    if (M > N) std::swap(M, N);
    // if (N * M < 2) {
    //     std::coo
    // }
    // std::cin >> mask;
    // std::cout << mask_place1x2((uint64_t)mask, __builtin_ctzll(~mask)) << "\n";
    // std::cout << mask_place2x1((uint64_t)mask, __builtin_ctzll(~mask)) << "\n";
    // std::cout << mask_place1x3((uint64_t)mask, __builtin_ctzll(~mask)) << "\n";
    // std::cout << mask_place3x1((uint64_t)mask, __builtin_ctzll(~mask)) << "\n";
    solve(0, N * M);
    std::cout << dp[0] << "\n";

    return 0;
}