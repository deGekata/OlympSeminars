#include <iostream>
#include <vector>
#include <algorithm>





int main() {
    int sets, cities;
    std::cin >> cities >> sets;

    std::vector<std::vector<int>> matrix(sets, std::vector<int>(cities + 2, INT32_MAX));
    std::vector<std::vector<int>> dp(sets, std::vector<int>(cities + 2, INT32_MAX));


    for (int row = 1; row <= cities; ++row) {
        for (int col = 0; col < sets; ++col) {
            std::cin >> matrix[col][row];
        }
        // for (int col = 0; col < sets; ++col) {
            // std::cout << matrix[col][row] << " ";
        // }
        // std::cout << " this\n";
    }
int ans = INT32_MAX;

    // for (int city = 1; city <= cities; ++city) {
    //     std::cout << "cur dp[city... " << matrix[0][city] << "\n";
    //     ans = std::min(ans, matrix[sets - 1][city]);
    // }


    for (int row = 1; row <= cities; ++row) {
        dp[sets - 1][row] = matrix[sets - 1][row];
    }

    for (int cur_set = sets - 2; cur_set >= 0; --cur_set) {
        for (int city = 1; city <= cities; ++city) {
            dp[cur_set][city] = std::min(
                std::min(dp[cur_set + 1][city + 1], dp[cur_set + 1][city - 1]),
                dp[cur_set + 1][city]
            ) + matrix[cur_set][city];
        }
        // std::cout << "set\n";
    }

    ans = INT32_MAX;
    int pos = -1;
    // ans = 
    for (int city = 1; city <= cities; ++city) {
        // std::cout << "cur dp[city... " << dp[0][city] << "\n";
        if (ans > dp[0][city]) {
            ans = dp[0][city];
            pos = city;
        }
    }


    // for (int city = 1; city <= cities; ++city) {
    //     for (int cur_set = 0; cur_set < sets; ++cur_set) {
    //         std::cout << dp[cur_set][city] << ' ';
    //     }
    //     std::cout << "\n";
    //     // std::cout << "set\n";
    // }

    std::vector<int> tracert(sets);
    tracert[0] = pos;
    for (int cur_set = 1; cur_set < sets; ++cur_set) {
        if (dp[cur_set - 1][pos] == (dp[cur_set][pos - 1] + matrix[cur_set - 1][pos])) {
            // std::cout << matrix[cur_set][pos - 1] << " iter-1 ";
            tracert[cur_set] = pos - 1;
            pos = pos - 1;
            continue;
        }
        if (dp[cur_set - 1][pos] == (dp[cur_set][pos] + matrix[cur_set - 1][pos])) {
            // std::cout << matrix[cur_set][pos] << " iter ";
            tracert[cur_set] = pos;
            pos = pos;
            continue;
        }
        if (dp[cur_set - 1][pos] == (dp[cur_set][pos + 1] + matrix[cur_set - 1][pos])) {
            // std::cout << matrix[cur_set][pos + 1] << " iter+1 ";
            tracert[cur_set] = pos + 1;
            pos = pos + 1;
            continue;
        }
    }
    // std::cout << "\n";

    for (auto it: tracert) {
        std::cout << it << " ";
    }
    std::cout << "\n" << ans << " ";


    return 0;
}