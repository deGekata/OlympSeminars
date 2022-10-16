#include <vector>
#include <inttypes.h>
#include <string>
#include <iostream>

int64_t n = 1001;
std::vector<std::vector<int64_t>> fenvik;

void upd(int64_t x, int64_t y, int64_t val) {
    for (int64_t i = x; i < n; i = (i | (i+1))) {
        for (int64_t j = y; j < n; j = (j | (j+1))) {
            fenvik[i][j] += val;
        }
    }
}

int64_t get_sum(int64_t x, int64_t y) {
    int64_t sm1 = 0;
    for (int64_t i = x; i >= 0; i = (i & (i+1)) - 1) {
        for (int64_t j = y; j >= 0; j = (j & (j+1)) - 1) {
            sm1 += fenvik[i][j];
        }
    }
    return sm1;
}

int main()
{
    fenvik.resize(n, std::vector<int64_t>(n));
    std::string mod;
    std::vector<std::vector<int64_t>> table(n, std::vector<int64_t>(n));
    while (std::cin >> mod) {
        if (mod == "ADD") {
            int64_t v, x, y;
            std::string at;
            std::cin >> v >> at >> x >> y;
            table[x][y] += v;
            upd(x, y, v);
        } else if (mod == "SUM"){
            std::string from, to;
            int64_t x1, y1, x2, y2;
            std::cin >> from >> x1 >> y1 >> to >> x2 >> y2;
            std::cout << get_sum(x2, y2) - get_sum(x2, y1 - 1) - get_sum(x1 - 1, y2) + get_sum(x1 - 1, y1 - 1) << '\n';
        } else if (mod == "REMOVE") {
            int64_t x, y;
            std::cin >> x >> y;
            upd(x, y, -table[x][y]);
            table[x][y] = 0;
        } else if (mod == "CHANGE") {
            int64_t x, y, v;
            std::string at, to;
            std::cin >> at >> x >> y >> to >> v;
            upd(x, y, v - table[x][y]);
            table[x][y] = v;
        }
    }
    return 0;
}
