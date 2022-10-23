#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <bit>
#include <stdio.h>

int main() {

    int N;
    std::cin >> N;
    std::vector<std::pair<double, double>> vertex_coords(N);
    for (int it = 0; it < N; ++it) {
        std::cin >> vertex_coords[it].first >> vertex_coords[it].second;
    }

    std::vector<std::vector<double>> dist(N, std::vector<double>(N));
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            dist[i][j] = sqrt(pow(vertex_coords[i].first - vertex_coords[j].first, 2) + pow(vertex_coords[i].second - vertex_coords[j].second, 2));
        }
    }

    std::vector<double> opt(1<<N, __DBL_MAX__);
    //base:

    opt[0b11] = dist[0][1];
    opt[0b00] = 0;
    //base mask
    // int mask = 0b11;
    for (int mask = 0; mask  <= (1 << N) - 1; ++mask) {
        if (std::__popcount(mask) % 2 != 0) continue;

        int cur = __builtin_ctz(~mask);
        if (cur  < std::__popcount(mask) / 2) continue;
        for (int i = cur + 1; i < N; ++i) {
                if (((1 << i) & mask)) continue;

                opt[mask | (1 << i) | (1 << cur)] = std::min(opt[mask | (1 << i) | (1 << cur)], opt[mask] + dist[i][cur]);
            
        }

    }
  
    printf("%.10lf", opt[(1 << N) - 1]); 

    return 0;
}