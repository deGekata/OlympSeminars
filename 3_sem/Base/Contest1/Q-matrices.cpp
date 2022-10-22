#include <iostream>
#include <string>
#include <vector>


inline int64_t calc_mul_op(std::pair<int, int> left, std::pair<int, int> right) {
    return left.first * left.second * right.second;
}


int main() {

    int cnt;
    std::cin >> cnt;
    std::vector<std::pair<int, int>> dimensions(cnt - 1);
    std::cin >> dimensions[0].first >> dimensions[0].second;
    cnt--;
    
    for (int it = 1; it < cnt; ++it) {
        dimensions[it].first = dimensions[it - 1].second;
        std::cin >> dimensions[it].second;
    }

    // for (int it = 0; it < cnt; ++it) {
    //     std::cout << dimensions[it].first << "  " << dimensions[it].second << '\n';
    // }


    std::vector<std::vector<int64_t>> dp(dimensions.size(), std::vector<int64_t>(dimensions.size(), 0));

    for (int it = 0; it < cnt - 1; ++it) {
        dp[it][it + 1] = calc_mul_op(dimensions[it], dimensions[it + 1]);
    }

    // std::cout << "base\n\t";
    //  for (int col = 0; col < cnt; ++col) {
    //     std::cout << '\t' << col;
    // }
    // std::cout << '\n';
    // for (int row = 0; row < cnt; ++row) {
    //     std::cout << "row:\t" <<  row << ':';
    //     for (int col = 0; col < cnt; ++col) {
    //         std::cout << '\t' << dp[row][col];
    //     }
    //     std::cout << '\n';
    // }


    for(int prefix = 2; prefix < cnt; prefix++) {
        for(int smaller_pref = prefix - 2; smaller_pref >= 0; smaller_pref--) {
            int64_t min_val = INT64_MAX;
            for (int partition = smaller_pref; partition < prefix; ++partition) {
                min_val = std::min(
                    min_val,
                    dp[smaller_pref][partition] + dp[partition + 1][prefix] + dimensions[smaller_pref].first * dimensions[partition + 1].first *dimensions[prefix].second
                );
            }
            dp[smaller_pref][prefix] = min_val;
            // dp[smaller_pref][smaller_pref + prefix] = std::min(
            //     calc_mul_op(dimensions[smaller_pref], {dimensions[smaller_pref + 1].first, dimensions[smaller_pref + prefix].second}) + dp[smaller_pref + 1][smaller_pref + prefix],
            //     dp[smaller_pref][smaller_pref + prefix - 1] + calc_mul_op({dimensions[smaller_pref].first, dimensions[smaller_pref + prefix - 1].second}, dimensions[smaller_pref + prefix])
            // );


            // if (str[it] == str[it + len]) {
            //     dp[it][it + len] = dp[it+1][it + len] + dp[it][it + len-1] + 1;
            // } else {
            //     dp[it][it + len] = dp[it+1][it + len] + dp[it][it + len-1] - dp[it+1][it + len-1];
            // }
        }
    }

    // std::cout << "base\n\t";
    //  for (int col = 0; col < dp.size(); ++col) {
    //     std::cout << '\t' << col;
    // }
    // std::cout << '\n';
    // for (int row = 0; row < dp.size(); ++row) {
    //     std::cout << "row:\t" <<  row << ':';
    //     for (int col = 0; col < dp.size(); ++col) {
    //         std::cout << '\t' << dp[row][col];
    //     }
    //     std::cout << '\n';
    // }

    std::cout << dp[0][cnt - 1];
    // std::cout << std::max(
    //             calc_mul_op(dimensions[0], {dimensions[1].first, dimensions[cnt - 2].second}),
    //             calc_mul_op({dimensions[0].first, dimensions[cnt - 3].second}, dimensions[cnt - 2])
    //         );
    // std::cout << "\n first on (from 2 until n):" << calc_mul_op(dimensions[0], {dimensions[1].first, dimensions[cnt - 2].second});
    // std::cout << "\n (from 1 until n - 1) on second:" << calc_mul_op({dimensions[0].first, dimensions[cnt - 3].second}, dimensions[cnt - 2]);
    return 0;

    // std::string str;
    // std::cin >> str;
    // std::vector<std::vector<int64_t>> dp(str.length(), std::vector<int64_t>(str.length(), 0));

    // for(int it = 0; it < str.length(); it++) 
    //     dp[it][it] = 1;
  

    // for(int len = 1; len < str.length(); len++) {
    //     for(int it = 0; it + len < str.length(); it++) {;
    //         if (str[it] == str[it + len]) {
    //             dp[it][it + len] = dp[it+1][it + len] + dp[it][it + len-1] + 1;
    //         } else {
    //             dp[it][it + len] = dp[it+1][it + len] + dp[it][it + len-1] - dp[it+1][it + len-1];
    //         }
    //     }
    // }
    
    // std::cout << dp[0][str.length() - 1];

    return 0;
}