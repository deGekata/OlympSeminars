#include <iostream>
#include <string>
#include <vector>



int main() {

    std::string str;
    std::cin >> str;
    std::vector<std::vector<int64_t>> dp(str.length(), std::vector<int64_t>(str.length(), 0));

    for(int it = 0; it < str.length(); it++) 
        dp[it][it] = 1;
  

    for(int len = 1; len < str.length(); len++) {
        for(int it = 0; it + len < str.length(); it++) {;
            if (str[it] == str[it + len]) {
                dp[it][it + len] = dp[it+1][it + len] + dp[it][it + len-1] + 1;
            } else {
                dp[it][it + len] = dp[it+1][it + len] + dp[it][it + len-1] - dp[it+1][it + len-1];
            }
        }
    }
    
    std::cout << dp[0][str.length() - 1];

    return 0;
}