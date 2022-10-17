#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

std::string st1;
std::string st2;

int get_optimal_comb(int** matrix, std::pair<int, int> pos, bool is_eq) {
    if (pos.first == 0)
        return 0;
    else if (pos.second == 0) 
        return 0;
    
    if (!is_eq) return 0;

    return matrix[pos.first - 1][pos.second - 1] + 1;
}

void get_ans(int** matrix) {
    int max_length = 0;
    std::vector<std::string> res_st;
    std::vector<int> res;
    for (int row = 0; row < st1.length() + 1; ++row)
        for (int col = 0; col < st2.length() + 1; ++col) {
            if (max_length < matrix[row][col]) {
                max_length = matrix[row][col];
            }
    }

    if (max_length == 0) {
        std::cout << "";
        return;
    }
    // std::cout << max_length << " mx \n";
    for (int row = 1; row < st1.length() + 1; ++row) {
        for (int col = 1; col < st2.length() + 1; ++col) {
            if (max_length == matrix[row][col]) {
                res_st.push_back("");
                // std::cout << row << " " << col << "\n";
                for (int it = max_length - 1; it >= 0; --it) {
                    // std::cout << "kek";
                    res_st[res_st.size() - 1].push_back(st1[row - 1 - it]);
                }
                // std::cout << "'"<<  res_st[res_st.size() - 1] <<"'\n";
            }
        } 
    }
        
    std::sort(res_st.begin(), res_st.end());
    std::cout << res_st[0] << "\n";
    // std::cout << "   'lol' ";
}



int main() {
    std::cin >> st1 >> st2;
    // std::getline(std::cin, first);
    // std::getline(std::cin, second);
    // int* lol = new int[30000 * 70000];
    int16_t* fline = new int16_t[st1.length() + 1];
    int16_t* sline = new int16_t[st1.length() + 1];
    // for (int it = 0; it < st1.length(); ++it) {
    //     matrix[it] = new int16_t[st2.length()];
    // }

    // std::vector<int> matrix(30000 * 20000);
    // std::vector<std::vector<int>> matrix(first.length() + 1);
    for (int it = 0; it < st1.length() + 1; ++it) {
        fline[it] = 0;
    }
    // std::cout << "lol";
    // for (int x = 0; x <= st1.length(); ++x) {
    //     matrix[x][0] = get_optimal_comb(matrix, {x, 0}, 0);
    // }

    // for (int y = 0; y <= st2.length(); ++y) {
    //     matrix[0][y] = get_optimal_comb(matrix, {0, y}, 0);
    // }
    std::pair<int, int> cur_max_pos = {0, 0};
    std::vector<int> mx_poses;
    int max_len = 0;
    for (int y = 1; y < st2.length() + 1; ++y) {
        for (int x = 1; x < st1.length() + 1; ++x) {
            if (st1[x-1] == st2[y-1]) {
                if (max_len == fline[x-1] + 1) {
                    mx_poses.push_back(x - 1);
                }
                if (max_len < fline[x-1] + 1) {
                    max_len = fline[x-1] + 1;
                    cur_max_pos = {x - 1, y - 1};
                    mx_poses.clear();
                    mx_poses.push_back(cur_max_pos.first);
                }
                sline[x] = fline[x-1] + 1;
            } else {
                sline[x] = 0;
            }
        }
        std::swap(fline, sline);
    }

    // std::cout << cur_max_pos.first << " maxlen" << max_len << "lol\n";
    std::vector<std::string> vars;
    for (auto pos: mx_poses) {
        std::string buff;
        // std::cout << pos << "pos\n";
        for (int it = pos - max_len + 1; it <= pos; ++it) {
            buff.push_back(st1[it]);
        }
        vars.push_back(buff);
        // std::cout << "iter";
    }
    std::sort(vars.begin(), vars.end());
    std::cout << vars[0];
    // get_ans(matrix);
    // delete[] matrix;
    return 0;
}