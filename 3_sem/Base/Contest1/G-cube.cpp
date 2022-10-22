#include <iostream>
#include <algorithm>

void find_prob(long double** matrix, uint64_t  N) {
    // for (int it = c_try; it <= (6 * c_try); ++it) {
    //     prev[it] /= 6;
    // }
    for (uint64_t  c_try = 1; c_try < N; c_try++) {
        for (uint64_t  cur_sum = c_try; cur_sum <= (c_try * 6); cur_sum++) {
            matrix[c_try][cur_sum] /= 6;
            
            for (uint64_t  add = 1; (add <= 6) && ((cur_sum + add) <= (6 * (c_try + 1))); ++add) {
                matrix[c_try + 1][cur_sum + add] += matrix[c_try][cur_sum];
            }
        }
    }
    return;
}


int main() {
    uint64_t  N = 0, M = 0;
    std::cin >> N >> M;

    if (M < N || M > (6 * N)) {
        std::cout << "0.00000000000000000000000000000000000000000000000000000";
        return 0;
    }


    long double** matrix = new long double*[N + 1];

    for (int tr = 1; tr <= N; ++tr) {
        matrix[tr] = new long double[6*N + 1]();
    }

    for (int it = 0; it <= 6; ++it) {
        matrix[1][it] = static_cast<long double>(1);
        // next[it] = static_cast<long double>(1);
    }

    
    find_prob(matrix, N);

    printf("%.19Lf\n", matrix[N][M] / static_cast<long double>(6));
    return 0;
}