#include <iostream> 
#include <algorithm>
#include <vector>

std::vector<int> optimal;
std::vector<int> nails;
std::vector<bool> connected;
int N;
int calc_ans(int it) {
    if (it > N - 3) return 0;

    if (optimal[it] == 0) {
        optimal[it] = nails[it + 1] - nails[it] + std::max(calc_ans(it + 2), calc_ans(it + 3));
    }

    return optimal[it];
}



int main() {


    std::cin >> N;
    nails.resize(N, 0);
    optimal.resize(N + 10, 0);
    connected.resize(N, 0);

    for (int it = 0; it < N; ++it) {
        std::cin >> nails[it];
    }

    std::sort(nails.begin(), nails.end());
    
    // for (int it = 0; it < nails.size(); ++it) {
    //     std::cout << nails[it] << " ";
    // }
    // std::cout << "\n";

    // optimal[0] = nails[1] - nails[0];
    // optimal[1] = nails[2] - nails[0];
    
    std:: cout << nails[nails.size() - 1] - nails[0] - std::max(calc_ans(1), calc_ans(2));

    // for (int it = 0; it < optimal.size(); ++it) {
    //     std::cout << optimal[it] << " ";
    // }
    // std::cout << "\n";
    // std::cout << optimal[N - 1];
    return 0;
}