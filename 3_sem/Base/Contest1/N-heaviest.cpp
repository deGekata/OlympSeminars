#include <iostream>
#include <algorithm>
#include <vector>


int main() {
    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<int64_t>> matrix(N, std::vector<int64_t>(M));
    std::vector<std::vector<int64_t>> dp(N, std::vector<int64_t>(M));

    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < M; ++col) {
            std::cin >> matrix[row][col];
        }
    }

    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < M; ++col) {
            if (row == 0 && col == 0) 
                matrix[row][col] = matrix[row][col];
            else if (row == 0) 
                matrix[row][col] += matrix[row][col - 1]; 
            else if (col == 0) 
                matrix[row][col] += matrix[row - 1][col]; 
            else
                matrix[row][col] += matrix[row][col - 1] + matrix[row - 1][col] - matrix[row - 1][col - 1];
        }
    }

    int64_t ans = matrix[0][0];
    for (int row1 = 0; row1 < N; ++row1) {
        for (int col1 = 0; col1 < M; ++col1) {
            
            

            for (int row2 = row1; row2 < N; ++row2) {
                for (int col2 = col1; col2 < M; ++col2) {
                    int64_t cur_ans = 0;

                    if (row1 == 0 && col1 == 0)
                        cur_ans = matrix[row2][col2];
                    else if(row1 == 0)
                        cur_ans = matrix[row2][col2] - matrix[row2][col1 - 1];
                    else if(col1 == 0)
                        cur_ans = matrix[row2][col2] - matrix[row1 - 1][col2];
                    else
                        cur_ans = matrix[row2][col2] - matrix[row2][col1 - 1] - matrix[row1 -1][col2] + matrix[row1 - 1][col1 - 1];

                    ans = std::max(ans, cur_ans);
                }
            }

        }
    }
    std::cout << ans;
    

    return 0;
}
