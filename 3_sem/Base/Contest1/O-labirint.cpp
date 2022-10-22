#include <iostream>
#include <algorithm>
#include <vector>




int main() {
    int N, M, K;
    std::cin >> N >> M >> K;
    
    std::vector<std::vector<uint64_t>> matrix(N + 2, std::vector<uint64_t>(M + 2, 0));
    std::vector<std::vector<std::vector<uint64_t>>> dp_cnt(K + 2, std::vector<std::vector<uint64_t>>(N + 2, std::vector<uint64_t>(M + 2, 0)));

    char tmp;
    std::pair<int, int> exit_coords  = {0, 0};
    std::pair<int, int> enter_coords = {0, 0};
    for (int row = 1; row <= N; ++row) {
        for (int col = 1; col <= M; ++col) {
            std::cin >> tmp;
            switch (tmp)
            {
            case '@':
                enter_coords = {row, col};
                //enter
                matrix[row][col] = 1;
                dp_cnt[0][row][col] = 1;
                break;

            case '#':
                exit_coords  = {row, col};
                matrix[row][col] = 1;
                break;
            case '.':
                matrix[row][col] = 1;
                break;
            case '+':
                matrix[row][col] = 0;
                break;
            default:
                break;
            }
        }
    }

    for (int epoch = 1; epoch <= K; ++epoch) {
        for (int row = 1; row <= N; ++row) {
            for (int col = 1; col <= M; ++col) {
                if (matrix[row][col]) {
                    dp_cnt[epoch][row][col] = dp_cnt[epoch - 1][row + 1][col    ] * matrix[row + 1][col    ] +
                                              dp_cnt[epoch - 1][row - 1][col    ] * matrix[row - 1][col    ] +
                                              dp_cnt[epoch - 1][row    ][col + 1] * matrix[row    ][col + 1] +
                                              dp_cnt[epoch - 1][row    ][col - 1] * matrix[row    ][col - 1];
                                            //   dp_cnt[epoch][row][col] * matrix[row][col];
                }
            }
        }
    }

    std::cout << dp_cnt[K][exit_coords.first][exit_coords.second];

    return 0;
}