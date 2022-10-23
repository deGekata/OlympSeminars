#include <iostream>
#include <vector>
#include <algorithm>


#define SLICE(mask, bitpos) (((mask) & (1 << (bitpos))) != 0)

int main() {
    int64_t N, M;
    std::cin >> N >> M;
    if (N > M) std::swap(N, M);

    std::vector<std::vector<int64_t>> dp(2, std::vector<int64_t>(1 << N, 0));
    int64_t mx_mask = 1 << N;
    for (int64_t mask = 0; mask < mx_mask; ++mask) 
        dp[0][mask] = 1;

    bool is_swp_ind = 0;



    for (int64_t col = 1; col < M; ++col) {

        for (int64_t n_mask = 0; n_mask < mx_mask; ++n_mask)
            for (int64_t p_mask = 0; p_mask < mx_mask; ++p_mask) {
                int64_t correct_multiplier = 1;
                for (int64_t line = 0; line < N - 1; ++line) {
                    if ( 
                        SLICE(n_mask, line) == SLICE(n_mask, line + 1) &&
                        SLICE(n_mask, line) == SLICE(p_mask, line) &&
                        SLICE(n_mask, line) == SLICE(p_mask, line + 1)
                    ) {
                        correct_multiplier = 0;
                        break;
                    }
                }
                dp[not is_swp_ind][n_mask] += correct_multiplier * dp[is_swp_ind][p_mask];
            }
        
        for (int64_t mask = 0; mask < mx_mask; ++mask) 
            dp[is_swp_ind][mask] = 0;
        
        is_swp_ind = !is_swp_ind;


    }

    int64_t ans = 0;

    for (auto elem: dp[is_swp_ind])
        ans += elem;

    std::cout << ans;







    return 0;
}