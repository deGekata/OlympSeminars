#include <vector>
#include <string>
#include <iostream>
#include <algorithm>


int get_optimal_comb(std::vector<std::vector<int>>& matrix, std::pair<int, int> pos, bool is_eq) {
    if (pos.first == 0)
        return pos.second;
    else if (pos.second == 0) 
        return pos.first;
    
    return std::min(
                    std::min(matrix[pos.first - 1][pos.second], matrix[pos.first][pos.second - 1]) + 1,
                    matrix[pos.first - 1][pos.second - 1] + static_cast<int>(is_eq)
                   );
}

int main() {
    std::string first, second;
    std::cin >> first >> second;
    std::vector<std::vector<int>> matrix(first.length() + 1);
    for (int it = 0; it <= first.length(); ++it) {
        matrix[it] = std::vector<int>(second.length() + 1, 0);
    }

    for (int x = 0; x <= first.length(); ++x) {
        matrix[x][0] = get_optimal_comb(matrix, {x, 0}, 0);
    }

    for (int y = 0; y <= second.length(); ++y) {
        matrix[0][y] = get_optimal_comb(matrix, {0, y}, 0);
    }

    for (int x = 1; x <= first.length(); ++x) {
        for (int y = 1; y <= second.length(); ++y) {
            matrix[x][y] = get_optimal_comb(matrix, {x, y}, first[x - 1] != second[y - 1] && (x != 0 && y != 0));
        }
    }

    // for (int x = 0; x <= first.length(); ++x) {
    //     for (int y = 0; y <= second.length(); ++y) {
    //         std::cout << '\t' << matrix[x][y];
    //     }
    //     std::cout << '\n';
    // }

    std::cout << matrix[first.length()][second.length()];
    return 0;
}